#include "../include/Footer.h"

Footer::Footer() 
{
    footerLabel = "None";
    footer = "No footer text assigned";
}

Footer::Footer(string footer, string lable)
{
    setFooter(footer);
    setFooterLable(lable);
}

void Footer::setFooter(string footer)
{
    this->footer = "\n\n" + footer;
}

string Footer::getFooter()
{
    return footer;
}

void Footer::setFooterLable(string lable)
{
    footerLabel = lable;
}

string Footer::getFooterLable()
{
    return footerLabel;
}
