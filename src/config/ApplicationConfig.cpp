#include <sstream>
#include <libconfig.h++>
#include "ApplicationConfig.h"
#include "SdlPanelUiConfig.h"

class ApplicationConfig : public IApplicationConfig {
private:
    int width, height;

public:
    INJECT(ApplicationConfig()) {
        libconfig::Config cfg;
        std::string file = this->getResourcePath("config") + "SdlPanelUi.config";

        try
        {
            cfg.readFile(file.c_str());
            const libconfig::Setting &root = cfg.getRoot();
            this->width = root["SdlPanelUi"]["width"];
            this->height = root["SdlPanelUi"]["height"];
        }
        catch(const libconfig::FileIOException &ex)
        {
            std::cerr << "I/O error while reading config file: " << file << std::endl;
            throw ex;
        }
        catch(const libconfig::ParseException &ex)
        {
            std::cerr << "Parse error at " << ex.getFile() << ":" << ex.getLine() << " - " << ex.getError() << std::endl;
            throw ex;
        }
        catch(libconfig::SettingTypeException &ex) {
            std::cerr << "Wrong type for setting: " << ex.getPath() << std::endl;
            throw ex;
        }
        catch(libconfig::SettingNotFoundException &ex) {
            std::cerr << "Setting not found: " << ex.getPath() << std::endl;
            throw ex;
        }

    };

    virtual std::string getVersionString() override {
        std::stringstream stream;
        stream << SdlPanelUi_PROJECT_NAME << " " << SdlPanelUi_VERSION_MAJOR << "." << SdlPanelUi_VERSION_MINOR;
        return stream.str();
    }

    virtual int getWindowWidth() override {
        return this->width;
    }

    virtual int getWindowHeight() override {
        return this->height;
    }

    virtual std::string getResourcePath(const std::string subDir = "") override {
        std::stringstream stream;
        stream << SdlPanelUi_INSTALL_PREFIX << "/SdlPanelUi/resources/" << subDir << "/";
        return stream.str();
    }

    virtual std::string getLog4CppConfigPath() override {
        std::string result = getResourcePath("config") + "log4cpp.properties";
        return result;
    }
};

fruit::Component<IApplicationConfig> getApplicationConfigComponent() {
    return fruit::createComponent().bind<IApplicationConfig, ApplicationConfig>();
}