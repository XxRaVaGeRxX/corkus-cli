#include "../headers/corkml.h"
#include <fstream>
#include <sstream>
#include <regex>

std::string CorkMLDocument::getValue(const std::string &path) const {
    std::vector<std::string> parts;
    std::stringstream ss(path);
    std::string part;
    while (std::getline(ss, part, '/')) {
        if (!part.empty()) parts.push_back(part);
    }

    if (parts.empty()) return "";

    const CorkMLNode *current = &root;

    for (size_t i = 0; i < parts.size(); ++i) {
        bool found = false;

        if (current->name == parts[i]) {
            if (i == parts.size() - 1) {
                return current->value;
            }
            if (i + 1 < parts.size()) {
                if (const auto *child = current->findChild(parts[i + 1])) {
                    current = child;
                    ++i;
                    if (i == parts.size() - 1) {
                        return current->value;
                    }
                    found = true;
                    continue;
                }
            }
        }

        if (const auto *child = current->findChild(parts[i])) {
            current = child;
            found = true;
            if (i == parts.size() - 1) {
                return current->value;
            }
        }

        if (!found) return "";
    }

    return current->value;
}

CorkMLDocument CorkMLParser::parse(const std::string &filepath) {
    std::ifstream file(filepath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return parseString(buffer.str());
}

CorkMLDocument CorkMLParser::parseString(const std::string &content) {
    CorkMLDocument doc;

    const std::regex declRegex(R"lit(<\?(corkml)\s+version="([^"]+)"\s+encoding="([^"]+)"\s*\?>)lit");
    if (std::smatch declMatch; std::regex_search(content, declMatch, declRegex)) {
        doc.version = declMatch[2];
        doc.encoding = declMatch[3];
    }

    std::string stripped = stripComments(content);
    doc.root = parseElement(stripped);

    return doc;
}

std::string CorkMLParser::stripComments(const std::string &content) {
    const std::regex commentRegex("<!--[\\s\\S]*?-->");
    return std::regex_replace(content, commentRegex, "");
}

std::string CorkMLParser::trim(const std::string &s) {
    const size_t start = s.find_first_not_of(" \t\n\r");
    const size_t end = s.find_last_not_of(" \t\n\r");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

CorkMLNode CorkMLParser::parseElement(const std::string &content) {
    CorkMLNode node;

    std::regex tagRegex("<(\\w+)([^>]*)>");
    std::smatch match;
    std::string remaining = content;

    while (std::regex_search(remaining, match, tagRegex)) {
        std::string tagName = match[1];

        if (tagName == "STARTFILE" || tagName == "ENDFILE" || tagName == "CORKFILE" ||
            tagName.find('?') != std::string::npos) {
            remaining = match.suffix();
            continue;
        }

        node.name = tagName;

        std::string attrStr = match[2];
        std::regex attrRegex("(\\w+)=\"([^\"]*)\"");
        std::smatch attrMatch;
        std::string attrSearch = attrStr;
        while (std::regex_search(attrSearch, attrMatch, attrRegex)) {
            node.attributes[attrMatch[1]] = attrMatch[2];
            attrSearch = attrMatch.suffix();
        }

        std::string closeTag = "</" + tagName + ">";
        size_t closePos = remaining.find(closeTag);
        if (closePos != std::string::npos) {
            size_t contentStart = remaining.find('>') + 1;
            std::string innerContent = remaining.substr(contentStart, closePos - contentStart);

            if (innerContent.find('<') != std::string::npos) {
                node.children = parseChildren(innerContent);
            } else {
                node.value = trim(innerContent);
            }
        }
        break;
    }

    return node;
}

std::vector<CorkMLNode> CorkMLParser::parseChildren(const std::string &content) {
    std::vector<CorkMLNode> children;
    const std::regex tagRegex(R"(<(\w+)([^>]*)>([\s\S]*?)</\1>)");
    std::smatch match;
    std::string remaining = content;

    while (std::regex_search(remaining, match, tagRegex)) {
        CorkMLNode child;
        child.name = match[1];

        std::string attrStr = match[2];
        std::regex attrRegex("(\\w+)=\"([^\"]*)\"");
        std::smatch attrMatch;
        std::string attrSearch = attrStr;
        while (std::regex_search(attrSearch, attrMatch, attrRegex)) {
            child.attributes[attrMatch[1]] = attrMatch[2];
            attrSearch = attrMatch.suffix();
        }

        const std::string innerContent = match[3];
        if (innerContent.find('<') != std::string::npos) {
            child.children = parseChildren(innerContent);
        } else {
            child.value = trim(innerContent);
        }

        children.push_back(child);
        remaining = match.suffix();
    }

    return children;
}
