#ifndef CORKUS_CONFIG_H
#define CORKUS_CONFIG_H

#include <string>

using namespace std;

struct Config {
    string dAuthor = "Unknown";
    string dVersion = "1.0.0";
    string dWebsite = "https://your-website.com";
    string dDesc = "My cool mod project.";
    string dDisName = "Cool Mod Name";
    string dName = "MyCoolMod";
    string output_filename = "ModInfo.xml";
    bool show_welcome_message = true;
    bool pause_after_completion = true;
    bool auto_generate_config = true;
    string xml_skeletons = "_";
    string xml_template_style = "standard";
    string xml_templates;
};

Config loadConfig();

void genDefault();

bool genCustom();

void showLoad();

const Config &getConfig();

#endif
