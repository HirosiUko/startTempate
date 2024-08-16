#include "HJ_Template.h"
#include "Log.h"

Template::Template() : log(Poco::Logger::get("Template"))
{
    log.setChannel(formattingChannel);

    log.information("Template Constructor");
    MessageService _service(1, _my_handler);
}