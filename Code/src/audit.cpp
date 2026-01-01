#include <string>
#include <string_view>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cctype>
#include <functional>

#include "../headers/audit.h"
#include "../headers/corkml.h"

using namespace std;

CorkValidationResult validate_cork_file(std::string_view filepath) {
    CorkValidationResult result;

    // Use CorkML parser
    CorkMLDocument doc = CorkMLParser::parse(std::string(filepath));

    if (doc.root.name.empty()) {
        result.is_valid = false;
        result.errors.emplace_back(" </> | Unable to parse .cork file | </> ");
        return result;
    }

    // Recursive helper to find a value by tag name at any depth
    std::function<string(const CorkMLNode &, const string &)> findValue;
    findValue = [&findValue](const CorkMLNode &node, const string &tagName) -> string {
        if (node.name == tagName) return node.value;
        for (const auto &child: node.children) {
            string val = findValue(child, tagName);
            if (!val.empty()) return val;
        }
        return "";
    };

    auto getValue = [&doc, &findValue](const string &tagName) -> string {
        return findValue(doc.root, tagName);
    };

    // Check required fields
    vector<string> required_fields = {"Name", "DisplayName", "Description", "Author", "Version"};
    for (const auto &field: required_fields) {
        if (getValue(field).empty()) {
            result.errors.emplace_back("</> | Missing required field: " + field + " | </>");
        }
    }

    // Validate boolean fields
    string welcomeMsg = getValue("WelcomeMessage");
    if (!welcomeMsg.empty() && welcomeMsg != "true" && welcomeMsg != "false") {
        result.errors.emplace_back("</> | WelcomeMessage must be 'true' or 'false' | </>");
    }

    string pauseAfter = getValue("PauseAfterCompletion");
    if (!pauseAfter.empty() && pauseAfter != "true" && pauseAfter != "false") {
        result.errors.emplace_back("</> | PauseAfterCompletion must be 'true' or 'false' | </>");
    }

    string autoGen = getValue("AutoGenerateConfig");
    if (!autoGen.empty() && autoGen != "true" && autoGen != "false") {
        result.errors.emplace_back("</> | AutoGenerateConfig must be 'true' or 'false' | </>");
    }

    // Validate XMLSkeletons
    string skeletons = getValue("Skeletons");
    if (!skeletons.empty()) {
        stringstream ss(skeletons);
        string token;
        while (getline(ss, token, ',')) {
            token.erase(0, token.find_first_not_of(" \t"));
            token.erase(token.find_last_not_of(" \t") + 1);
            if (!token.empty()) {
                try {
                    int xmlSkel = stoi(token);
                    if (xmlSkel < 0 || xmlSkel > 24) {
                        result.errors.emplace_back("</> | Skeletons value must be between 0-24 | </>");
                    }
                } catch (...) {
                    result.errors.emplace_back("</> | Invalid Skeletons value: " + token + " | </>");
                }
            }
        }
    }

    // Extract and verify KEY using a parser
    string keyInFile = getValue("KEY");

    // Validate KEY exists and has a correct format

    if (keyInFile.empty()) {
        result.errors.emplace_back("</> | PARSE ERROR: Missing KEY - file may be corrupted | </>");
        result.is_valid = false;
        return result;
    }

    if (constexpr size_t KEY_LENGTH = 64; keyInFile.length() != KEY_LENGTH) {
        result.errors.emplace_back("</> | PARSE ERROR: Malformed KEY (expected " +
                                   std::to_string(KEY_LENGTH) + " chars, got " +
                                   std::to_string(keyInFile.length()) + ") | </>");
        result.is_valid = false;
        return result;
    }

    // Validate KEY contains only valid hex characters
    for (char c: keyInFile) {
        if (!std::isxdigit(static_cast<unsigned char>(c))) {
            result.errors.emplace_back("</> | PARSE ERROR: KEY contains invalid characters (must be hex) | </>");
            result.is_valid = false;
            return result;
        }
    }

    if (string sec_key_in_file = decryptKey(keyInFile); !verifyInFile(string(filepath), sec_key_in_file)) {
        result.errors.emplace_back("</> | Security key not found in .keys file | </>");
    }

    result.is_valid = result.errors.empty();
    return result;
}

bool verifyInFile(const string &configFile, const string &secKey) {
    std::ifstream keysFile(".keys");
    if (!keysFile.is_open()) {
        return false;
    }

    string encryptedData;
    string line;
    while (getline(keysFile, line)) {
        if (!line.empty() && line[0] != '#') {
            encryptedData += line;
        }
    }
    keysFile.close();

    if (encryptedData.empty()) {
        return false;
    }

    string decryptedContent = decryptFile(encryptedData);
    std::istringstream contentStream(decryptedContent);

    string filename = configFile;
    if (size_t last_slash = configFile.find_last_of("/\\"); last_slash != string::npos) {
        filename = configFile.substr(last_slash + 1);
    }

    string keyLine;
    while (getline(contentStream, keyLine)) {
        if (keyLine.empty() || keyLine[0] == '#') {
            continue;
        }

        if (size_t pos = keyLine.find('='); pos != string::npos) {
            string label = keyLine.substr(0, pos);
            string encrypted_key = keyLine.substr(pos + 1);

            if (label == configFile || label == filename) {
                if (string stored_key = decryptKey(encrypted_key); stored_key == secKey) {
                    return true;
                }
            }
        }
    }
    return false;
}


string generateKey(const string &content) {
    unsigned long hash = 5381;
    unsigned long hash2 = 0;
    for (const char c: content) {
        hash = ((hash << 5) + hash) + c;
        hash2 = hash2 * 33 + c;
    }

    std::stringstream ss;
    ss << std::hex << std::setfill('0') << std::setw(16) << hash << std::setw(16) << hash2;
    return ss.str();
}


bool verifyKey(const string &filename) {
    // Use CorkML parser to read the config file
    CorkMLDocument doc = CorkMLParser::parse(filename);

    if (doc.root.name.empty()) {
        cerr << "\n </> Error-93: Unable to parse " << filename << " </> \n";
        return false;
    }

    // Recursive helper to find a value by tag name at any depth
    std::function<string(const CorkMLNode &, const string &)> findValue;
    findValue = [&findValue](const CorkMLNode &node, const string &tagName) -> string {
        if (node.name == tagName) return node.value;
        for (const auto &child: node.children) {
            if (string val = findValue(child, tagName); !val.empty()) return val;
        }
        return "";
    };

    // Helper lambda to get values (searches all depths)
    auto getValue = [&doc, &findValue](const string &tagName) -> string {
        return findValue(doc.root, tagName);
    };

    // Get KEY using a parser
    string keyInFile = getValue("KEY");

    // Validate KEY format

    if (keyInFile.empty()) {
        cerr << "\n </> PARSE ERROR: Missing KEY in " << filename << " </> \n";
        return false;
    }

    if (constexpr size_t EXPECTED_ENCRYPTED_KEY_LENGTH = 64;
        keyInFile.length() != EXPECTED_ENCRYPTED_KEY_LENGTH) {
        cerr << "\n </> PARSE ERROR: Malformed KEY in " << filename
                << " (expected " << EXPECTED_ENCRYPTED_KEY_LENGTH
                << " chars, got " << keyInFile.length() << ") </> \n";
        return false;
    }

    // Check for valid hex characters
    for (char c: keyInFile) {
        if (!std::isxdigit(static_cast<unsigned char>(c))) {
            cerr << "\n </> PARSE ERROR: KEY contains invalid characters in " << filename << " </> \n";
            return false;
        }
    }

    string storedKeyInConfig = decryptKey(keyInFile);

    if (storedKeyInConfig.empty()) {
        cerr << "\n </> Error-347: KEY decryption failed for " << filename << " </> \n";
        return false;
    }

    std::ifstream keysFile(".keys");
    if (!keysFile.is_open()) {
        cerr << "\n </> Error-302: .keys file not found! </> \n";
        return false;
    }

    string encryptedData;
    string line;
    while (getline(keysFile, line)) {
        if (!line.empty() && line[0] != '#') {
            encryptedData += line;
        }
    }
    keysFile.close();

    if (encryptedData.empty()) {
        cerr << "\n </> Error: .keys file is empty! </> \n";
        return false;
    }

    string decryptedFile = decryptFile(encryptedData);

    std::istringstream contentStream(decryptedFile);
    string keyLine;
    bool found = false;
    while (getline(contentStream, keyLine)) {
        if (keyLine.empty() || keyLine[0] == '#') {
            continue;
        }

        if (size_t pos = keyLine.find('='); pos != string::npos) {
            string label = keyLine.substr(0, pos);
            string encrypted_key = keyLine.substr(pos + 1);

            if (label == filename) {
                if (string storedKeyInKeys = decryptKey(encrypted_key); storedKeyInKeys == storedKeyInConfig) {
                    cout << "\n </> KEY Verified For " << filename << " </> ";
                    found = true;
                    break;
                }
            }
        }
    }

    if (!found) {
        cerr << "\n </> !!! Security key mismatch for " << filename << " !!! </> \n";
        return false;
    }

    return true;
}


void saveSecKey(const string &configFile, const string &secKey) {
    const string keyFile = ".keys";

    string existingContent;
    if (std::ifstream checkFile(keyFile); checkFile.good()) {
        checkFile.close();

        std::ifstream encFile(keyFile);
        string encryptedData;
        string line;
        while (getline(encFile, line)) {
            if (!line.empty() && line[0] != '#') {
                encryptedData += line;
            }
        }
        encFile.close();

        if (!encryptedData.empty()) {
            existingContent = decryptFile(encryptedData);
        }
    }

    std::ostringstream contentBuilder;

    if (existingContent.empty()) {
        contentBuilder << "# Corkus Config Security Keys (Encrypted)\n";
        contentBuilder << "# Format: filename=encrypted_key_hash\n";
        contentBuilder << "# DO NOT MANUALLY EDIT - Keys are encrypted\n";
        contentBuilder << "# ------------------------------------\n";
    } else {
        contentBuilder << existingContent;
    }

    string encryptedKey = encryptKey(secKey);
    contentBuilder << configFile << "=" << encryptedKey << "\n";
    contentBuilder << "# ------------------------------------\n";

    string plainContent = contentBuilder.str();
    string encryptedFileContent = encryptFile(plainContent);

    std::ofstream keysFileOut(keyFile);
    keysFileOut << "#            CORKUS KEY VAULT\n";
    keysFileOut << "#  Format: filename=encrypted_key_hash\n";
    keysFileOut << "# -------------------------------------\n";
    keysFileOut << encryptedFileContent;
    keysFileOut.close();
}


string loadSecKeyFromFile(const string &configFile) {
    std::ifstream keysFile(".keys");
    if (!keysFile.is_open()) {
        return "";
    }

    string encryptedData;
    string line;
    while (getline(keysFile, line)) {
        if (!line.empty() && line[0] != '#') {
            encryptedData += line;
        }
    }
    keysFile.close();

    if (encryptedData.empty()) {
        return "";
    }

    string decryptedCont = decryptFile(encryptedData);
    std::istringstream contentStream(decryptedCont);

    string filename = configFile;
    if (size_t last_slash = configFile.find_last_of("/\\"); last_slash != string::npos) {
        filename = configFile.substr(last_slash + 1);
    }

    string keyLine;
    while (getline(contentStream, keyLine)) {
        if (keyLine.empty() || keyLine[0] == '#') {
            continue;
        }

        if (size_t pos = keyLine.find('='); pos != string::npos) {
            string label = keyLine.substr(0, pos);
            string encrypted_key = keyLine.substr(pos + 1);

            if (label == configFile || label == filename) {
                return decryptKey(encrypted_key);
            }
        }
    }
    return "";
}


string encryptKey(const string &plaintext) {
    const string salt = "C0rKu5_S3cUr1tY_K3Y_2025";
    string key;
    for (size_t i = 0; i < 64; ++i) {
        key += static_cast<char>((salt[i % salt.length()] + i * 7) % 256);
    }

    string encrypted;
    for (size_t i = 0; i < plaintext.length(); ++i) {
        const char encryptedChar = static_cast<char>(plaintext[i] ^ key[i % key.length()]);
        char hex[3];
        snprintf(hex, sizeof(hex), "%02x", static_cast<unsigned char>(encryptedChar));
        encrypted += hex;
    }

    return encrypted;
}


string decryptKey(const string &ciphertext) {
    const string salt = "C0rKu5_S3cUr1tY_K3Y_2025";
    string key;
    for (size_t i = 0; i < 64; ++i) {
        key += static_cast<char>((salt[i % salt.length()] + i * 7) % 256);
    }

    string decrypted;
    for (size_t i = 0; i < ciphertext.length(); i += 2) {
        if (i + 1 < ciphertext.length()) {
            string byteStr = ciphertext.substr(i, 2);
            char byte = static_cast<char>(stoi(byteStr, nullptr, 16));
            decrypted += static_cast<char>(byte ^ key[(i / 2) % key.length()]);
        }
    }

    return decrypted;
}


string encryptFile(const string &content) {
    const string salt = "C0rKu5_F1L3_3nCrYpT_2025";
    string key;
    for (size_t i = 0; i < 128; ++i) {
        key += static_cast<char>((salt[i % salt.length()] + i * 13) % 256);
    }

    string encrypted;
    size_t charCount = 0;

    for (size_t i = 0; i < content.length(); ++i) {
        char encryptedChar = static_cast<char>(content[i] ^ key[i % key.length()]);
        char hex[3];
        snprintf(hex, sizeof(hex), "%02x", static_cast<unsigned char>(encryptedChar));
        encrypted += hex;
        charCount += 2;

        // Add newline every LINE_LENGTH characters
        if (constexpr size_t LINE_LENGTH = 40; charCount >= LINE_LENGTH) {
            encrypted += "\n";
            charCount = 0;
        }
    }

    return encrypted;
}


string decryptFile(const string &ciphertext) {
    const string salt = "C0rKu5_F1L3_3nCrYpT_2025";
    string key;
    for (size_t i = 0; i < 128; ++i) {
        key += static_cast<char>((salt[i % salt.length()] + i * 13) % 256);
    }

    // Remove newlines and whitespace from ciphertext
    string cleanCiphertext;
    for (const char c: ciphertext) {
        if (c != '\n' && c != '\r' && c != ' ' && c != '\t') {
            cleanCiphertext += c;
        }
    }

    string decrypted;
    for (size_t i = 0; i < cleanCiphertext.length(); i += 2) {
        if (i + 1 < cleanCiphertext.length()) {
            string byteStr = cleanCiphertext.substr(i, 2);
            try {
                char byte = static_cast<char>(stoi(byteStr, nullptr, 16));
                decrypted += static_cast<char>(byte ^ key[(i / 2) % key.length()]);
            } catch (...) {
                return "";
            }
        }
    }

    return decrypted;
}
