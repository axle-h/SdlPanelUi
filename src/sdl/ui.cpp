#include <iostream>
#include <SDL.h>
#include "utils.h"
#include "ui.h"


SdlUi::SdlUi(const int width, const int height) : width(width), height(height) { }
SdlUi::~SdlUi() {
    std::cout << "Shutdown" << std::endl;
    sdlCleanup(this->pBackground, this->pSDLRenderer, this->pSDLWindow);
    SDL_Quit();
}

bool SdlUi::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        logSDLError("SDL_Init");
        return false;
    }

    this->pSDLWindow = SDL_CreateWindow("SDL UI", 100, 100, this->width, this->height, SDL_WINDOW_SHOWN);
    if (this->pSDLWindow == nullptr){
        logSDLError("SDL_CreateWindow");
        return false;
    }

    this->pSDLRenderer = SDL_CreateRenderer(this->pSDLWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (pSDLRenderer == nullptr){
        logSDLError("SDL_CreateRenderer");
        return false;
    }

    this->createBackground();
    return true;
}

bool SdlUi::showImage(const std::string &file) {
    //Initialize to nullptr to avoid dangling pointer issues
    sdlCleanup(this->pBackground);
    this->pBackground = nullptr;

    //Load the image
    SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());

    //If the loading went ok, convert to texture and set to the background
    if (loadedImage != nullptr){
        this->pBackground = SDL_CreateTextureFromSurface(this->pSDLRenderer, loadedImage);
        SDL_FreeSurface(loadedImage);

        //Make sure converting went ok too
        if (this->pBackground == nullptr){
            logSDLError("CreateTextureFromSurface");
            return false;
        }
    }
    else {
        logSDLError("LoadBMP");
        return false;
    }

    SDL_RenderClear(this->pSDLRenderer);
    SDL_RenderCopy(this->pSDLRenderer, this->pBackground, NULL, NULL);
    SDL_RenderPresent(this->pSDLRenderer);

    return true;
}

void SdlUi::hideImage() {
    this->createBackground();
}