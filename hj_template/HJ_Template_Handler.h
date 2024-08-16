#ifndef _HJ_TEMPLATE_HANDLER_H_
#define _HJ_TEMPLATE_HANDLER_H_

#include "MessageHandler.h"
#include "Log.h"
#include <Poco/AutoPtr.h>
class MyTestService_Handler : virtual public MessageHandler
{
private:
    Poco::Logger &_log;

public:
    MyTestService_Handler() : _log(Poco::Logger::get("Template2")) {
        _log.setChannel(formattingChannel);
        _log.information("MyTestService_Handler Constructor");
    }

    void handleMessage(const Message &msg) override;
};

#endif // _HJ_TEMPLATE_HANDLER_H_