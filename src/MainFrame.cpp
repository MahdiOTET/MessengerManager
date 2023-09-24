#include <wx/wx.h>
#include "../include/MainFrame.h"
#include <curl/curl.h>
#include <string>
#include <stdlib.h>
using std::string;


MainFrame::MainFrame(wxString windowTitle) : wxFrame(NULL, wxID_ANY, windowTitle)
{
	wxPanel* panel = new wxPanel(this, wxID_ANY);
	//wxPanel* panel1 = new wxPanel(panel, wxID_ANY, wxPoint(300, 300));
	wxStaticText* eitaaTokenLable = new wxStaticText(panel, wxID_ANY, "Eitaa Token: ", wxPoint(60, 102));
	wxTextCtrl* eitaaTokenEntry = new wxTextCtrl(panel, wxID_ANY, "Enter your eitaa token", wxPoint(130, 100), wxSize(300, 20));
	//eitaaTokenEntry->Bind(wxEVT_SET_FOCUS, &MainFrame::onEntryFocus, this);
	wxStaticText* eitaaChannelLable = new wxStaticText(panel, wxID_ANY, "Channel Number Id: ", wxPoint(18, 132));
	wxTextCtrl* eitaaChannelEntry = new wxTextCtrl(panel, wxID_ANY, "Enter your eitaa channel number id", wxPoint(130, 130), wxSize(300, 20));
	//eitaaChannelEntry->Bind(wxEVT_SET_FOCUS, &MainFrame::onEntryFocus, this);

	wxStaticText* telegramTokenLable = new wxStaticText(panel, wxID_ANY, "Telegram Token: ", wxPoint(35, 202));
	wxTextCtrl* telegramTokenEntry = new wxTextCtrl(panel, wxID_ANY, "Enter your telegram token", wxPoint(130, 200), wxSize(300, 20));
	//telegramTokenEntry->Bind(wxEVT_SET_FOCUS, &MainFrame::onEntryFocus, this);

	wxStaticText* telegramChannelLable = new wxStaticText(panel, wxID_ANY, "Channel Number Id: ", wxPoint(18, 232));
	wxTextCtrl* telegramChannelEntry = new wxTextCtrl(panel, wxID_ANY, "Enter your telegram channel number id", wxPoint(130, 230), wxSize(300, 20));
	//telegramChannelEntry->Bind(wxEVT_SET_FOCUS, &MainFrame::onEntryFocus, this);

	wxButton* send = new wxButton(panel, wxID_ANY, "Send", wxPoint(200, 400), wxSize(100, 50), wxBU_EXACTFIT);
	send->Bind(wxEVT_BUTTON, &MainFrame::sendClicked, this);

	CreateStatusBar();
}

void MainFrame::onEntryFocus(wxFocusEvent& evt)
{}
void MainFrame::sendClicked(wxCommandEvent& evt)
{
	wxLogStatus("Send Progress has been started");
	wxLogStatus(u8"آزمایشگاه پژوهشی فضای سایبر");

	if(sendEitaaMessage())
		wxLogStatus("Eitaa message sent");

	

	if(sendTelegramMessage())
		wxLogStatus("Telegram message sent");

	

}

bool MainFrame::sendEitaaMessage()
{
	setlocale(LC_ALL, "fa_IR");
	CURLcode ret;
	CURL* hnd = curl_easy_init();;
	curl_mime* mime = curl_mime_init(hnd);;
	curl_mimepart* part = curl_mime_addpart(mime);
	long httpCode;

	string eitaaFileEndpoint = "https://eitaayar.ir/api/bot206108:0cf4e8e7-1300-4999-966d-7e2f4e13e849/sendFile\?";
	string chat_id = "chat_id=Test_channell&caption=";
	string caption = u8"آزمایشگاه پژوهشی فضای سایبر";

	string encoded = urlEncode(caption.c_str());
	eitaaFileEndpoint.append(chat_id).append(encoded);

	
	//curl_easy_setopt(hnd, CURLOPT_VERBOSE, 1L);
	curl_easy_setopt(hnd, CURLOPT_URL, eitaaFileEndpoint.c_str());
	
	curl_mime_filedata(part, "C:/Users/MahdiOTET/Desktop/Img.jpg");
	curl_mime_name(part, "file");
	curl_easy_setopt(hnd, CURLOPT_MIMEPOST, mime);

	ret = curl_easy_perform(hnd);
	curl_easy_getinfo(hnd, CURLINFO_RESPONSE_CODE, &httpCode);


	curl_easy_cleanup(hnd);
	curl_mime_free(mime);

	if (httpCode == 200)
		return true;
	return false;

}
bool MainFrame::sendTelegramMessage()
{
	CURLcode ret;
	CURL* hnd = curl_easy_init();;
	curl_mime* mime = curl_mime_init(hnd);
	curl_mimepart* part = curl_mime_addpart(mime);
	long httpCode;
	
	string caption = u8"آزمایشگاه پژوهشی فضای سایبر";
	string encoded = urlEncode(caption.c_str());

	string telegramApiEndpoint = "https://api.telegram.org/bot6351217913:AAEIptkNU78Zz2f9IyZlTIR2ZSm_S9eFVEg/";
	//string telegramBotToken = "";
	string telegramChannelId = "@test_channel_your&";
	//string query = telegramApiEndpoint.append(telegramBotToken).append("sendPhoto?");
	string query = telegramApiEndpoint.append("sendPhoto?");

	curl_easy_setopt(hnd, CURLOPT_URL, (query.append("chat_id=").append(telegramChannelId).append("caption=").append(encoded)).c_str());
	curl_mime_filedata(part, "C:/Users/MahdiOTET/Desktop/Img.jpg");
	curl_mime_name(part, "photo");
	curl_easy_setopt(hnd, CURLOPT_MIMEPOST, mime);

	ret = curl_easy_perform(hnd);
	curl_easy_getinfo(hnd, CURLINFO_RESPONSE_CODE, &httpCode);
	
	curl_easy_cleanup(hnd);
	curl_mime_free(mime);

	if (httpCode == 200)
		return true;
	return false;

}
int MainFrame::isURLSafe(char ch)
{
		if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') ||
			ch == '-' || ch == '_' || ch == '.' || ch == '~') 
		{
			return 1;
		}
		return 0;
}

char* MainFrame::urlEncode(const char* str)
{
	size_t len = strlen(str); // Length of the input string
	char* encoded = (char*)malloc(3 * len + 1); // Allocate memory for the encoded string

	size_t j = 0; // Index for the encoded string

	for (size_t i = 0; i < len; i++) 
	{
		if (isURLSafe(str[i])) 
		{
			encoded[j++] = str[i]; // Append safe characters as is
		}
		else 
		{
			// Encode unsafe characters
			sprintf(encoded + j, "%%%02X", (unsigned char)str[i]);
			j += 3;
		}
	}

	encoded[j] = '\0'; // Null-terminate the encoded string
	return encoded;
}