#include "../include/TelegramHandler.h"

TelegramHandler::TelegramHandler(string chat_id, string messengerToken)
{
	hnd = curl_easy_init();
	mime = curl_mime_init(hnd);

	this->chat_id = chat_id;
	this->messengerToken = messengerToken;
}

TelegramHandler::~TelegramHandler()
{
	curl_mime_free(mime);
	curl_easy_cleanup(hnd);
}

//				setters				//

void TelegramHandler::setMessage(Message message) { this->message = message; }

void TelegramHandler::setMessengerToken(string messengerToken) { this->messengerToken = messengerToken; }

void TelegramHandler::setChatId(string chat_id) { this->chat_id = chat_id; }

//				getters				//

string TelegramHandler::getChatId() { return chat_id; }

Message TelegramHandler::getMessage() { return message; }

string TelegramHandler::getMessengerToken() { return messengerToken; }

//				utilities				//

bool TelegramHandler::sendMessage(Message message, Footer footer)
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

		switch (type)
		{
		case MessageType::Text:
			curl_easy_perform(hnd);

			//parse the response and notify the result (successful or failed)
			break;
		case MessageType::Photo:
			for (const auto& file : message.getFiles())
			{
				part = curl_mime_addpart(mime);
				curl_mime_name(part, "photo");
				curl_mime_filedata(part, file.c_str());
			}
			curl_easy_setopt(hnd, CURLOPT_MIMEPOST, mime);
			curl_easy_perform(hnd);
			break;
		case MessageType::Video:
			for (const auto& file : message.getFiles())
			{
				part = curl_mime_addpart(mime);
				curl_mime_name(part, "video");
				curl_mime_filedata(part, file.c_str());
			}
			curl_easy_setopt(hnd, CURLOPT_MIMEPOST, mime);
			curl_easy_perform(hnd);
			break;
		case MessageType::Audio:
			for (const auto& file : message.getFiles())
			{
				part = curl_mime_addpart(mime);
				curl_mime_name(part, "audio");
				curl_mime_filedata(part, file.c_str());
			}
			curl_easy_setopt(hnd, CURLOPT_MIMEPOST, mime);
			curl_easy_perform(hnd);
			break;
		case MessageType::Document:
			for (const auto& file : message.getFiles())
			{
				part = curl_mime_addpart(mime);
				curl_mime_name(part, "document");
				curl_mime_filedata(part, file.c_str());
			}
			curl_easy_setopt(hnd, CURLOPT_MIMEPOST, mime);
			curl_easy_perform(hnd);
			break;
		}
	}
	return false;
}
