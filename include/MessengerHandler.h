#pragma once

class MessengerHandler
{
public:
	MessengerHandler();
	virtual bool sendMessage(Message, Footer) = 0;
	virtual ~MessengerHandler() = 0;
};

