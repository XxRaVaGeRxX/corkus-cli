#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>

void DirConfig(const std::string &modName);

void createXMLSkeleton(const std::string &modName, const std::string &skeletonName, const std::string &style = "standard");

void xmlSkeletonMenu(const std::string &modName, const std::string &style = "standard");

void createAllXMLSkeletons(const std::string &modName, const std::string &style = "standard");

void selectSkel(const std::string &modName, const std::string &style = "standard");

void createSFC(const std::string &modName, const std::string &numbers, const std::string &style = "standard");

#endif
