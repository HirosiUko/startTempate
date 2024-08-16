#include <Poco/SingletonHolder.h>
#include <Poco/Logger.h>
#include "MessageService.h"
#include "HJ_Template_Handler.h"

#define LOG initial_logger()
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
    Poco::AutoPtr<MessageService> _service;
    
    Template();
    ~Template(){};

    Template(const Template &) = delete;
    Template &operator=(const Template &) = delete;

    friend class Poco::SingletonHolder<Template>;
};