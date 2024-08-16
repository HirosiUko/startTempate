#include "HJ_Template.h"
#include "Log.h"

Template::Template() : log(Poco::Logger::get("Template")), _service(Poco::AutoPtr<MessageService>(new MessageService(1, _my_handler)))
{
    log.setChannel(formattingChannel);
    log.information("Template Constructor");
}