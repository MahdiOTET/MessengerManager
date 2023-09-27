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
	Message(string, MessageType, deque<string>, vector<lableValuePair>, vector<lableValuePair>);
	//Set the cation or text of the message
	void setText(string);
	//Set the type of the message
	void setType(MessageType);
	//Push back a file path to the queue
	void filePushBack(string);
	//Push back a pair of the header lable and the value of header
	void headerPushBack(lableValuePair);
	//Push back a pair of the paramter lable and value of parameter
	void parameterPushBack(lableValuePair);
	
	//Get the cation or text of the message
	string getText();
	//Get the type of the message
	MessageType getType();
	//Get the files in a queue
	deque<string> getFiles();
	//Get the headers in a vector of pairs
	vector<lableValuePair> getHeaders();
	//Get the parameters in a vector of pairs
	vector<lableValuePair> getParameters();

private:
	string text;
	MessageType type;
	deque<string>files;
	vector<pair<string,string>>headers;
	vector<lableValuePair>parameters;
};

