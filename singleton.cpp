#include "singleton.h"



Singleton::Singleton(int _width, int _height)
    :Width(_width),Height(_height)
{

    setMinimumSize(WLength::Auto,Height);

    mIntroPage = addWidget(cpp14::make_unique<intro::Intro>(Width,Height));

    mIntroPage->mBody->EnterClicked().connect(this,&Singleton::initMainPage);


}

void Singleton::initMainPage()
{
    clear();
    mDesktopMainPage = addWidget(cpp14::make_unique<MainPage::DesktopMainPage>());
}
