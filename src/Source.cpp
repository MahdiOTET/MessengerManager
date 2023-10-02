#include <iostream>
#include <windows.h>
#include "../include/EitaaHandler.h"
#include "../include/TelegramHandler.h"
//using namespace std;
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include <codecvt>

int main()
{

	std::wstring ws = L"این یک تست است ";
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv1;
	std::string u8str = conv1.to_bytes(ws);

	Footer foot(u8str, "lable1");
	Message message;
	//message.filePushBack("C:/Users/Public/Pictures/Sample Pictures/Chrysanthemum.jpg");
	//message.filePushBack("C:/Users/Public/Pictures/Sample Pictures/Desert.jpg");
	message.filePushBack("C:/Users/Public/Pictures/Sample Pictures/Hydrangeas.jpg");
	//message.filePushBack("C:/Users/Public/Pictures/Sample Pictures/Jellyfish.jpg");
	//message.filePushBack("C:/Users/Public/Pictures/Sample Pictures/Koala.jpg");
	message.setText("This is a album");
	message.setType(MessageType::Text);

	EitaaHandler eHandler(string("Test_channell"), string("bot206108:0cf4e8e7-1300-4999-966d-7e2f4e13e849"));
	eHandler.setMessage(message);
	try
	{
		eHandler.sendMessage(message, foot);
	}
	catch (std::invalid_argument& err)
	{
		std::cout << err.what() << std::endl;
	}
	catch (std::runtime_error& err)
	{
		std::cout << err.what() << std::endl;
	}
	
	TelegramHandler tHandler(string("@test_channel_your"), string("6351217913:AAEIptkNU78Zz2f9IyZlTIR2ZSm_S9eFVEg"));
	tHandler.setMessage(message);
	try
	{
		tHandler.sendMessage(message, foot);

	}
	catch (std::invalid_argument& err)
	{
		std::cout << err.what() << std::endl;
	}
	catch (std::runtime_error& err)
	{
		std::cout << err.what() << std::endl;
	}
}