#ifndef _PEPS_MESSAGE_QUEUE_
#define _PEPS_MESSAGE_QUEUE_
#include <Poco/Condition.h>
#include "Message.h"

// MessageQueue
class MessageQueue {
public:
    void sendMessage(const Message& msg) {
        Poco::Mutex::ScopedLock lock(_mutex);
        _queue.push_back(msg);
        _condition.signal();
    }

    void sendMessage_front(const Message& msg) {
        Poco::Mutex::ScopedLock lock(_mutex);
        _queue.push_front(msg);
        _condition.signal();
    }

    Message receiveMessage() {
        Poco::Mutex::ScopedLock lock(_mutex);
        while (_queue.empty()) {
            _condition.wait(_mutex);
        }

        Message msg = _queue.front();
        _queue.pop_front();
        return msg;
    }

private:
    std::deque<Message> _queue;
    Poco::Mutex _mutex;
    Poco::Condition _condition;
};
#endif // _PEPS_MESSAGE_QUEUE_