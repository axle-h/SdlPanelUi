#define SDL_MAIN_HANDLED
#include <iostream>
#include "sdl/ui.h"
#include "sdl/events.h"
#include "res/path.h"
#include "SdlPanelUiConfig.h"


int main() {

    printf("%s Version %d.%d\n", SdlPanelUi_PROJECT_NAME, SdlPanelUi_VERSION_MAJOR, SdlPanelUi_VERSION_MINOR);

    std::string fonts = getResourcePath("fonts");
    SdlUi *ui = new SdlUi(fonts, SdlPanelUi_FB_WIDTH, SdlPanelUi_FB_HEIGHT);
    if(!ui->init()) {
        return 1;
    }

    SdlEvents *events = new SdlEvents(ui);

    std::string hello1 = getResourcePath("images") + "hello.bmp";
    std::string hello2 = getResourcePath("images") + "hello2.bmp";

    bool error = events->run(hello1, hello2);

    delete events;
    delete ui;
    return !error;
}