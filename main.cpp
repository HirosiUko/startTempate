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
    // std::map<std::string, std::string> salt;
    // if(PEPS_Networking::instance().request_owner_pairing_request(salt))
    // {
    //     std::cout << salt[W0] << std::endl;
    // }

    // hojune test
    Template::instance().doSomething();

    return 0;
}