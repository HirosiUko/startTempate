#ifndef PEPS_NETWORKING_H
#define PEPS_NETWORKING_H
#include <Poco/SingletonHolder.h>
#include <Poco/Logger.h>

#define TEST_URL "https://peps-peps-server.stage.42dot.io/vehicle/v1/system/did:dm:42dot:system:mccoy:m312m0t:AK71005B80E828F31F8/owner-pairing/params"
#define W0 "W0"
#define LX "Lx"
#define LY "Ly"

class PEPS_Networking
{
public:
    static PEPS_Networking &instance()
    {
        static Poco::SingletonHolder<PEPS_Networking> sh;
        return *sh.get();
    }

    bool request_owner_pairing_request(std::map<std::string, std::string> &salt){
        std::string result="";
        if(false == request_https(TEST_URL, result)){
            return false;
        }
        if(parse_owner_pairing_json(result, salt)){ 
            return true;
        } 
        return false;
    };

private:
    Poco::Logger &logger();
    bool request_https(const std::string &url, std::string &result);
    bool parse_owner_pairing_json(std::string &json, std::map<std::string, std::string> &result);

    PEPS_Networking()
    {
        logger().information("PEPS_Networking Constructor");
    }

    ~PEPS_Networking()
    {
        logger().information("PEPS_Networking Destructor");
    }

    PEPS_Networking(const PEPS_Networking &) = delete;
    PEPS_Networking &operator=(const PEPS_Networking &) = delete;

    friend class Poco::SingletonHolder<PEPS_Networking>;
};

#endif // PEPS_NETWORKING_H