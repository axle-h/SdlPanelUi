#include "SdlPanelUi.h"


class SdlPanelUi : public ISdlPanelUi {
private:
    IApplicationConfig* config;
    ILogger*log;
public:
    INJECT(SdlPanelUi(IApplicationConfig* config, ILogger* log)) : config(config), log(log) {
    }

    virtual void run() override {
        this->log->debug(this->config->getVersionString());
    }
};

fruit::Component<fruit::Required<IApplicationConfig, ILogger>, ISdlPanelUi> getSdlPanelUiComponent() {
    return fruit::createComponent().bind<ISdlPanelUi, SdlPanelUi>();
}