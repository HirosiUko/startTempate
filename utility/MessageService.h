#ifndef _MESSAGE_SERVICE_H_
#define _MESSAGE_SERVICE_H_
#include <iostream>
#include "MessageHandler.h"
#include <Poco/Thread.h>
#include <Poco/Logger.h>
class MessageService
{
public:
    MessageService(u_int32_t id, MessageHandler &_handler) : _id(id), _service_handler(_handler)
    {
        _service_looper = new MessageLooper(id /*id*/, _service_queue, _service_handler);
        thread1.start(*_service_looper);

        // FOR Testing
        // _service_queue.sendMessage({"Hello from main thread to Thread 1!", 1});
        // Poco::Thread::sleep(2000);
        // _service_looper->stop();
        
    }
    ~MessageService(){
        thread1.join();
        delete _service_looper;
    }

    void stopService()
    {
        _service_looper->stop();
    }
private:
    uint32_t _id;
    MessageQueue _service_queue;
    MessageHandler &_service_handler;
    MessageLooper *_service_looper;
    Poco::Thread thread1;
};

#endif // _MESSAGE_SERVICE_H_