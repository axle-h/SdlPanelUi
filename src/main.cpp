#include "sdl/SdlPanelUiWindow.h"
#include "sdl/SdlPanelUi.h"

fruit::Component<ISdlPanelUi> createBindings() {
    return fruit::createComponent()
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