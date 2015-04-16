#pragma once

#include <SDL.h>
#include <utility>

class SdlPanelUiWindow {
private:
    int width, height;
    SDL_Surface *pSDLWindow;
    SDL_Surface *pBackground;
    std::string fonts;

public:
    SdlPanelUiWindow(std::string fonts, const int width, const int height);
    ~SdlPanelUiWindow();

    bool init();

    bool showImage(const std::string &file);

};