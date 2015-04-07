#include <iostream>
#include <SDL.h>
#include "ui.h"
#include "utils.h"
#include "events.h"

SdlEvents::SdlEvents(SdlUi *ui) : ui(ui) { }
SdlEvents::~SdlEvents() {}

bool SdlEvents::run(const std::string &file1, const std::string &file2) {

    SDL_Event e;
    int currentImage = 1;
    ui->showImage(file1);

    while (1) {
        if(!SDL_WaitEvent(&e)) {
            logSDLError("SDL_WaitEvent");
            return false;
        }

        if (e.type == SDL_QUIT){
            break;
        }

        if (e.type == SDL_MOUSEBUTTONDOWN) {
            currentImage = currentImage == 1 ? 2 : 1;
        }

        //Render the scene
        if(!ui->showImage(currentImage == 1 ? file1 : file2)) {
            return false;
        }


    }

    return true;
}