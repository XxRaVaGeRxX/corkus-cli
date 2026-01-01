#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <sstream>

#include "../headers/options.h"
#include "../headers/xmltemplates.h"

using std::cout;
using std::cin;
using std::string;
using std::getline;
using std::vector;

void DirConfig(const string &modName) {
    const string configPath = modName + "/Config";

    if (!std::filesystem::exists(modName)) {
        std::filesystem::create_directory(modName);
        cout << " </> Created mod directory: " << modName << " </> \n";
    }

    if (!std::filesystem::exists(configPath)) {
        std::filesystem::create_directory(configPath);
        cout << " </> Created Config directory in " << modName << " </> \n";
    }
}

void createXMLSkeleton(const string &modName, const string &skeletonName, const string &style) {
    DirConfig(modName);

    const string filePath = modName + "/Config/" + skeletonName + ".xml";

    if (std::ofstream xmlFile(filePath); xmlFile.is_open()) {
        // Get template content based on skeleton name and style
        string templateContent = getXMLTemplate(skeletonName, style);
        xmlFile << templateContent;

        xmlFile.close();
        cout << " </> Created " << skeletonName << ".xml (" << style << " style) in " << modName << "/Config/ </> \n";
        cout << " </> PATH </> " << std::filesystem::absolute(filePath) << " </> \n";
    } else {
        cout << " </> Failed to create " << skeletonName << ".xml </> \n";
    }
}

void createAllXMLSkeletons(const string &modName, const string &style) {
    const vector<string> skeletons = {
        "items", "blocks", "recipes", "buffs", "traders", "item_modifiers",
        "loot", "progression", "entityclasses", "entitygroups", "archetypes",
        "biomes", "loadingscreen", "materials", "particles", "rwgmixer",
        "sounds", "spawning", "ui_display", "vehicle_properties",
        "worldglobal", "quests", "dialogs", "npc"
    };

    cout << "\n </> Creating all XML skeletons (" << style << " style) in " << modName << "/Config/... </> \n";
    for (const auto &skeleton: skeletons) {
        createXMLSkeleton(modName, skeleton, style);
    }
    cout << "\n </> All skeletons created successfully! </> \n";
}


void xmlSkeletonMenu(const string &modName, const string &style) {
    bool continueMenu = true;

    while (continueMenu) {
        cout << "\n </> XML Skeleton Tool Open in: " << modName << " (Style: " << style << ") </> \n";
        cout << " </> 0. Create ALL skeletons </> \n";
        cout << " </> 1. items </>\n";
        cout << " </> 2. blocks </> \n";
        cout << " </> 3. recipes </>\n";
        cout << " </> 4. buffs </>\n";
        cout << " </> 5. traders </>\n";
        cout << " </> 6. item_modifiers </>\n";
        cout << " </> 7. loot </>\n";
        cout << " </> 8. progression </>\n";
        cout << " </> 9. entityclasses </>\n";
        cout << " </> 10. entitygroups </>\n";
        cout << " </> 11. archetypes </>\n";
        cout << " </> 12. biomes </>\n";
        cout << " </> 13. loadingscreen </>\n";
        cout << " </> 14. materials </>\n";
        cout << " </> 15. particles </>\n";
        cout << " </> 16. rwgmixer </>\n";
        cout << " </> 17. sounds </>\n";
        cout << " </> 18. spawning </>\n";
        cout << " </> 19. ui_display </>\n";
        cout << " </> 20. vehicle_properties </>\n";
        cout << " </> 21. worldglobal </>\n";
        cout << " </> 22. quests </>\n";
        cout << " </> 23. dialogs </>\n";
        cout << " </> 24. npc </>\n";
        cout << " </> 25. Multi-Select </>\n";
        cout << " </> 26. Continue Setup </>\n";
        cout << " </> Select option (0-26): </> ";

        int choice;
        cin >> choice;
        cin.ignore();

        const vector<string> skeletons = {
            "items", "blocks", "recipes", "buffs", "traders", "item_modifiers",
            "loot", "progression", "entityclasses", "entitygroups", "archetypes",
            "biomes", "loadingscreen", "materials", "particles", "rwgmixer",
            "sounds", "spawning", "ui_display", "vehicle_properties",
            "worldglobal", "quests", "dialogs", "npc"
        };

        if (choice == 0) {
            createAllXMLSkeletons(modName, style);
            continueMenu = false;
        } else if (choice >= 1 && choice <= 24) {
            createXMLSkeleton(modName, skeletons[choice - 1], style);
            continueMenu = false;
        } else if (choice == 25) {
            selectSkel(modName, style);
            continueMenu = false;
        } else if (choice == 26) {
            continueMenu = false;
            cout << " </> Returning to main menu </> \n";
        } else {
            cout << " </> Invalid option. Please try again. </> \n";
        }
    }
}


void selectSkel(const string &modName, const string &style) {
    const vector<string> skeletons = {
        "items", "blocks", "recipes", "buffs", "traders", "item_modifiers",
        "loot", "progression", "entityclasses", "entitygroups", "archetypes",
        "biomes", "loadingscreen", "materials", "particles", "rwgmixer",
        "sounds", "spawning", "ui_display", "vehicle_properties",
        "worldglobal", "quests", "dialogs", "npc"
    };
    vector<bool> selected(skeletons.size(), false);

    bool selecting = true;
    while (selecting) {
        cout << "\n </> Select multiple skeletons for: " << modName << " (Style: " << style << ") </> \n";
        cout << " </> (enter option number, 0 to finish) </> \n";
        for (size_t i = 0; i < skeletons.size(); i++) {
            cout << " " << (i + 1) << ". " << skeletons[i]
                    << (selected[i] ? " [✓]" : "") << "\n";
        }
        cout << " 0. Create selected skeletons\n";
        cout << " </> Enter selection: </> ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 0) {
            selecting = false;
        } else if (choice > 0 && choice <= static_cast<int>(skeletons.size())) {
            selected[choice - 1] = !selected[choice - 1];
            cout << " </> " << skeletons[choice - 1]
                    << (selected[choice - 1] ? " added" : " removed") << " </> \n";
        } else {
            cout << " </> Invalid option. </> \n";
        }
    }

    bool anySelected = false;
    for (size_t i = 0; i < skeletons.size(); i++) {
        if (selected[i]) {
            createXMLSkeleton(modName, skeletons[i], style);
            anySelected = true;
        }
    }

    if (!anySelected) {
        cout << " </> No skeletons selected. </> \n";
    } else {
        cout << "\n </> Selected skeletons created successfully! </> \n";
    }
}

void createSFC(const string &modName, const string &numbers, const string &style) {
    string trimmed = numbers;
    trimmed.erase(0, trimmed.find_first_not_of(" \t\r\n"));
    trimmed.erase(trimmed.find_last_not_of(" \t\r\n") + 1);

    if (trimmed.empty()) {
        return;
    }

    const vector<string> skeletons = {
        "items", "blocks", "recipes", "buffs", "traders", "item_modifiers",
        "loot", "progression", "entityclasses", "entitygroups", "archetypes",
        "biomes", "loadingscreen", "materials", "particles", "rwgmixer",
        "sounds", "spawning", "ui_display", "vehicle_properties",
        "worldglobal", "quests", "dialogs", "npc"
    };

    if (trimmed.find('0') != string::npos) {
        createAllXMLSkeletons(modName, style);
        return;
    }

    cout << "\n </> Creating XML skeletons (" << style << " style) from config: " << trimmed << " </> \n";

    std::istringstream stream(trimmed);
    string token;
    int createdCount = 0;

    while (std::getline(stream, token, ',')) {
        token.erase(0, token.find_first_not_of(" \t"));
        token.erase(token.find_last_not_of(" \t") + 1);

        try {
            if (const int num = std::stoi(token); num >= 1 && num <= static_cast<int>(skeletons.size())) {
                createXMLSkeleton(modName, skeletons[num - 1], style);
                createdCount++;
            } else {
                cout << " </> Warning: Invalid skeleton number " << num
                        << " (must be 1-" << skeletons.size() << ") </> \n";
            }
        } catch (const std::exception &) {
            cout << " </> Warning: Could not parse number '" << token << "' </> \n";
        }
    }

    if (createdCount > 0) {
        cout << " </> Created " << createdCount << " skeleton(s) from config </> \n";
    }
}
