#include <cstdio>
#include <string>
#include "../include/TextProcessor.h"
#pragma warning (disable:4996)

char* TextProcessor::textToUrlEncoder(const char* str)
{
	size_t len = strlen(str); // Length of the input string
	char* encoded = (char*)malloc(3 * len + 1); // Allocate memory for the encoded string

	size_t j = 0; // Index for the encoded string

	for (size_t i = 0; i < len; i++)
	{
		if (isCharUrlSafe(str[i]))
		{
			encoded[j++] = str[i]; // Append safe characters as is
		}
		else
		{
			// Encode unsafe characters
			sprintf(encoded + j, "%%%02X", (unsigned char)str[i]);
			j += 3;
		}
	}

	encoded[j] = '\0'; // Null-terminate the encoded string
	return encoded;

}

bool TextProcessor::isCharUrlSafe(char ch)
{
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') ||
		ch == '-' || ch == '_' || ch == '.' || ch == '~')
	{
		return true;
	}
	return false;
}
