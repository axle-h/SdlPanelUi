#pragma once

#include <SDL.h>
#include "ui.h"
#include "utils.h"

class SdlEvents {
    SdlUi *ui;
public:
    SdlEvents(SdlUi *ui);
    ~SdlEvents();

    bool run(const std::string &file1, const std::string &file2);

};