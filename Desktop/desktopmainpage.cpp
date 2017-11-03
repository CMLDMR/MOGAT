#include "desktopmainpage.h"



MainPage::DesktopMainPage::DesktopMainPage()
{
    addWidget(cpp14::make_unique<WText>("Main Page"));
}
