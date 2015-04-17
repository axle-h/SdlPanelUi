#include "sdl/SdlPanelUiWindow.h"
#include "sdl/SdlPanelUi.h"
#include "sdl/LiteHtmlSdlContainer.h"

fruit::Component<ISdlPanelUi> createBindings() {
    return fruit::createComponent()
            .install(getLiteHtmlSdlContainer())
            .install(getSdlPanelUiWindowComponent())
            .install(getSdlPanelUiComponent())
            .install(getApplicationConfigComponent())
            .install(getLoggerComponent());
}


int main() {
    fruit::Injector<ISdlPanelUi> injector(createBindings());
    ISdlPanelUi* sdlPanelUi = injector.get<ISdlPanelUi*>();

    return sdlPanelUi->run();
}