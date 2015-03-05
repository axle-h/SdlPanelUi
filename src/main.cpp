#define SDL_MAIN_HANDLED
#include <iostream>
#include "sdl/ui.h"
#include "sdl/events.h"
#include "res/path.h"
#include "SdlPanelUiConfig.h"


int main() {

    printf("%s Version %d.%d\n", SdlPanelUi_PROJECT_NAME, SdlPanelUi_VERSION_MAJOR, SdlPanelUi_VERSION_MINOR);

    SdlUi *ui = new SdlUi(640, 480);
    if(!ui->init()) {
        return 1;
    }

    SdlEvents *events = new SdlEvents(ui);

    std::string imagePath = getResourcePath("images") + "hello.bmp";
    bool error = events->run(imagePath);

    delete events;
    delete ui;
    return !error;
}