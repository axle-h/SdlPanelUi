#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "utils.h"
#include "SdlPanelUiWindow.h"
#include <litehtml/litehtml.h>

class SdlPanelUiWindow : public ISdlPanelUiWindow {
private:
    IApplicationConfig *config;
    ILogger *log;
    SDL_Surface *pSDLWindow;
    SDL_Surface *pBackground;
    litehtml::document_container *liteHtmlContainer;

public:
    INJECT(SdlPanelUiWindow(ILogger *log, IApplicationConfig *config, litehtml::document_container *liteHtmlContainer))
            : log(log), config(config), liteHtmlContainer(liteHtmlContainer) {
    }

    virtual ~SdlPanelUiWindow() {
        sdlCleanup(this->pBackground, this->pSDLWindow);
        TTF_Quit();
        SDL_Quit();
    }

    bool init();

    bool showImage(const std::string &file);

};


bool SdlPanelUiWindow::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        this->log->sdl_error("SDL_Init");
        return false;
    }

    SDL_WM_SetCaption("SDL UI", "SDL UI");
    this->pSDLWindow = SDL_SetVideoMode(this->config->getWindowWidth(), this->config->getWindowHeight(), 32, SDL_SWSURFACE);

    if (this->pSDLWindow == nullptr){
        this->log->sdl_error("SDL_CreateWindow");
        return false;
    }

    //Initialize SDL_ttf
    if(TTF_Init() == -1)
    {
        this->log->sdl_error("TTF_Init");
        return false;
    }

    litehtml::context html_context = litehtml::context();
    html_context.load_master_stylesheet("");
    litehtml::document::ptr m_html = litehtml::document::createFromString("<html><body>Hello World!</body></html>", this->liteHtmlContainer, &html_context);

    return true;
}

bool SdlPanelUiWindow::showImage(const std::string &file) {
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
        this->log->sdl_error("LoadBMP");
        return false;
    }

    //Apply image to screen
    SDL_BlitSurface(this->pBackground, NULL, this->pSDLWindow, NULL);

    //Update Screen
    SDL_Flip(this->pSDLWindow);

    return true;
}

fruit::Component<fruit::Required<IApplicationConfig, ILogger, litehtml::document_container>, ISdlPanelUiWindow> getSdlPanelUiWindowComponent() {
    return fruit::createComponent().bind<ISdlPanelUiWindow, SdlPanelUiWindow>();
}
