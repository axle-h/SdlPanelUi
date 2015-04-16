#pragma once

#include <fruit/fruit.h>
#include "config/ApplicationConfig.h"
#include "log/Logger.h"

class ISdlPanelUi {
public:
    virtual void run() = 0;
};

fruit::Component<fruit::Required<IApplicationConfig, ILogger>, ISdlPanelUi> getSdlPanelUiComponent();