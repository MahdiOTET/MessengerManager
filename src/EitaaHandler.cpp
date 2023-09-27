//#include <curl/curl.h>
#include "../include/EitaaHandler.h"

EitaaHandler::EitaaHandler() : MessengerHandler()
{
	hnd = curl_easy_init();
	mime = curl_mime_init(hnd);
	part = curl_mime_addpart(mime);
}

EitaaHandler::EitaaHandler(Message message) : EitaaHandler() { this->message = message; }

EitaaHandler::~EitaaHandler()
{
	curl_mime_free(mime);
	curl_easy_cleanup(hnd);
}

bool EitaaHandler::sendMessage(Message message = Message(), Footer footer = Footer())
{
	
}