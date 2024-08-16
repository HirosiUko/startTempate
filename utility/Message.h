#ifndef _PEPS_MESSAGE_
#define _PEPS_MESSAGE_
#include <string>
struct Message {
    std::string text;
    u_int32_t sender_id;
};
#endif // _PEPS_MESSAGE_