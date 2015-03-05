#ifndef SDLPANELUI_SDL_EVENTS_H
#define SDLPANELUI_SDL_EVENTS_H

#include <SDL.h>
#include "ui.h"
#include "utils.h"

class SdlEvents {
    SdlUi *ui;
public:
    SdlEvents(SdlUi *ui) : ui(ui) { };
    ~SdlEvents() {};

    bool run(const std::string &file) {

        SDL_Event e;
        bool imageIsShowing = false;
        bool showImage = false;
        bool hideImage = false;

        while (1) {
            if(!SDL_WaitEvent(&e)) {
                logSDLError("SDL_WaitEvent");
                return false;
            }

            if (e.type == SDL_QUIT){
                break;
            }

            if (e.type == SDL_MOUSEBUTTONDOWN) {
                if(imageIsShowing) {
                    hideImage = true;
                } else {
                    showImage = true;
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