#pragma once
#include "Message.h"
#include "MessengerHandler.h"
class TextProcessor
{
public:
	//static string urlGenerator(MessengerHandler*, Message);
	static char* textToUrlEncoder(string str);
	static size_t writeCallback(char* buffer, size_t size, size_t nmemb, std::string* userData);
private:
	static bool isCharUrlSafe(wchar_t ch);
};

