#pragma once
#include <boost/format.hpp>
#include <unordered_map>
#include <curl/curl.h>
#include <iostream>
#include "Footer.h"
#include "Message.h"
#include "TextProcessor.h"
#include "MessengerHandler.h"

using std::unordered_map;
using boost::format;

class TelegramHandler :  public MessengerHandler
{
public:
	TelegramHandler(string chat_id, string messengerToken);
	virtual ~TelegramHandler();
	
	//			setters			//

	void setMessage(Message message);
	void setMessengerToken(string token);
	void setChatId(string chat_id);
	
	//			getters			//

	string getChatId();
	Message getMessage();
	virtual string getMessengerToken();

	//			utilities			//

	virtual bool sendMessage(Message, Footer);

private:

	string chat_id;
	string messengerToken;
	const string apiEndpoint = "https://api.telegram.org/bot";

	unordered_map <MessageType, vector<string>> messageTypeAndParams
	{
		{MessageType::Test, {"getMe", "chat_id", "text"}},
		{MessageType::Text, {"sendMessage", "chat_id", "text"}},
		{MessageType::Photo, {"sendPhoto", "chat_id", "caption"}},//mimeName photo
		{MessageType::Video, {"sendVideo", "chat_id", "caption"}},//mimeName video
		{MessageType::Audio, {"sendAudio", "chat_id", "caption"}},//mimeName audio
		{MessageType::Document, {"sendDocument", "chat_id", "caption"}}//mimeName document
	};

	CURL* hnd;
	CURLcode res;
	curl_mime* mime;
	curl_mimepart* part;
	curl_mimepart* part1;
	curl_mimepart* part2;
	long httpCode;

	Message message;

	string urlGenerator(string messageAndFooter)
	{
		vector<string>params = messageTypeAndParams[message.getType()];
		auto generatedUrl = format("%1%%2%/%3%?%4%=%5%&%6%=%7%") % apiEndpoint
			% messengerToken
			% params[0]
			% params[1] % chat_id
			% params[2] % messageAndFooter;

		return str(generatedUrl);
	}
};

