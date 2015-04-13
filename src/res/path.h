#pragma once

#include <string>

/*
 * Get the resource path for resources located in res/subDir
 */
std::string getResourcePath(const std::string subDir = "") {
    // TODO: Implement x-platform install dir

    std::string result = "/home/alex/working/C++/SdlPanelUi/res/" + subDir + "/";
    return result;
}