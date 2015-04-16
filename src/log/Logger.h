#pragma once

#include <iostream>
#include <fruit/fruit.h>
#include "../config/ApplicationConfig.h"

class ILogger {
public:
    virtual void debug(std::string value) = 0;
    virtual void debug(const char* stringFormat, ...) = 0;

    virtual void info(std::string value) = 0;
    virtual void info(const char* stringFormat, ...) = 0;

    virtual void warn(std::string value) = 0;
    virtual void warn(const char* stringFormat, ...) = 0;

    virtual void error(std::string value) = 0;
    virtual void error(const char* stringFormat, ...) = 0;

    virtual void sdl_error(std::string value) = 0;
};

fruit::Component<fruit::Required<IApplicationConfig>, ILogger> getLoggerComponent();