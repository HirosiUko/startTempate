#include <Poco/Logger.h>
#include <Poco/AutoPtr.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/FormattingChannel.h>
#include <Poco/PatternFormatter.h>

#include "PEPS_Networking.h"
#include <Poco/URI.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/StreamCopier.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Stringifier.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Exception.h>

#define LOG "PEPS_Networking"

Poco::Logger &PEPS_Networking::logger()
{
    static Poco::AutoPtr<Poco::ConsoleChannel> pConsoleChannel(new Poco::ConsoleChannel);
    static Poco::AutoPtr<Poco::PatternFormatter> pFormatter(new Poco::PatternFormatter);
    pFormatter->setProperty("pattern", "%Y-%m-%d %H:%M:%S %s: %t");
    static Poco::AutoPtr<Poco::FormattingChannel> pFC(new Poco::FormattingChannel(pFormatter, pConsoleChannel));
    static Poco::Logger &logger = Poco::Logger::create(LOG, pFC, Poco::Message::PRIO_INFORMATION);
    return logger;
}

bool PEPS_Networking::request_https(const std::string &url, std::string &result)
{
    logger().information("😊😊");
    logger().debug("Request URL: %s", url);
    try
    {
        Poco::URI uri(url); // 테스트를 위한 URL
        std::string path(uri.getPathAndQuery());
        if (path.empty())
            path = "/";

        Poco::Net::HTTPSClientSession session(uri.getHost(), uri.getPort());

        // Poco::JSON::Object::Ptr json = new Poco::JSON::Object();
        // json->set("name", "42dot");
        // std::stringstream jsonStream;
        // Poco::JSON::Stringifier::stringify(json, jsonStream);
        // std::string jsonString = jsonStream.str();

        // create HTTP POST request  
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, path, Poco::Net::HTTPMessage::HTTP_1_1);
        request.setContentType("application/json");
        // request.setContentLength(jsonString.length());

        // add json string to request body
        std::ostream &os = session.sendRequest(request);
        // os << jsonString;

        Poco::Net::HTTPResponse response;
        std::istream &rs = session.receiveResponse(response);
        logger().information("Response status: [%d] %s", int(response.getStatus()), response.getReason());

        std::stringstream responseStream;
        Poco::StreamCopier::copyStream(rs, responseStream);
        logger().information("Response body: %s", responseStream.str());

        result = responseStream.str();

        return true;
    }
    catch (Poco::Exception &ex)
    {
        logger().error("Poco exception: %s", ex.displayText());
        result = ex.displayText();
        return false;
    }
    catch (std::exception &ex)
    {
        logger().error("Standard exception: %s", ex.what());
        result = ex.what();
        return false;
    }
}

bool PEPS_Networking::parse_owner_pairing_json(std::string &json, std::map<std::string, std::string> &result)
{
    try
    {
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var parser_result = parser.parse(Poco::trim(json));
        Poco::JSON::Object::Ptr jsonObject = parser_result.extract<Poco::JSON::Object::Ptr>();

        result[W0] = jsonObject->getValue<std::string>(W0);
        result[LX] = jsonObject->getValue<std::string>(LX);
        result[LY] = jsonObject->getValue<std::string>(LY);
    }
    catch (Poco::Exception &ex)
    {
        logger().error("Poco exception: %s %d", ex.displayText(), ex.code());
        return false;
    }
    catch (std::exception &ex)
    {
        logger().error("Standard exception: %s", ex.what());
        return false;
    }
    return true;
}
