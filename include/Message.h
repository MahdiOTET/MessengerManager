#pragma once
#include <vector>
#include <deque>
#include <string>
#include "../include/MessageType.h"

using std::pair;
using std::deque;
using std::vector;
using std::string;
typedef pair<string, string> lableValuePair;

class Message
{
public:
	
	Message();
	Message(string text,
		MessageType type,
		deque<string>files = deque<string>(),
		vector<lableValuePair>headers = vector<lableValuePair>());

	void setText(string);
	//Set the type of the message
	void setType(MessageType);
	//Push back a file path to the queue
	void filePushBack(string);
	//Push back a pair of the header lable and the value of header
	void headerPushBack(lableValuePair);
	
	//Get the cation or text of the message
	string getText();
	//Get the type of the message
	MessageType getType();
	//Get the files in a queue
	deque<string> getFiles();
	//Get the headers in a vector of pairs
	vector<lableValuePair> getHeaders();


private:
	string text;
	MessageType type;
	deque<string>files;
	vector<pair<string,string>>headers;
};