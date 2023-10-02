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
	auto search = messageTypeAndParams.find(type); //check and find the message type within the messageTypeAndParams

	

	if (search == messageTypeAndParams.end()) //if the message is not found then an exception is thrown 
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
		messageAndFooter = TextProcessor::textToUrlEncoder(message.getText() + footer.getFooter()); //append the message and footer and encoded it
		generatedUrl = urlGenerator(messageAndFooter); //generate a url from the encoded message and api endpoints
		curl_easy_setopt(hnd, CURLOPT_URL, generatedUrl.c_str()); //set the curl object's url
		
		/*store the api response into the response string*/
		curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, &TextProcessor::writeCallback);
		curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &response);
		json result;
		string ok;
		string desc;

		if (type == MessageType::Test) //Authorize the credentials
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
				desc = result["description"];
				if (desc == "Forbidden: user not access of channel chat")
				{
					throw std::invalid_argument{ "Eitaa channel id is not valid" };
					/*
					paste it in main:
					catch(std::invalid_argument &err)
					{
						show a dialog box and get the error message from err.what();
					}
					*/

				}
				else if (desc == "Unauthorized")
				{
					throw std::invalid_argument{ "Eitaa bot token is not valid" };
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
			
			if (ok != "true")
			{
				throw std::runtime_error{ "An unexpected error accoured during upload to Eitaa servers" };
				/*
				paste it in main:
				catch(std::runtime_error &err)
				{
					show a dialog box and get the error message from err.what();
				}
				*/
			}
			return true;
		}
		else
		{
			part = curl_mime_addpart(mime);
			curl_mime_name(part, "file");
			curl_mime_filedata(part, message.getFiles()[0].c_str());
			curl_easy_setopt(hnd, CURLOPT_MIMEPOST, mime);
			
			result = json::parse(response);
			ok = result["ok"].dump();
			desc = result["description"].dump();

			if (ok != "true")
			{
				throw std::runtime_error{ "An unexpected error accoured during upload to Eitaa servers" };
			}
			return true;
		}
	}
}