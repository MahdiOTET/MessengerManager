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
	EitaaHandler(string, string);
	virtual ~EitaaHandler();


	void setMessage(Message);
	void setMessengerToken(string);
	void setChatId(string);

	string getChatId();
	Message getMessage();
	virtual const string getApiEndpoint();
	virtual string getMessengerToken();
	virtual unordered_map <MessageType, vector<string>> getTypeAndParams();


	virtual bool sendMessage(Message, Footer);
private:
	string chat_id;
	string messengerToken;
	const string apiEndpoint = "https://eitaayar.ir/api";
	//string urlFormat = 

	unordered_map <MessageType, vector<string>> messageTypeAndParams
	{
		{MessageType::Text, {"sendMessage", "chat_id", "text"}},
		{MessageType::Photo, {"sendFile", "chat_id", "caption"}},
		{MessageType::Video, {"sendFile", "chat_id", "caption"}},
		{MessageType::Audio, {"sendFile", "chat_id", "caption"}},
		{MessageType::Document, {"sendFile", "chat_id", "caption"}}
	};

	CURL* hnd;
	CURLcode res;
	curl_mime* mime;
	curl_mimepart* part;
	long httpCode;
	
	Message message;
};