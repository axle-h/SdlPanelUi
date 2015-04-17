#pragma once

#include <SDL.h>
#include <utility>
#include <litehtml/html.h>
#include "../config/ApplicationConfig.h"
#include "../log/Logger.h"


class ISdlPanelUiWindow {
public:
    virtual ~ISdlPanelUiWindow() = default;

    virtual bool init() = 0;

    virtual bool showImage(const std::string &file) = 0;
};

fruit::Component<fruit::Required<IApplicationConfig, ILogger, litehtml::document_container>, ISdlPanelUiWindow> getSdlPanelUiWindowComponent();