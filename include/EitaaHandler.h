#pragma once
#include <unordered_map>
#include <curl/curl.h>
#include "Footer.h"
#include "Message.h"
#include "TextProcessor.h"
#include "MessengerHandler.h"
using std::unordered_map;

class EitaaHandler : public MessengerHandler
{
public :
	EitaaHandler();
	EitaaHandler(Message);
	virtual ~EitaaHandler();

	virtual bool sendMessage(Message, Footer);

	void setChatId(string);
	void setMessage(Message);
	void setMessengerToken(string);
	
	string getChatId();
	Message getMessage();
	string getMessengerToken();

private:
	string chat_id;
	string messengerToken;
	const unordered_map <MessageType, string> apiMethodNames;
	const string apiEndpoint = "https://eitaayar.ir/api/";

	CURL* hnd;
	CURLcode res;
	curl_mime* mime;
	curl_mimepart* part;
	long httpCode;
	
	Message message;
};