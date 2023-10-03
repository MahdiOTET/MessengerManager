#include "../include/BaleHandler.h"

BaleHandler::BaleHandler(string chat_id, string messengerToken)
{
	hnd = curl_easy_init();
	mime = curl_mime_init(hnd);

	setChatId(chat_id);
	setMessengerToken(messengerToken);
}

BaleHandler::~BaleHandler()
{
	curl_mime_free(mime);
	curl_easy_cleanup(hnd);
}

//				setters				//

void BaleHandler::setMessage(Message message) { this->message = message; }

void BaleHandler::setMessengerToken(string token) { this->messengerToken = token; }

void BaleHandler::setChatId(string chat_id) { this->chat_id = chat_id; }

//				getters				//

string BaleHandler::getChatId() { return chat_id; }

Message BaleHandler::getMessage() { return message; }

string BaleHandler::getMessengerToken() { return messengerToken; }

//				utilities				//

bool BaleHandler::sendMessage(Message message, Footer footer)
{
	string generatedUrl;
	string messageAndFooter;
	string response;
	MessageType type = message.getType();
	auto search = messageTypeAndParams.find(type);	//check and find the message type within the messageTypeAndParams

	if (search == messageTypeAndParams.end())	//if the message is not found then an exception is thrown 
	{
		throw std::invalid_argument{ "The message type is not valid" };
		/*
		paste it in main:
		catch(std::invalid_argument &err)
		{
			show a dialog box and get the error message from err.what();
		}
		*/
	}
	else
	{
		curl_easy_reset(hnd);
		messageAndFooter = TextProcessor::textToUrlEncoder(message.getText() + footer.getFooter());	//append the message and footer and encoded it
		generatedUrl = urlGenerator(messageAndFooter);	//generate a url from the encoded message and api endpoints
		curl_easy_setopt(hnd, CURLOPT_URL, generatedUrl.c_str());
		
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
			if (ok == "true")
			{
				return true;
			}
			else
			{
				throw std::invalid_argument{ "Bale bot token is not valid" };
				/*
				paste it in main:
				catch(std::invalid_argument &err)
				{
					show a dialog box and get the error message from err.what();
				}
				*/
			}
		}
		else if (type == MessageType::Text)
		{
			curl_easy_perform(hnd);
			result = json::parse(response);
			ok = result["ok"].dump();
			desc = result["description"].dump();
			if (ok != "true")
			{
				if (desc == "group not found")
				{
					throw std::invalid_argument{ "Bale channel id is not valid" };
				}
				else
				{
					throw std::runtime_error{ "An unexpected error accoured during upload to Telegram servers" };
				}
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

			if (desc == "group not found")
			{
				throw std::invalid_argument{ "Bale channel id is not valid" };
			}
			else
			{
				throw std::runtime_error{ "An unexpected error accoured during upload to Bale servers" };
			}
			return true;

		} //Todo fill the desc
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

			if (desc == "group not found")
			{
				throw std::invalid_argument{ "Bale channel id is not valid" };
			}
			else
			{
				throw std::runtime_error{ "An unexpected error accoured during upload to Bale servers" };
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

			if (desc == "group not found")
			{
				throw std::invalid_argument{ "Bale channel id is not valid" };
			}
			else
			{
				throw std::runtime_error{ "An unexpected error accoured during upload to Bale servers" };
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

		if (desc == "group not found")
		{
			throw std::invalid_argument{ "Bale channel id is not valid" };
		}
		else
		{
			throw std::runtime_error{ "An unexpected error accoured during upload to Bale servers" };
		}
		return true;

		}

	}
}
