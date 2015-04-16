#include "Logger.h"

#include <log4cpp/Priority.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>
#include <SDL_error.h>


class Log4CppLogger : public ILogger {
private:
    log4cpp::Category *log;

public:
    INJECT(Log4CppLogger(IApplicationConfig* config)) {
        log4cpp::PropertyConfigurator::configure(config->getLog4CppConfigPath());
        this->log = &log4cpp::Category::getRoot();
    }

    ~Log4CppLogger() {
        log4cpp::Category::shutdown();
        delete this->log;
    }

    virtual void debug(std::string value) override {
        this->log->debug(value);
    }

    virtual void debug(const char* stringFormat, ...) override {
        va_list vaList;
        va_start(vaList, stringFormat);
        this->log->logva(log4cpp::Priority::DEBUG, stringFormat, vaList);
        va_end(vaList);
    }

    virtual void info(std::string value) override {
        this->log->info(value);
    }

    virtual void info(const char *stringFormat, ...) override {
        va_list vaList;
        va_start(vaList, stringFormat);
        this->log->logva(log4cpp::Priority::INFO, stringFormat, vaList);
        va_end(vaList);
    }

    virtual void warn(std::string value) override {
        this->log->warn(value);
    }

    virtual void warn(const char *stringFormat, ...) override {
        va_list vaList;
        va_start(vaList, stringFormat);
        this->log->logva(log4cpp::Priority::WARN, stringFormat, vaList);
        va_end(vaList);
    }

    virtual void error(std::string value) override {
        this->log->error(value);
    }

    virtual void error(const char *stringFormat, ...) override {
        va_list vaList;
        va_start(vaList, stringFormat);
        this->log->logva(log4cpp::Priority::ERROR, stringFormat, vaList);
        va_end(vaList);
    }

    virtual void sdl_error(std::string value) override {
        this->log->errorStream() << value << " error: " << SDL_GetError();
    }
};

fruit::Component<fruit::Required<IApplicationConfig>, ILogger> getLoggerComponent() {
    return fruit::createComponent().bind<ILogger, Log4CppLogger>();
}