#pragma once

#include <iostream>
#include <fruit/fruit.h>

class IApplicationConfig {
public:
    virtual std::string getVersionString() = 0;
    virtual int getWindowWidth() = 0;
    virtual int getWindowHeight() = 0;
    virtual std::string getResourcePath(const std::string subDir = "") = 0;
    virtual std::string getLog4CppConfigPath() = 0;
};

fruit::Component<IApplicationConfig> getApplicationConfigComponent();
