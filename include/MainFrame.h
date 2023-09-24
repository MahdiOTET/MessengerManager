#pragma once
#include <wx/wx.h>
class MainFrame : public wxFrame
{
public:
	MainFrame(wxString);
private:
	void onEntryFocus(wxFocusEvent&);
	void sendClicked(wxCommandEvent&);
	static bool sendEitaaMessage();
	static bool sendTelegramMessage();
	static int isURLSafe(char);
	static char* urlEncode(const char*);
};

