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

class BaleHandler : public MessengerHandler
{
public:
	BaleHandler(string chat_id, string messengerToken);
	virtual ~BaleHandler();

	//			setters			//
	void setMessage(Message message);
	void setMessengerToken(string token);
	void setChatId(string chat_id);

	//			getters			//

	string getChatId();
	Message getMessage();
	virtual string getMessengerToken();

	//			utilites			//

	virtual bool sendMessage(Message, Footer);

private:
	string chat_id;
	string messengerToken;
	const string apiEndpoint = "https://tapi.bale.ai";

	unordered_map <MessageType, vector<string>> messageTypeAndParams
	{
		{MessageType::Test, {"getMe","chat_id","text"}},
		{MessageType::Text, {"sendMessage", "chat_id", "text"}},
		{MessageType::Photo, {"sendPhoto", "chat_id", "caption"}},
		{MessageType::Video, {"sendVideo", "chat_id", "caption"}},
		{MessageType::Audio, {"sendAudio", "chat_id", "caption"}},
		{MessageType::Document, {"sendDocument", "chat_id", "caption"}}
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
		auto generatedUrl = format("%1%/bot%2%/%3%?%4%=%5%&%6%=%7%") % apiEndpoint
			% messengerToken
			% params[0]
			% params[1] % chat_id
			% params[2] % messageAndFooter;

		return str(generatedUrl);
	}
};

