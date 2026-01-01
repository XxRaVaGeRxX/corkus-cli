#ifndef CORKUS_CORKML_H
#define CORKUS_CORKML_H

#include <string>
#include <map>
#include <vector>

struct CorkMLNode {
    std::string name;
    std::string value;
    std::map<std::string, std::string> attributes;
    std::vector<CorkMLNode> children;

    // Helper to find child by name
    [[nodiscard]] const CorkMLNode *findChild(const std::string &childName) const {
        for (const auto &child: children) {
            if (child.name == childName) return &child;
        }
        return nullptr;
    }

    // Helper to get child value by name
    [[nodiscard]] std::string getChildValue(const std::string &childName) const {
        if (const auto *child = findChild(childName)) {
            return child->value;
        }
        return "";
    }
};

struct CorkMLDocument {
    std::string version;
    std::string encoding;
    CorkMLNode root;

    // Helper to get value from path like "ModInfo/Name" or just "KEY"
    [[nodiscard]] std::string getValue(const std::string &path) const;
};

class CorkMLParser {
public:
    static CorkMLDocument parse(const std::string &filepath);

    static CorkMLDocument parseString(const std::string &content);

private:
    static std::string stripComments(const std::string &content);

    static std::string trim(const std::string &s);

    static CorkMLNode parseElement(const std::string &content);

    static std::vector<CorkMLNode> parseChildren(const std::string &content);
};

#endif //CORKUS_CORKML_H
