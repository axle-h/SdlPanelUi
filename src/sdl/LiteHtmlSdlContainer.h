#pragma once

#include <litehtml/html.h>
#include "../log/Logger.h"

fruit::Component<fruit::Required<ILogger, IApplicationConfig>, litehtml::document_container> getLiteHtmlSdlContainer();
