#pragma once

#include <SDL.h>
#include <utility>

class SdlUi {
private:
    int width, height;
    SDL_Surface *pSDLWindow;
    SDL_Surface *pBackground;

public:
    SdlUi(const int width, const int height);
    ~SdlUi();

    bool init();

    bool showImage(const std::string &file);

};