#pragma once
#include <string>
using std::string;

class Footer
{
public:
	Footer();
	Footer(string footerText, string footerLable);
	void setFooter(string footerText);
	string getFooter();
	void setFooterLable(string footerLable);	
	string getFooterLable();
private:
	string footer;
	string footerLabel;
};

