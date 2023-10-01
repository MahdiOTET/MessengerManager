#pragma once
#include <boost/format.hpp>
#include <unordered_map>
#include <curl/curl.h>
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
	//virtual const string getApiEndpoint();
	virtual string getMessengerToken();
	//virtual unordered_map <MessageType, vector<string>> getTypeAndParams();

	//			utilites			//

	virtual bool sendMessage(Message, Footer);

private:
	string chat_id;
	string messengerToken;
	const string apiEndpoint = "https://eitaayar.ir/api";

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
	curl_mimepart* part1;
	curl_mimepart* part2;
	//vector<curl_mimepart*>parts;
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

	//size_t writeCallback(char* buffer, size_t size, size_t nmemb, std::string* userData)
	//{
	//	size_t totalSize = size * nmemb;
	//	userData->append(buffer, totalSize);
	//	return totalSize;
	//}
};