#pragma once
#include "Footer.h"
#include "json.hpp"
#include <unordered_map>
using std::unordered_map;
using json = nlohmann::json;
class MessengerHandler
{
public:
	MessengerHandler() {}
	//virtual const string getApiEndPoint() = 0;
	virtual string getMessengerToken() = 0;
	//virtual unordered_map<MessageType, string> getApiMethodNames() = 0;
	virtual bool sendMessage(Message, Footer) = 0;
	virtual ~MessengerHandler() {}
};

