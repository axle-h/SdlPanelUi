#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "utils.h"
#include "ui.h"
#include "../litehtml/litehtml.h"
#include "litehtml_container.h"


SdlUi::SdlUi(const std::string fonts, const int width, const int height) : fonts(fonts), width(width), height(height) { }
SdlUi::~SdlUi() {
    std::cout << "Shutdown" << std::endl;
    sdlCleanup(this->pBackground, this->pSDLWindow);
    TTF_Quit();
    SDL_Quit();
}

bool SdlUi::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        logSDLError("SDL_Init");
        return false;
    }

    SDL_WM_SetCaption("SDL UI", "SDL UI");
    this->pSDLWindow = SDL_SetVideoMode(this->width, this->height, 32, SDL_SWSURFACE);

    if (this->pSDLWindow == nullptr){
        logSDLError("SDL_CreateWindow");
        return false;
    }

    //Initialize SDL_ttf
    if(TTF_Init() == -1)
    {
        logSDLError("TTF_Init");
        return false;
    }

    litehtml_container* litehtmlContainer = new litehtml_container(this->fonts + "FreeMono.ttf", this->fonts + "FreeSans.ttf", this->fonts + "FreeSerif.ttf");
    litehtml::context html_context = litehtml::context();
    html_context.load_master_stylesheet("");
    litehtml::document::ptr m_html = litehtml::document::createFromString("<html><body>Hello World!</body></html>", litehtmlContainer, &html_context);

    return true;
}

bool SdlUi::showImage(const std::string &file) {
    //Initialize to nullptr to avoid dangling pointer issues
    (this->pBackground);
    this->pBackground = nullptr;

    //Load the image
    SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());

    //If the loading went ok, convert to texture and set to the background
    if (loadedImage != nullptr){
        this->pBackground = loadedImage;
    }
    else {
        logSDLError("LoadBMP");
        return false;
    }

    //Apply image to screen
    SDL_BlitSurface(this->pBackground, NULL, this->pSDLWindow, NULL);

    //Update Screen
    SDL_Flip(this->pSDLWindow);

    return true;
}