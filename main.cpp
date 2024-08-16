#include <iostream>

#include <Poco/Runnable.h>
#include <Poco/Mutex.h>
#include <Poco/Condition.h>
#include <queue>
#include <string>
#include "utility/MessageHandler.h"
#include "network/PEPS_Networking.h"
#include "HJ_Template.h"

int main()
{
    // MessageQueue queue1, queue2;

    // MessageHandler handler;

    // MessageLooper looper1(1, queue1, handler);
    // MessageLooper looper2(2, queue2, handler);

    // Poco::Thread thread1;
    // Poco::Thread thread2;

    // thread1.start(looper1);
    // thread2.start(looper2);

    // queue1.sendMessage({"Hello from main thread to Thread 1!", 0});
    // queue2.sendMessage({"Hello from main thread to Thread 2!", 0});

    // Poco::Thread::sleep(2000);

    // looper1.stop();
    // looper2.stop();

    // thread1.join();
    // thread2.join();

    // std::map<std::string, std::string> salt;
    // if(PEPS_Networking::instance().request_owner_pairing_request(salt))
    // {
    //     std::cout << salt[W0] << std::endl;
    // }

    // hojune test
    Template::instance().doSomething();

    return 0;
}