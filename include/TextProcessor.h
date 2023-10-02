#pragma once
#include "Message.h"
#include "MessengerHandler.h"
class TextProcessor
{
public:
	//static string urlGenerator(MessengerHandler*, Message);
	static char* textToUrlEncoder(string str);
	static size_t writeCallback(char* buffer, size_t size, size_t nmemb, std::string* userData);
	static bool verify(string plainText, string cipheredText);
	static string hash(string plainText);
private:
	static bool isCharUrlSafe(wchar_t ch);
	static string sha256(string plainText);
	
};





