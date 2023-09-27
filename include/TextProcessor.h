#pragma once
class TextProcessor
{
public:
	static char* textToUrlEncoder(const char*);
private:
	static bool isCharUrlSafe(char);
};

