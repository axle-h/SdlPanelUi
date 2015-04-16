#pragma once

#include <fruit/fruit.h>
#include "SdlPanelUiWindow.h"
#include "../config/ApplicationConfig.h"
#include "../log/Logger.h"

class ISdlPanelUi {
public:
    virtual int run() = 0;
};

fruit::Component<fruit::Required<ISdlPanelUiWindow, IApplicationConfig, ILogger>, ISdlPanelUi> getSdlPanelUiComponent();