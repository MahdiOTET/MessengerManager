#pragma once
#include <boost/format.hpp>
#include <unordered_map>
#include <curl/curl.h>
#include <stdexcept>
#include <iostream>
#include "Footer.h"
#include "Message.h"
#include "TextProcessor.h"
#include "MessengerHandler.h"
using std::unordered_map;
using boost::format;
class EitaaHandler : public MessengerHandler
{
public :
	EitaaHandler(string chat_id, string messengerToken);
	virtual ~EitaaHandler();

	//			setters			//
	void setMessage(Message message);
	void setMessengerToken(string token);
	void setChatId(string chat_id);

	//			getters			//

	string getChatId();
	Message getMessage();
	virtual string getMessengerToken();

	//			utilites			//

	virtual bool sendMessage(Message message, Footer footer);

private:
	string chat_id;
	string messengerToken;
	const string apiEndpoint = "https://eitaayar.ir/api";

	unordered_map <MessageType, vector<string>> messageTypeAndParams
	{
		{MessageType::Test, {"getMe", "chat_id", "text"}},
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

	string urlGenerator(string messageAndFooter)
	{
		vector<string>params = messageTypeAndParams[message.getType()];
		auto generatedUrl = format("%1%/%2%/%3%?%4%=%5%&%6%=%7%") % apiEndpoint
			% messengerToken
			% params[0]
			% params[1] % chat_id
			% params[2] % messageAndFooter;

			return str(generatedUrl);
	}

	
};