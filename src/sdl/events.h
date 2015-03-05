#ifndef SDLPANELUI_SDL_EVENTS_H
#define SDLPANELUI_SDL_EVENTS_H

#include <SDL.h>
#include "ui.h"

class SdlEvents {
    SdlUi *ui;
public:
    SdlEvents(SdlUi *ui) : ui(ui) { };
    ~SdlEvents() {};

    bool run(const std::string &file) {

        SDL_Event e;
        bool quit = false;
        bool imageIsShowing = false;
        bool showImage = false;
        bool hideImage = false;

        while (!quit) {

            while (SDL_PollEvent(&e)){
                if (e.type == SDL_QUIT){
                    quit = true;
                }
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                    if(imageIsShowing) {
                        hideImage = true;
                    } else {
                        showImage = true;
                    }
                }
            }

            //Render the scene
            if(showImage && !imageIsShowing) {
                if(!ui->showImage(file)) {
                    return false;
                }
                showImage = false;
                imageIsShowing = true;
            }

            if(hideImage && imageIsShowing) {
                ui->hideImage();
                hideImage = false;
                imageIsShowing = false;
            }

        }

        return true;
    }

};


#endif