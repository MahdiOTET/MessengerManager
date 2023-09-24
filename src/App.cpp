#include "../include/App.h"
#include "../include/MainFrame.h"
#include <locale>

wxIMPLEMENT_APP(App);
//#define wxUSE_UNICODE_UTF8;

bool App::OnInit()
{
	setlocale(LC_ALL, "fa_IR");
	std::string c = u8"آزمایشگاه پژوهشی فضای سایبر";
	MainFrame* mainFrame = new MainFrame("Messenger Manager Panel");
	mainFrame->SetClientSize(500, 600);
	mainFrame->Center();
	mainFrame->Show();
	return true;
}

