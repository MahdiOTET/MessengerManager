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
	auto search = messageTypeAndParams.find(type);	//check and find the message type within the messageTypeAndParams





	if (search == messageTypeAndParams.end())	//if the message is not found then an exception is thrown 
	{
		throw std::invalid_argument{ "The message type is not valid" };
		//The message type is not valid //raise exception or something similar
	}
	else
	{
		curl_easy_reset(hnd);
		messageAndFooter = TextProcessor::textToUrlEncoder(message.getText() + footer.getFooter()); //append the message and footer and encoded it
		generatedUrl = urlGenerator(messageAndFooter); //generate a url from the encoded message and api endpoints
		curl_easy_setopt(hnd, CURLOPT_URL, generatedUrl.c_str()); //set the curl object's url

		/*store the api response into the response string*/
		curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, &TextProcessor::writeCallback);
		curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &response);

		json result;
		string ok;
		string desc;
		if (type == MessageType::Test)
		{
			curl_easy_perform(hnd);
			result = json::parse(response);
			ok = result["ok"].dump();
			desc = result["description"].dump();

			if (ok == "true")
			{
				return true;
			}
			else
			{
				if (desc == "Unauthorized")
				{
					throw std::invalid_argument{ "Telegram bot token is not valid" };
					/*
					paste it in main:
					catch(std::invalid_argument &err)
					{
						show a dialog box and get the error message from err.what();
					}
					*/
				}
			}
		}
		else if (type == MessageType::Text)
		{
			curl_easy_perform(hnd);
			result = json::parse(response);
			ok = result["ok"].dump();
			desc = result["description"].dump();

			if (desc == "Bad Request : chat not found")
			{
				throw std::invalid_argument{ "Telegram channel id is not valid" };
			}
			else if (ok != "true")
			{
				throw std::runtime_error{ "An unexpected error accoured during upload to Telegram servers" };
			}
			return true;
		}
		else if (type == MessageType::Photo)
		{
			part = curl_mime_addpart(mime);
			curl_mime_name(part, "photo");
			curl_mime_filedata(part, message.getFiles()[0].c_str());
			curl_easy_setopt(hnd, CURLOPT_MIMEPOST, mime);

			curl_easy_perform(hnd);
			result = json::parse(response);
			ok = result["ok"].dump();
			desc = result["description"].dump();

			if (desc == "Bad Request : chat not found")
			{
				throw std::invalid_argument{ "Telegram channel id is not valid" };
			}
			else if (ok != "true")
			{
				throw std::runtime_error{ "An unexpected error accoured during upload to Telegram servers" };
			}
			return true;
		}
		else if (type == MessageType::Video)
		{
			part = curl_mime_addpart(mime);
			curl_mime_name(part, "video");
			curl_mime_filedata(part, message.getFiles()[0].c_str());
			curl_easy_setopt(hnd, CURLOPT_MIMEPOST, mime);

			curl_easy_perform(hnd);
			result = json::parse(response);
			ok = result["ok"].dump();
			desc = result["description"].dump();

			if (desc == "Bad Request : chat not found")
			{
				throw std::invalid_argument{ "Telegram channel id is not valid" };
			}
			else if (ok != "true")
			{
				throw std::runtime_error{ "An unexpected error accoured during upload to Telegram servers" };
			}
			return true;
		}
		else if (type == MessageType::Audio)
		{
			part = curl_mime_addpart(mime);
			curl_mime_name(part, "audio");
			curl_mime_filedata(part, message.getFiles()[0].c_str());
			curl_easy_setopt(hnd, CURLOPT_MIMEPOST, mime);
			
			curl_easy_perform(hnd);
			result = json::parse(response);
			ok = result["ok"].dump();
			desc = result["description"].dump();

			if (desc == "Bad Request : chat not found")
			{
				throw std::invalid_argument{ "Telegram channel id is not valid" };
			}
			else if (ok != "true")
			{
				throw std::runtime_error{ "An unexpected error accoured during upload to Telegram servers" };
			}
			return true;
		}
		else if (type == MessageType::Document)
		{
			part = curl_mime_addpart(mime);
			curl_mime_name(part, "document");
			curl_mime_filedata(part, message.getFiles()[0].c_str());
			curl_easy_setopt(hnd, CURLOPT_MIMEPOST, mime);
			
			curl_easy_perform(hnd);
			result = json::parse(response);
			ok = result["ok"].dump();
			desc = result["description"].dump();

			if (desc == "Bad Request : chat not found")
			{
				throw std::invalid_argument{ "Telegram channel id is not valid" };
			}
			else if (ok != "true")
			{
				throw std::runtime_error{ "An unexpected error accoured during upload to Telegram servers" };
			}
			return true;
		}

	}
}
