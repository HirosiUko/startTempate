import argparse
import os
import re

program_description = r'''
Auto generate code for a new service. 
If you need any help, please contact to hojune.lee(hojune.lee@42dot.ai)
'''

service_cpp = r'''
#include "AAAAAA.h"
#include "Log.h"

AAAAAA::AAAAAA() : log(Poco::Logger::get("AAAAAA")), 
                        _service(Poco::AutoPtr<MessageService>(new MessageService(1, new AAAAAA_handler(this))))
{
    log.setChannel(formattingChannel);
    log.information("AAAAAA Constructor");
}

void AAAAAA::requestA(){
    log.information("doing requestA");
}
'''

service_header = r'''
#ifndef _BBBBBB_H_
#define _BBBBBB_H_
#include <Poco/Logger.h>
#include "MessageService.h"
#include "AAAAAA_handler.h"
class AAAAAA_handler;
class AAAAAA
{
public:
    void requestA();

    AAAAAA();
    ~AAAAAA()
    {
        log.information("[%s] AAAAAA Destructor", std::string(__func__));
        log.information("[%s] [MemChk] _my_handler use_count: %d", std::string(__func__), _CCCCCC_handler.referenceCount());
    };

private:
    Poco::Logger &log;
    Poco::SharedPtr<AAAAAA_handler> _CCCCCC_handler;
    Poco::AutoPtr<MessageService> _service;

    friend class AAAAAA_intrface;
};

#endif // _HJ_TEMPLATE_H_
'''

service_handler_cpp = r'''
#include "AAAAAA_handler.h"
#include "AAAAAA_interface.h"

void AAAAAA_handler::handleMessage(const Message &msg)
{
    uint32_t command = msg.command;
    if(command >= END_OF_COMMAND){
        _log.error("Invalid Command");
        return;
    }
    switch (command)
    {
        case START_OF_COMMAND:
            break;
        case REQ_A:
            _log.information("REQ_A");
            _service->requestA();
            break;
        default:
            _log.error("Invalid Command");
            break;
    }
}
'''

service_handler_header = r'''
#ifndef _BBBBBB_HANDLER_H_
#define _BBBBBB_HANDLER_H_
#include <Poco/AutoPtr.h>
#include "MessageHandler.h"
#include "Log.h"
#include "AAAAAA.h"
class AAAAAA;
class AAAAAA_handler : virtual public MessageHandler
{
private:
    Poco::Logger &_log;
    Poco::SharedPtr<AAAAAA> _service;

public:
    AAAAAA_handler( Poco::SharedPtr<AAAAAA> service) : _log(Poco::Logger::get("AAAAAA_handler")), _service(service) {
        _log.setChannel(formattingChannel);
        _log.information("AAAAAA_handler Constructor");
    }
    ~AAAAAA_handler()=default;

    void handleMessage(const Message &msg) override;
};

#endif // _BBBBBB_HANDLER_H_
'''

service_interface = r'''
#ifndef _BBBBBB_INTERFACE_H_
#define _BBBBBB_INTERFACE_H_
#include <Poco/SingletonHolder.h>
#include <Poco/Logger.h>
#include "Log.h"
#include "AAAAAA.h"

enum BBBBBB_CMD{
    START_OF_COMMAND = 0,
    REQ_A,
    END_OF_COMMAND
};

class AAAAAA_intrface
{
public:
    // Async Interface
    void requestA_by_async()
    {
        _service->_service->sendMessage({REQ_A, "REQ_A"});
        Poco::Thread::sleep(2000);
        _service->_service->stopService();
    }
    // Sync Interface
    void requestA_by_sync()
    {
        log.information("requestA_by_sync");
        _service->requestA();
        _service->_service->stopService();
    }

    // DO Not Change!!
public:
    static AAAAAA_intrface &instance()
    {
        static Poco::SingletonHolder<AAAAAA_intrface> sh;
        return *sh.get();
    }

private:
    Poco::Logger &log;
    Poco::SharedPtr<AAAAAA> _service;

    AAAAAA_intrface() : log(Poco::Logger::get("AAAAAA_INTERFACE")), _service(new AAAAAA())
    {
        log.setChannel(formattingChannel);
    };
    ~AAAAAA_intrface() = default;

    AAAAAA_intrface(const AAAAAA_intrface &) = delete;
    AAAAAA_intrface &operator=(const AAAAAA_intrface &) = delete;

    friend class Poco::SingletonHolder<AAAAAA_intrface>;
};

#endif //_BBBBBB_INTERFACE_H_
'''

def generate_service_cpp(service_name):
    with open(service_name, "w") as f:
        new_service_name = service_name.split(".")[0]
        new_service_cpp = service_cpp.replace("AAAAAA", new_service_name)
        new_service_cpp = new_service_cpp.replace("BBBBBB", new_service_name.upper())
        new_service_cpp = new_service_cpp.replace("CCCCCC", new_service_name.lower())
        f.write(new_service_cpp)

def generate_service_header(service_name):
    with open(service_name, "w") as f:
        new_service_name = service_name.split(".")[0]
        new_service_header = service_header.replace("AAAAAA", new_service_name)
        new_service_header = new_service_header.replace("BBBBBB", new_service_name.upper())
        new_service_header = new_service_header.replace("CCCCCC", new_service_name.lower())
        f.write(new_service_header)

def generate_service_handler_cpp(service_name):
    with open(service_name, "w") as f:
        new_service_name = service_name.split("_")[0]
        new_service_handler_cpp = service_handler_cpp.replace("AAAAAA", new_service_name)
        new_service_handler_cpp = new_service_handler_cpp.replace("BBBBBB", new_service_name.upper())
        new_service_handler_cpp = new_service_handler_cpp.replace("CCCCCC", new_service_name.lower())
        f.write(new_service_handler_cpp)

def generate_service_handler_header(service_name):
    with open(service_name, "w") as f:
        new_service_name = service_name.split("_")[0]
        new_service_handler_header = service_handler_header.replace("AAAAAA", new_service_name)
        new_service_handler_header = new_service_handler_header.replace("BBBBBB", new_service_name.upper())
        new_service_handler_header = new_service_handler_header.replace("CCCCCC", new_service_name.lower())
        f.write(new_service_handler_header)

def generate_service_interface(service_name):
    with open(service_name, "w") as f:
        new_service_name = service_name.split("_")[0]
        new_service_interface = service_interface.replace("AAAAAA", new_service_name)
        new_service_interface = new_service_interface.replace("BBBBBB", new_service_name.upper())
        new_service_interface = new_service_interface.replace("CCCCCC", new_service_name.lower())
        f.write(new_service_interface)

def main():
    parser = argparse.ArgumentParser(description=program_description)
    parser.add_argument('--init', type=str, help='generate a new service')
    args = parser.parse_args()
    print(f"init : {args.init}")
    
    if not re.match("^[a-zA-Z]+$", args.init):
        print("Invalid input")
        return
    
    os.mkdir(args.init)
    os.chdir(args.init)
    print(f"Generating a new service {args.init}")
    
    print(f"Service cpp name : {args.init}.cpp")
    generate_service_cpp(f"{args.init}.cpp")
    print(f"Service header name : {args.init}.h")
    generate_service_header(f"{args.init}.h")
    print(f"Service handler name : {args.init}_handler.cpp")
    generate_service_handler_cpp(f"{args.init}_handler.cpp")
    print(f"Service handler header name : {args.init}_handler.h")
    generate_service_handler_header(f"{args.init}_handler.h")
    print(f"Service interface name : {args.init}_interface.h")
    generate_service_interface(f"{args.init}_interface.h")

if __name__ == "__main__":
    main()