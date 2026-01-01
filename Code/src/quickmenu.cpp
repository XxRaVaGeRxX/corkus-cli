#include <iostream>
#include <string>
#include <filesystem>

#include "../headers/quickmenu.h"
#include "../headers/config.h"
#include "../headers/main.h"
#include "../headers/options.h"

using std::cout;
using std::string;

bool userInput(const std::string &question) {
    std::string input;

    cout << question << " (y/n): ";
    getline(std::cin, input);

    if (!input.empty()) {
        input[0] = static_cast<char>(tolower(static_cast<unsigned char>(input[0])));
    }

    return input == "y" || input == "yy" || input == "yes" || input == "Y" || input == "Yes" || input == "YES";
}

void SkipMenu() {
    if (userInput(" </> Do you already have an un.cork ready to bake? </>")) {
        const Config config = loadConfig();
        const ModInfo mod = getInfoFromConfig(config);

        const string modName = mod.name;
        const string fileName = config.output_filename;
        showLoad();
        writeFile(modName, fileName, mod);
        createSFC(modName, config.xml_skeletons, config.xml_template_style);

        cout << "\n </> Corkus has finished processing. EXITING... </>" << std::endl;
        exit(0);
    }

    cout << " </> DevNote: There is a basic overwrite protection for un.cork </> \n\n";
    makeCustomConfig();
}

void MultiSelMenu() {
    if (userInput(" </> Do you want to include additional xml files (ex: items.xml)? </>")) {
        const Config config = loadConfig();
        const ModInfo mod = getInfo(config);
        const string modName = mod.name;
        xmlSkeletonMenu(modName, config.xml_template_style);
    }
    cout << " </> Continuing </> \n";
}

void makeCustomConfig() {
    if (userInput(" </> |y| Do you want to generate an un.cork? |y|< OR >|n| Continue with guided setup? |n| </>")) {
        genCustom();

        const Config config = loadConfig();
        const string modName = config.dName;
        cout << "\n </>  ### CONFIGURATION FILE GENERATED ###  </> \n" << std::endl;
        cout << "\n </> EXITING... </> \n" << std::endl;
        exit(0);
    } else {
        cout << "\n </> Continuing... </> \n" << std::endl;
        cout << "\n </> Skipping Config Generation </> \n" << std::endl;

        const Config config = loadConfig();
        const ModInfo mod = getInfoFromConfig(config);
        const string modName = mod.name;
        const string fileName = config.output_filename;

        MultiSelMenu();
        writeFile(modName, fileName, mod);

        exit(0);
    }
}
