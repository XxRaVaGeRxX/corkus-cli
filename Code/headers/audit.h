#ifndef CORKUS_AUDIT_H
#define CORKUS_AUDIT_H

#include <string>
#include <string_view>
#include <vector>

struct CorkValidationResult {
    bool is_valid = true;
    std::vector<std::string> errors;
};

CorkValidationResult validate_cork_file(std::string_view filepath);

std::string generateKey(const std::string &content);

bool verifyKey(const std::string &filename);

void saveSecKey(const std::string &configFile, const std::string &secKey);

bool verifyInFile(const std::string &configFile, const std::string &secKey);

std::string loadSecKeyFromFile(const std::string &configFile);

// Encryption/Decryption functions for key storage
std::string encryptKey(const std::string &plaintext);

std::string decryptKey(const std::string &ciphertext);

// Full file encryption/decryption for .keys file
std::string encryptFile(const std::string &content);

std::string decryptFile(const std::string &encrypted);

#endif //CORKUS_AUDIT_H
