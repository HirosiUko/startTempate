#include <Poco/SingletonHolder.h>
#include <Poco/Logger.h>
#include "MessageService.h"
#include "HJ_Template_Handler.h"

#define LOG initial_logger()
// #define SERVICE_NAME "HJ_Template"
class Template
{
public:
    static Template &instance()
    {
        static Poco::SingletonHolder<Template> sh;
        return *sh.get();
    }

    void doSomething()
    {
        log.information("doSomething");
    }

private:
    Poco::Logger& log;
    MyTestService_Handler _my_handler;
    
    Template();

    ~Template()
    {
        log.information("Template Destructor");
    }

    Template(const Template &) = delete;
    Template &operator=(const Template &) = delete;

    friend class Poco::SingletonHolder<Template>;
};