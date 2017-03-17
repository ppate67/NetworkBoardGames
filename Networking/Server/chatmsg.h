#ifndef CHATMSG_H
#define CHATMSG_H
#include "string"

using namespace std;
class ChatMsg
{
public:
    ChatMsg();
    string senderName;
    string receiverName;
    int senderID;
    int receiverID;
    string msgData;

};

#endif // CHATMSG_H
