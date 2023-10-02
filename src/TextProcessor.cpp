#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <iomanip>
#include <openssl/evp.h>
#include "../include/TextProcessor.h"
#pragma warning (disable:4996)

char* TextProcessor::textToUrlEncoder(string str)
{
	size_t len = str.size(); // Length of the input string
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

bool TextProcessor::isCharUrlSafe(wchar_t ch)
{
	if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') ||
		ch == '-' || ch == '_' || ch == '.' || ch == '~')
	{
		return true;
	}
	return false;
}


size_t TextProcessor::writeCallback(char* buffer, size_t size, size_t nmemb, std::string* userData)
	{
		size_t totalSize = size * nmemb;
		userData->append(buffer, totalSize);
		return totalSize;
	}


string TextProcessor::hash(string plainText)
{
	string hashedPassword = sha256(plainText);

	return hashedPassword;
}

string TextProcessor::sha256(string plainText)

{
	string input = plainText;
	unsigned char hash[EVP_MAX_MD_SIZE];
	unsigned int hash_len;

	EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
	EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);
	EVP_DigestUpdate(mdctx, input.c_str(), input.length());
	EVP_DigestFinal_ex(mdctx, hash, &hash_len);
	EVP_MD_CTX_free(mdctx);

	string hashedPlainText;

	for (unsigned int i = 0; i < hash_len; i++)
	{
		char buf[3];
		sprintf_s(buf, "%02x", hash[i]);
		hashedPlainText += buf;
	}

	return hashedPlainText;
}

bool TextProcessor::verify(string plainText, string cipheredText)
{
	string hashedPlainText = sha256(plainText);

	return hashedPlainText == cipheredText;
}