#include "SdlPanelUi.h"

class SdlPanelUi : public ISdlPanelUi {
private:
    IApplicationConfig* config;
    ILogger* log;
    ISdlPanelUiWindow* ui;

public:
    INJECT(SdlPanelUi(ISdlPanelUiWindow* window, IApplicationConfig* config, ILogger* log)) : config(config), log(log), ui(window) {
    }

    virtual int run() override {
        this->log->debug(this->config->getVersionString());
        if(!this->ui->init()) {
            return 1;
        }

        std::string file1 = this->config->getResourcePath("images") + "hello.bmp";
        std::string file2 = this->config->getResourcePath("images") + "hello2.bmp";

        SDL_Event e;
        int currentImage = 1;
        ui->showImage(file1);

        while (1) {
            if(!SDL_WaitEvent(&e)) {
                this->log->sdl_error("SDL_WaitEvent");
                return 1;
            }

            if (e.type == SDL_QUIT){
                return 0;
            }

            if (e.type == SDL_MOUSEBUTTONDOWN) {
                currentImage = currentImage == 1 ? 2 : 1;
            }

            //Render the scene
            if(!ui->showImage(currentImage == 1 ? file1 : file2)) {
                return 1;
            }
        }
    }
};

fruit::Component<fruit::Required<ISdlPanelUiWindow, IApplicationConfig, ILogger>, ISdlPanelUi> getSdlPanelUiComponent() {
    return fruit::createComponent().bind<ISdlPanelUi, SdlPanelUi>();
}