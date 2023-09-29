#pragma once
#include "Message.h"
#include "MessengerHandler.h"
class TextProcessor
{
public:
	//static string urlGenerator(MessengerHandler*, Message);
	static char* textToUrlEncoder(const char*);
private:
	static bool isCharUrlSafe(char);
};

