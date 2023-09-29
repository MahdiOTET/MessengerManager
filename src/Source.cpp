#include <iostream>
#include <windows.h>
#include "../include/EitaaHandler.h"
#include "../include/TelegramHandler.h"
//using namespace std;
int main()
{
	char* s = (char*)"این یک تست است ";
	WCHAR utf8String[16];
	MultiByteToWideChar(CP_UTF8, 0, s, -1, utf8String, 16);
	
		
	Footer foot(utf8String, "lable1");
	Message message;
	//message.filePushBack("C:/Users/Public/Pictures/Sample Pictures/Chrysanthemum.jpg");
	//message.filePushBack("C:/Users/Public/Pictures/Sample Pictures/Desert.jpg");
	//message.filePushBack("C:/Users/Public/Pictures/Sample Pictures/Hydrangeas.jpg");
	message.filePushBack("C:/Users/Public/Pictures/Sample Pictures/Jellyfish.jpg");
	message.filePushBack("C:/Users/Public/Pictures/Sample Pictures/Koala.jpg");
	message.setText("This is a album");
	message.setType(MessageType::Photo);

	EitaaHandler eHandler(string("Test_channell"), string("bot206108:0cf4e8e7-1300-4999-966d-7e2f4e13e849"));
	eHandler.setMessage(message);
	eHandler.sendMessage(message, foot);
	
	TelegramHandler tHandler(string("@test_channel_your"), string("6351217913:AAEIptkNU78Zz2f9IyZlTIR2ZSm_S9eFVEg"));
	tHandler.setMessage(message);
	tHandler.sendMessage(message, foot);
}