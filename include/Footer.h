#pragma once
#include <string>
using std::string;

class Footer
{
public:
	Footer();
	Footer(string, string);
	void setFooter(string);
	string getFooter();
	void setFooterLable(string);
	string getFooterLable();
private:
	string footer;
	string footerLabel;
};

