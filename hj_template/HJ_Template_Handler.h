#include "MessageHandler.h"
#include "Log.h"
#include <iostream>   
class MyTestService_Handler : virtual public MessageHandler
{
    Poco::Logger &_log;
public:
    MyTestService_Handler() : _log(Poco::Logger::get("Template2")) {
        _log.setChannel(formattingChannel);
        _log.information("MyTestService_Handler Constructor");
    }

    void handleMessage(const Message &msg) override
    {
        _log.information("Thread %d says: %s", int(msg.sender_id), msg.text);
    }
};