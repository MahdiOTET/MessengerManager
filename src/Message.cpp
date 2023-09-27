#include "../include/Message.h"

Message::Message() { text = "No message text assigned"; }

Message::Message(string text, MessageType type
	, deque<string>files = deque<string>()
	, vector<lableValuePair>headers = vector<lableValuePair>()
	, vector<lableValuePair>parameters = vector<lableValuePair>())
{
	this->text = text;
	this->type = type;
	this->files = files;
	this->headers = headers;
	this->parameters = parameters;
}
//				setters				//
void Message::setText(string text) { this->text = text; }

void Message::setType(MessageType type) { this->type = type; }

void Message::filePushBack(string file) { files.push_back(file); }

void Message::headerPushBack(lableValuePair header) { headers.push_back(header); }

void Message::parameterPushBack(lableValuePair parameter) { parameters.push_back(parameter); }

//				getters				//

string Message::getText() { return text; }

MessageType Message::getType() { return type; }

deque<string> Message::getFiles() { return files; }

vector<lableValuePair> Message::getHeaders() { return headers; }

vector<lableValuePair> Message::getParameters() { return parameters; }




