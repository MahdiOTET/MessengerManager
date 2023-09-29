#include <iostream>
#include "../include/EitaaHandler.h"

EitaaHandler::EitaaHandler(string chat_id, string messengerToken)
{
	hnd = curl_easy_init();
	mime = curl_mime_init(hnd);

	this->chat_id = chat_id;
	this->messengerToken = messengerToken;
}

//EitaaHandler::EitaaHandler(Message message) : EitaaHandler() { this->message = message; }

EitaaHandler::~EitaaHandler()
{
	curl_mime_free(mime);
	curl_easy_cleanup(hnd);
}

//				setters				//

void EitaaHandler::setMessage(Message message) { this->message = message; }

void EitaaHandler::setMessengerToken(string messengerToken) { this->messengerToken = messengerToken; }

void EitaaHandler::setChatId(string chat_id) { this->chat_id = chat_id; }

//				getters				//

string EitaaHandler::getChatId() { return chat_id; }

Message EitaaHandler::getMessage() { return message; }

//const string EitaaHandler::getApiEndpoint() { return apiEndpoint; }

string EitaaHandler::getMessengerToken() { return messengerToken; }

//unordered_map <MessageType, vector<string>> EitaaHandler::getTypeAndParams() { return messageTypeAndParams; }

//				utilities				//

bool EitaaHandler::sendMessage(Message message, Footer footer)
{
	string generatedUrl;
	string messageAndFooter;
	string response;
	MessageType type = message.getType();
	auto search = messageTypeAndParams.find(type);

	

	if (search == messageTypeAndParams.end())
	{
		//The message type is not valid //raise exception or something similar
	}
	else
	{
		curl_easy_reset(hnd);
		messageAndFooter = TextProcessor::textToUrlEncoder((message.getText() + footer.getFooter()).c_str()); //append the message and footer and encoded it
		generatedUrl = urlGenerator(messageAndFooter); //generate a url from the encoded message and api endpoints
		curl_easy_setopt(hnd, CURLOPT_URL, generatedUrl.c_str());
		if (type == MessageType::Text)
		{
			curl_easy_setopt(hnd, CURLOPT_VERBOSE, 1L);
			//curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, &writeCallback);
			//curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &response);
			curl_easy_perform(hnd);
			//std::cout << response << std::endl;
			//parse the response and notify the result (successful or failed)

		}
		else
		{
			//messageAndFooter = TextProcessor::textToUrlEncoder((message.getText() + footer.getFooter()).c_str());
			//generatedUrl = urlGenerator(messageAndFooter);
			//curl_easy_setopt(hnd, CURLOPT_URL, generatedUrl.c_str());
			curl_easy_setopt(hnd, CURLOPT_VERBOSE, 1L);
			//curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, writeCallback);
			//curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &response);
			for (const auto &file : message.getFiles())
			{
				part = curl_mime_addpart(mime);
				curl_mime_name(part, "file");
				curl_mime_filedata(part, file.c_str());
			}
			curl_easy_setopt(hnd, CURLOPT_MIMEPOST, mime);
			curl_easy_perform(hnd);
		}
	}
	return false;
}