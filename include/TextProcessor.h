#pragma once
#include "../include/Message.h"
#include "../include/MessengerHandler.h"
#include "../include/EitaaHandler.h"
class TextProcessor
{
public:
	static string urlGenerator(MessengerHandler*, Message);
	static char* textToUrlEncoder(const char*);
private:
	static bool isCharUrlSafe(char);
};

