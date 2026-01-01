#include <filesystem>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include "../headers/path.h"

using std::string;
using std::cin;
using std::cout;
using std::cerr;
using std::getline;

namespace fs = std::filesystem;

void addToPath() {
    fs::path currentExe = fs::canonical("/proc/self/exe");
    fs::path corkusDir = currentExe.parent_path();

    const char *home = getenv("HOME");
    if (!home) {
        cerr << " </> ✗ Could not determine home directory </>\n";
        return;
    }

    string exportLine = "export PATH=\"" + corkusDir.string() + ":$PATH\"";

    cout << "\n </> Corkus PATH Manager </>\n";
    cout << " </> This allows running 'corkus' from any directory </>\n";
    cout << " </> Corkus location: " << corkusDir << " </>\n\n";
    cout << " ┌─ Add to PATH ─────────────────────────────────┐\n";
    cout << " │  1. Add to ~/.bashrc                          │\n";
    cout << " │  2. Add to ~/.zshrc                           │\n";
    cout << " ├─ Remove from PATH ───────────────────────────-┤\n";
    cout << " │  3. Remove from ~/.bashrc                     │\n";
    cout << " │  4. Remove from ~/.zshrc                      │\n";
    cout << " ├───────────────────────────────────────────────┤\n";
    cout << " │  5. Cancel                                    │\n";
    cout << " └───────────────────────────────────────────────┘\n";
    cout << " </> Choice: ";

    string choice;
    getline(cin, choice);

    fs::path configFile;

    if (choice == "1") {
        configFile = fs::path(home) / ".bashrc";
    } else if (choice == "2") {
        configFile = fs::path(home) / ".zshrc";
    } else if (choice == "3") {
        configFile = fs::path(home) / ".bashrc";
    } else if (choice == "4") {
        configFile = fs::path(home) / ".zshrc";
    } else {
        cout << " </> Cancelled </>\n";
        return;
    }

    // Add to PATH
    if (choice == "1" || choice == "2") {
        // Check if already in config
        std::ifstream inFile(configFile);
        string content((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
        inFile.close();

        if (content.find(corkusDir.string()) != string::npos) {
            cout << " </> Corkus is already in " << configFile << " </>\n";
            return;
        }

        // Append to config file
        std::ofstream outFile(configFile, std::ios::app);
        if (!outFile) {
            cerr << " </> ✗ Could not open " << configFile << " </>\n";
            return;
        }

        outFile << "\n# Corkus PATH\n" << exportLine << "\n";
        outFile.close();

        cout << " </> ✓ Added to " << configFile << " </>\n";
        cout << " </> Run 'source " << configFile << "' or restart your terminal </>\n";
    }
    // Remove from PATH
    else if (choice == "3" || choice == "4") {
        std::ifstream inFile(configFile);
        if (!inFile) {
            cerr << " </> ✗ Could not open " << configFile << " </>\n";
            return;
        }

        string content((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
        inFile.close();

        // Find and remove Corkus PATH lines
        string searchStr = corkusDir.string();
        if (content.find(searchStr) == string::npos) {
            cout << " </> Corkus not found in " << configFile << " </>\n";
            return;
        }

        // Remove the Corkus PATH block
        std::istringstream stream(content);
        std::ostringstream result;
        string line;
        bool skipNext = false;

        while (getline(stream, line)) {
            if (line.find("# Corkus PATH") != string::npos) {
                skipNext = true;
                continue;
            }
            if (skipNext && line.find(searchStr) != string::npos) {
                skipNext = false;
                continue;
            }
            skipNext = false;
            result << line << "\n";
        }
        std::ofstream outFile(configFile);
        if (!outFile) {
            cerr << " </> ✗ Could not write to " << configFile << " </>\n";
            return;
        }

        outFile << result.str();
        outFile.close();

        cout << " </> ✓ Removed from " << configFile << " </>\n";
        cout << " </> Run 'source " << configFile << "' or restart your terminal </>\n";
    }
}
