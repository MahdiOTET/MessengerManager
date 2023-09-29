#include "../include/Message.h"

Message::Message() { text = "No text assigned!!"; }
Message::Message(string text,
		MessageType type,
		deque<string>files,
		vector<lableValuePair>headers)
{
	this->text = text;
	this->type = type;
	this->files = files;
	this->headers = headers;
}
//				setters				//
void Message::setText(string text) { this->text = text; }

void Message::setType(MessageType type) { this->type = type; }

void Message::filePushBack(string file) { files.push_back(file); }

void Message::headerPushBack(lableValuePair header) { headers.push_back(header); }


//				getters				//

string Message::getText() { return text; }

MessageType Message::getType() { return type; }

deque<string> Message::getFiles() { return files; }

vector<lableValuePair> Message::getHeaders() { return headers; }
