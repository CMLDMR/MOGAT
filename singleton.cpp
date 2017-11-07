#include "singleton.h"



Singleton::Singleton(int _width, int _height, double _ratio )
    :Width(_width),Height(_height),Ratio(_ratio)
{

    setMinimumSize(WLength::Auto,Height);

    mIntroPage = addWidget(cpp14::make_unique<intro::Intro>(Width,Height,Ratio));

    mIntroPage->mBody->EnterClicked().connect(this,&Singleton::initMainPage);


}

void Singleton::initMainPage()
{
    clear();

    mDesktopMainPage = addWidget(cpp14::make_unique<MainPage::DesktopMainPage>(Width,Height,Ratio));
}
