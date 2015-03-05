#ifndef SDLPANELUI_SDL_UI_H
#define SDLPANELUI_SDL_UI_H

#include <SDL.h>
#include "utils.h"

class SdlUi {
private:
    int width, height;
    SDL_Window *pSDLWindow;
    SDL_Renderer *pSDLRenderer;
    SDL_Texture *pBackground;

    void createBackground() {
        // Set render color to blue ( background will be rendered in this color )
        SDL_SetRenderDrawColor(this->pSDLRenderer, 0, 0, 255, 255);

        // Clear window
        SDL_RenderClear(this->pSDLRenderer);

        // Create a rect at pos ( 50, 50 ) that's 50 pixels wide and 50 pixels high.
        SDL_Rect r;
        r.x = 50;
        r.y = 50;
        r.w = 50;
        r.h = 50;

        // Set render color to red ( rect will be rendered in this color )
        SDL_SetRenderDrawColor(this->pSDLRenderer, 255, 0, 0, 255);

        // Render rect
        SDL_RenderFillRect(this->pSDLRenderer, &r);

        // Render the rect to the screen
        SDL_RenderPresent(this->pSDLRenderer);
    }

public:
    SdlUi(const int width, const int height) : width(width), height(height) { }
    ~SdlUi() {
        std::cout << "Shutdown" << std::endl;
        sdlCleanup(this->pBackground, this->pSDLRenderer, this->pSDLWindow);
        SDL_Quit();
    }

    bool init() {
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

    bool showImage(const std::string &file) {
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

    void hideImage() {
        this->createBackground();
    }
};


#endif