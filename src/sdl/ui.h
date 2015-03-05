#pragma once

#include <SDL.h>
#include <utility>

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
    SdlUi(const int width, const int height);
    ~SdlUi();

    bool init();

    bool showImage(const std::string &file);

    void hideImage();
};