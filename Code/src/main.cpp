#include <filesystem>
#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>
#include <cstring>

#include "../headers/config.h"
#include "../headers/quickmenu.h"
#include "../headers/audit.h"
#include "../headers/options.h"
#include "../headers/path.h"

using std::string;
using std::cin;
using std::cout;
using std::cerr;
using std::getline;


struct ModInfo {
    string name;
    string dName;
    string desc;
    string author;
    string version;
    string website;
};

ModInfo getInfoFromConfig(const Config &config) {
    ModInfo mod;
    mod.name = config.dName;
    mod.dName = config.dDisName;
    mod.desc = config.dDesc;
    mod.author = config.dAuthor;
    mod.version = config.dVersion;
    mod.website = config.dWebsite;

    return mod;
}

ModInfo getInfo(const Config &config) {
    ModInfo mod;

    cout << " </> Enter Mod Name </>  ";
    getline(cin, mod.name);
    if (mod.name.empty()) {
        mod.name = config.dName;
    }

    cout << "\n </> Enter Display Name </>  ";
    getline(cin, mod.dName);
    if (mod.dName.empty()) {
        mod.dName = config.dDisName;
    }

    cout << "\n </> Enter Description </>  ";
    getline(cin, mod.desc);
    if (mod.desc.empty()) {
        mod.desc = config.dDesc;
    }

    cout << "\n </> Enter Author </>  ";
    getline(cin, mod.author);
    if (mod.author.empty()) {
        mod.author = config.dAuthor;
    }

    cout << "\n </> Enter Version </>  ";
    getline(cin, mod.version);
    if (mod.version.empty()) {
        mod.version = config.dVersion;
    }

    cout << "\n </> Enter Website </>  ";
    getline(cin, mod.website);
    if (mod.website.empty()) {
        mod.website = config.dWebsite;
    }

    return mod;
}

void modDir(const string &modName) {
    if (!std::filesystem::exists(modName)) {
        std::filesystem::create_directory(modName);
        cout << " </> Created mod directory: " << modName << " </> \n";
    }
}

void writeFile(const string &modName, const string &fileName, const ModInfo &mod) {
    modDir(modName);

    const string filePath = modName + "/" + fileName;

    if (std::ofstream xmlFile(filePath); xmlFile.is_open()) {
        xmlFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        xmlFile << "<ModInfo>\n";
        xmlFile << "    <Name value=\"" << mod.name << "\" />\n";
        xmlFile << "    <DisplayName value=\"" << mod.dName << "\" />\n";
        xmlFile << "    <Description value=\"" << mod.desc << "\" />\n";
        xmlFile << "    <Author value=\"" << mod.author << "\" />\n";
        xmlFile << "    <Version value=\"" << mod.version << "\" />\n";
        xmlFile << "    <Website value=\"" << mod.website << "\" />\n";
        xmlFile << "</ModInfo>\n";

        xmlFile.close();
        if (std::filesystem::exists("un.cork")) {
            cout << "\n </> Creating the ModInfo.xml file </> \n";
            cout << " </> Created ModInfo.xml in " << modName << "/ </> \n";
            cout << " </> PATH </> " << std::filesystem::absolute(filePath) << " </> " << std::endl;
            cout << " </> Created Successfully, Corkus will now exit </> \n";
        } else if (std::filesystem::exists(".cork")) {
            cout << "\n </> Creating the ModInfo.xml file </> \n";
            cout << " </> Created ModInfo.xml in " << modName << "/ </> \n";
            cout << " </> PATH </> " << std::filesystem::absolute(filePath) << " </> " << std::endl;
            cout << " </> Created Successfully, Corkus will now exit </> \n";
        } else {
            std::cerr << " </> | </> Error: Unable to create ModInfo.xml! See Errors in Corkus wiki </> | </> \n";
            return;
        }
    }
}

void initMsg() {
    using std::this_thread::sleep_for;
    using std::chrono::milliseconds;

    cout << "\n";


    cout << R"(     ██████╗ ██████╗ ██████╗ ██╗  ██╗██╗   ██╗███████╗
    ██╔════╝██╔═══██╗██╔══██╗██║ ██╔╝██║   ██║██╔════╝
    ██║     ██║   ██║██████╔╝█████╔╝ ██║   ██║███████╗
    ██║     ██║   ██║██╔══██╗██╔═██╗ ██║   ██║╚════██║
    ╚██████╗╚██████╔╝██║  ██║██║  ██╗╚██████╔╝███████║
    ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝ )" << std::endl;
    cout << "\n </> Corkus </> Pop The Cork On Your Mods!! </> ";
    cout << "\n </> Made By: </> RavagerStudio </> ©2026 GPL-3.0 </> \n";
    sleep_for(4s);

    cout << "\n </>  </>  </>  </> \n\n";
    cout << " </> Welcome to Corkus 1.2.2! </> \n";
    cout << " </> A CLI app for creating a ModInfo.xml </> \n";
    cout << " </> For more information visit the GitHub page </> \n";
    cout << " </> https://github.com/XxRaVaGeRxX/Corkus </> \n";
    cout << " </> Thank you for using the app! </> \n";
    cout << " </> ### TURN OFF LONG INTRO IN YOUR un.cork ### </> ";
    cout << "\n\n </> Corkus Is Ready </> \n\n";
}


void printHelp() {
    cout << R"(
 ██████╗ ██████╗ ██████╗ ██╗  ██╗██╗   ██╗███████╗
██╔════╝██╔═══██╗██╔══██╗██║ ██╔╝██║   ██║██╔════╝
██║     ██║   ██║██████╔╝█████╔╝ ██║   ██║███████╗
██║     ██║   ██║██╔══██╗██╔═██╗ ██║   ██║╚════██║
╚██████╗╚██████╔╝██║  ██║██║  ██╗╚██████╔╝███████║
 ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝

Corkus v1.2.2 - 7 Days to Die Mod Configuration Tool
Compatible with 7D2D V1.0 (Alpha 2.5+)

USAGE:
    corkus [OPTIONS]
    corkus                      Run in interactive mode

OPTIONS:
    -h, --help                  Show this help message
    -v, --version               Show version information
    --install                   Add Corkus to PATH for global access

CONFIG GENERATION:
    --new-cork                  Generate a new default .cork file
    --new-uncork                Generate a new un.cork user config
    --clean                     Remove .cork, un.cork, and .keys files

VALIDATION:
    --validate <file>           Validate a .cork or un.cork file
    --verify-keys               Verify security keys match

XML GENERATION:
    --build                     Build ModInfo.xml from current config
    --skeleton <num>            Generate XML template (1-24, or 0 for all)
    --skeleton <num> <style>    Generate with style (minimal/standard/comprehensive)
    --list-skeletons            List all available XML skeleton types

EXAMPLES:
    corkus --new-cork                    Create fresh .cork config
    corkus --new-uncork                  Create user config file
    corkus --validate .cork              Check if config is valid
    corkus --skeleton 1                  Generate items.xml template
    corkus --skeleton 3 comprehensive   Generate detailed recipes.xml
    corkus --build                       Generate ModInfo.xml

SKELETON NUMBERS:
    0  = ALL          9  = entityclasses    17 = sounds
    1  = items        10 = entitygroups     18 = spawning
    2  = blocks       11 = archetypes       19 = ui_display
    3  = recipes      12 = biomes           20 = vehicle_properties
    4  = buffs        13 = loadingscreen    21 = worldglobal
    5  = traders      14 = materials        22 = quests
    6  = item_mods    15 = particles        23 = dialogs
    7  = loot         16 = rwgmixer         24 = npc
    8  = progression

)";
}

void printVersion() {
    cout << "Corkus v1.2.2\n";
    cout << "7 Days to Die Mod Configuration Tool\n";
    cout << "Compatible with 7D2D V1.0 (Alpha 2.5+)\n";
    cout << "Made by RavagerStudio - 2026 GPL-3.0\n";
}

void listSkeletons() {
    cout << "\nAvailable XML Skeleton Types:\n";
    cout << "========================================\n";
    cout << "  0  = ALL (generate all 24 at once)\n";
    cout << "----------------------------------------\n";
    cout << "  1  = items             Item definitions\n";
    cout << "  2  = blocks            Block definitions\n";
    cout << "  3  = recipes           Crafting recipes\n";
    cout << "  4  = buffs             Status effects/buffs\n";
    cout << "  5  = traders           Trader configurations\n";
    cout << "  6  = item_modifiers    Item modification rules\n";
    cout << "  7  = loot              Loot container definitions\n";
    cout << "  8  = progression       Player progression/skills\n";
    cout << "  9  = entityclasses     Entity/creature definitions\n";
    cout << "  10 = entitygroups      Entity spawn groups\n";
    cout << "  11 = archetypes        POI archetypes\n";
    cout << "  12 = biomes            Biome definitions\n";
    cout << "  13 = loadingscreen     Loading screen tips\n";
    cout << "  14 = materials         Material properties\n";
    cout << "  15 = particles         Particle effects\n";
    cout << "  16 = rwgmixer          Random world generation\n";
    cout << "  17 = sounds            Sound definitions\n";
    cout << "  18 = spawning          Entity spawning rules\n";
    cout << "  19 = ui_display        UI display settings\n";
    cout << "  20 = vehicle_properties Vehicle configs\n";
    cout << "  21 = worldglobal       Global world settings\n";
    cout << "  22 = quests            Quest definitions\n";
    cout << "  23 = dialogs           NPC dialog trees\n";
    cout << "  24 = npc               NPC configurations\n";
    cout << "========================================\n";
}

int handleArgs(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];

        // Help
        if (arg == "-h" || arg == "--help") {
            printHelp();
            return 0;
        }

        // Version
        if (arg == "-v" || arg == "--version") {
            printVersion();
            return 0;
        }

        // Install to PATH
        if (arg == "--install") {
            addToPath();
            return 0;
        }

        // Generate new .cork
        if (arg == "--new-cork") {
            cout << " </> Generating new .cork file... </>\n";
            genDefault();
            return 0;
        }

        // Generate new un.cork
        if (arg == "--new-uncork") {
            cout << " </> Generating new un.cork file... </>\n";
            genCustom();
            return 0;
        }

        // Clean all config files
        if (arg == "--clean") {
            cout << " </> Removing configuration files... </>\n";
            if (std::filesystem::exists(".cork")) {
                std::filesystem::remove(".cork");
                cout << "   Removed .cork\n";
            }
            if (std::filesystem::exists("un.cork")) {
                std::filesystem::remove("un.cork");
                cout << "   Removed un.cork\n";
            }
            if (std::filesystem::exists(".keys")) {
                std::filesystem::remove(".keys");
                cout << "   Removed .keys\n";
            }
            cout << " </> Clean complete </>\n";
            return 0;
        }

        // Validate a file
        if (arg == "--validate") {
            if (i + 1 < argc) {
                string filepath = argv[++i];
                cout << " </> Validating " << filepath << "... </>\n";
                auto result = validate_cork_file(filepath);
                if (result.is_valid) {
                    cout << " </> ✓ " << filepath << " is valid </>\n";
                    return 0;
                } else {
                    cerr << " </> ✗ Validation failed: </>\n";
                    for (const auto &err: result.errors) {
                        cerr << "   " << err << "\n";
                    }
                    return 1;
                }
            } else {
                cerr << " </> Error: --validate requires a file path </>\n";
                cerr << " </> Usage: corkus --validate <file> </>\n";
                return 1;
            }
        }

        // Verify keys
        if (arg == "--verify-keys") {
            cout << " </> Verifying security keys... </>\n";
            bool valid = true;
            bool foundFiles = false;
            if (std::filesystem::exists(".cork")) {
                foundFiles = true;
                cout << " </> verifying .cork... </>\n";
                if (verifyKey(".cork")) {
                    cout << " </> ✓ .cork key verified </>\n";
                } else {
                    cout << " </> ✗ .cork key FAILED </>\n";
                    valid = false;
                }
            }
            if (std::filesystem::exists("un.cork")) {
                foundFiles = true;
                cout << " </> verifying un.cork... </>\n";
                if (verifyKey("un.cork")) {
                    cout << " </> ✓ un.cork key verified </>\n";
                } else {
                    cout << " </> ✗ un.cork key FAILED </>\n";
                    valid = false;
                }
            }

            if (!foundFiles) {
                cerr << " </> No .cork or un.cork files found to verify </>\n";
                return 1;
            }

            cout << " </> Verification complete </>\n";
            return valid ? 0 : 1;
        }

        // List skeletons
        if (arg == "--list-skeletons") {
            listSkeletons();
            return 0;
        }

        // Generate skeleton
        if (arg == "--skeleton") {
            if (i + 1 < argc) {
                int skelNum = std::stoi(argv[++i]);
                string style = "standard";

                // Check if style argument provided
                if (i + 1 < argc && argv[i + 1][0] != '-') {
                    style = argv[++i];
                }

                // Get mod name from config or use default
                string modName = "MyMod";
                if (std::filesystem::exists("un.cork") || std::filesystem::exists(".cork")) {
                    Config config = loadConfig();
                    modName = config.dName.empty() ? "MyMod" : config.dName;
                }

                if (skelNum == 0) {
                    createAllXMLSkeletons(modName, style);
                } else {
                    selectSkel(modName, style);
                }
                return 0;
            } else {
                cerr << " </> Error: --skeleton requires a number (0-24) </>\n";
                return 1;
            }
        }

        // Build ModInfo.xml
        if (arg == "--build") {
            cout << " </> Building ModInfo.xml from config... </>\n";

            if (!std::filesystem::exists(".cork") && !std::filesystem::exists("un.cork")) {
                cerr << " </> Error: No .cork or un.cork file found </>\n";
                cerr << " </> Run: corkus --new-cork or corkus --new-uncork first </>\n";
                return 1;
            }

            Config config = loadConfig();
            ModInfo mod = getInfoFromConfig(config);
            string modName = mod.name;
            string fileName = config.output_filename;

            // Create skeletons if configured
            if (!config.xml_skeletons.empty()) {
                createSFC(modName, config.xml_skeletons, config.xml_template_style);
            }

            writeFile(modName, fileName, mod);
            cout << " </> Build complete </>\n";
            return 0;
        }
        // Unknown argument
        cerr << " </> Unknown option: " << arg << " </>\n";
        cerr << " </> Use 'corkus --help' for usage information </>\n";
        return 1;
    }

    return -1; // No arguments processed, run interactive mode
}


int main(int argc, char *argv[]) {
    // Handle command-line arguments
    if (argc > 1) {
        return handleArgs(argc, argv);
    }

    // No arguments - run in interactive mode
    const Config config = loadConfig();
    if (config.show_welcome_message) {
        initMsg();
    } else {
        cout << "\n </> Welcome Skipped  </> \n"
                "\n";
    }
    SkipMenu();
    const ModInfo mod = getInfo(config);

    const string modName = mod.name;
    const string fileName = config.output_filename;
    writeFile(modName, fileName, mod);

    return 0;
}
