#pragma once
#include "Message.h"
#include "MessengerHandler.h"
class TextProcessor
{
public:
	//static string urlGenerator(MessengerHandler*, Message);
	static char* textToUrlEncoder(string str);
private:
	static bool isCharUrlSafe(wchar_t);
};

