#ifndef CORKUS_MAIN_H
#define CORKUS_MAIN_H

#include <fstream>
#include <string>

struct ModInfo {
    std::string name;
    std::string dName;
    std::string desc;
    std::string author;
    std::string version;
    std::string website;
};

struct Config;

void writeFile(const std::string &modName, const std::string &fileName, const ModInfo &mod);

void modDir(const std::string &modName);

ModInfo getInfo(const Config &config);

ModInfo getInfoFromConfig(const Config &config);

#endif //CORKUS_MAIN_H
