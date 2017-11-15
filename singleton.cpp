#include "singleton.h"



Singleton::Singleton(int _width, int _height, double _ratio )
    :Width(_width),Height(_height),Ratio(_ratio)
{


    mIntroPage = addWidget(cpp14::make_unique<intro::Intro>());

    mIntroPage->mBody->EnterClicked().connect(this,&Singleton::initMainPage);

    auto device0 = addWidget(cpp14::make_unique<WText>("Large desktops and laptops"));
    auto device1 = addWidget(cpp14::make_unique<WText>("Landscape tablets and medium desktops"));
    auto device2 = addWidget(cpp14::make_unique<WText>("Portrait tablets and small desktops"));
    auto device3 = addWidget(cpp14::make_unique<WText>("Landscape phones and portrait tablets"));
    auto device4 = addWidget(cpp14::make_unique<WText>("Portrait phones and smaller"));


    device0->addStyleClass("device0");
    device1->addStyleClass("device1");
    device2->addStyleClass("device2");
    device3->addStyleClass("device3");
    device4->addStyleClass("device4");



}

void Singleton::initMainPage()
{
    clear();
    mDesktopMainPage = addWidget(cpp14::make_unique<MainPage::DesktopMainPage>(Width,Height,Ratio));

    WApplication::instance()->setBodyClass("rootBody");

}
