#include <sstream>
#include "ApplicationConfig.h"
#include "SdlPanelUiConfig.h"

class ApplicationConfig : public IApplicationConfig {
public:
    INJECT(ApplicationConfig()) = default;

    virtual std::string getVersionString() override {
        std::stringstream stream;
        stream << SdlPanelUi_PROJECT_NAME << " " << SdlPanelUi_VERSION_MAJOR << "." << SdlPanelUi_VERSION_MINOR;
        return stream.str();
    }

    virtual int getWindowWidth() override {
        return SdlPanelUi_FB_WIDTH;
    }

    virtual int getWindowHeight() override {
        return SdlPanelUi_FB_HEIGHT;
    }

    virtual std::string getResourcePath(const std::string subDir = "") override {
        std::string result = "/home/alex/working/C++/SdlPanelUi/res/" + subDir + "/";
        return result;
    }

    virtual std::string getLog4CppConfigPath() override {
        std::string result = getResourcePath("config") + "log4cpp.properties";
        return result;
    }
};

fruit::Component<IApplicationConfig> getApplicationConfigComponent() {
    return fruit::createComponent().bind<IApplicationConfig, ApplicationConfig>();
}