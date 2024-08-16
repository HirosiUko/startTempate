#include "HJ_Template_Handler.h"

void MyTestService_Handler::handleMessage(const Message &msg)
{
    _log.information("Thread %d says: %s", int(msg.sender_id), msg.text);
}