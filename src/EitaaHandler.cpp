#include <iostream>
#include "../include/EitaaHandler.h"

EitaaHandler::EitaaHandler(string chat_id, string messengerToken) : MessengerHandler()
{
	hnd = curl_easy_init();
	mime = curl_mime_init(hnd);
	part = curl_mime_addpart(mime);

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

void EitaaHandler::setMessengerToken(string token) { messengerToken = token; }

void EitaaHandler::setChatId(string chat_id) { this->chat_id = chat_id; }

//				getters				//

string EitaaHandler::getChatId() { return chat_id; }

Message EitaaHandler::getMessage() { return message; }

const string EitaaHandler::getApiEndpoint() { return apiEndpoint; }

string EitaaHandler::getMessengerToken() { return messengerToken; }

unordered_map <MessageType, vector<string>> EitaaHandler::getTypeAndParams() { return messageTypeAndParams; }

//				utilities				//

bool EitaaHandler::sendMessage(Message message = Message(), Footer footer = Footer())
{
	string generatedUrl;

	MessageType type = message.getType();
	auto search = messageTypeAndParams.find(type);


	if (search == messageTypeAndParams.end())
	{
		//The message type is not valid //raise exception or something similar
	}
	else
	{
		if (type == MessageType::Text)
		{
			generatedUrl = TextProcessor::urlGenerator(this, message);
		}
	}
}