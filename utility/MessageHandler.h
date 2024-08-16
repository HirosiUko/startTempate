#ifndef _PEPS_MESSAGE_HANDLER_
#define _PEPS_MESSAGE_HANDLER_

#include "Message.h"
#include "MessageQueue.h"
#include <Poco/Runnable.h>

class MessageHandler {
public:
    virtual void handleMessage(const Message& msg) = 0;
};

class MessageLooper : public Poco::Runnable {
public:
    MessageLooper(u_int32_t id, MessageQueue& queue, MessageHandler& handler)
        : _id(id), _queue(queue), _handler(handler), _stop(false) {}

    void run() override {
        while (!_stop) {
            Message msg = _queue.receiveMessage();
            _handler.handleMessage(msg);

            // if (_id == 1) {
            //     _queue.sendMessage({"Hello from Thread 1!", 1});
            // } else {
            //     _queue.sendMessage({"Hello from Thread 2!", 2});
            // }
        }
        // _handler._log("MessageLooper Thread " + std::to_string(_id) + " stopped");
        // std::cout << "MessageLooper Thread " << _id << " stopped" << std::endl;
    }

    void stop() {
        _stop = true;
        _queue.sendMessage_front({"kill MessageLooper Thread", 1});
    }

private:
    u_int32_t _id;
    MessageQueue& _queue;
    MessageHandler& _handler;
    bool _stop;
};

#endif // _PEPS_MESSAGE_HANDLER_