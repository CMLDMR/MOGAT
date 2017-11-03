#include "desktopmainpage.h"



MainPage::DesktopMainPage::DesktopMainPage()
{
    addWidget(cpp14::make_unique<Header>());

    addWidget(cpp14::make_unique<Footer>());
}

MainPage::Header::Header()
{
    setStyleClass("introheader");

    setContentAlignment(Wt::AlignmentFlag::Center);

    mLayout = setLayout(cpp14::make_unique<WHBoxLayout>());
    mLayout->setContentsMargins(0,0,0,0);


    mEUFlag = mLayout->addWidget(cpp14::make_unique<WImage>(WLink("/img/EurpanCommisionFlag.jpg")),0,Wt::AlignmentFlag::Right);

    auto mDevLayout = mLayout->addLayout(cpp14::make_unique<WVBoxLayout>());
    mDevLayout->addStretch(1);
    auto mTitle = mDevLayout->addWidget(cpp14::make_unique<WText>("Development of Innovation"),0,Wt::AlignmentFlag::Left);
    mTitle->setStyleClass("introDevelopment_of_Innovation");
    mDevLayout->addStretch(1);

    auto mflagLayout = mDevLayout->addLayout(cpp14::make_unique<WHBoxLayout>());

    int spaceWidth = 31;
    auto english = mflagLayout->addWidget(cpp14::make_unique<WImage>(WLink("img/flags/en.jpg")),0,Wt::AlignmentFlag::Left);
    english->setMaximumSize(46,28);
    mflagLayout->addSpacing(spaceWidth);
    auto turkish = mflagLayout->addWidget(cpp14::make_unique<WImage>(WLink("img/flags/tr.jpg")),0,Wt::AlignmentFlag::Left);
    turkish->setMaximumSize(46,28);
    mflagLayout->addSpacing(spaceWidth);
    auto italian = mflagLayout->addWidget(cpp14::make_unique<WImage>(WLink("img/flags/it.jpg")),0,Wt::AlignmentFlag::Left);
    italian->setMaximumSize(46,28);
    mflagLayout->addSpacing(spaceWidth);
    auto german = mflagLayout->addWidget(cpp14::make_unique<WImage>(WLink("img/flags/de.jpg")),0,Wt::AlignmentFlag::Left);
    german->setMaximumSize(46,28);
    mflagLayout->addStretch(1);

    english->decorationStyle().setCursor(Wt::Cursor::PointingHand);
    turkish->decorationStyle().setCursor(Wt::Cursor::PointingHand);
    italian->decorationStyle().setCursor(Wt::Cursor::PointingHand);
    german->decorationStyle().setCursor(Wt::Cursor::PointingHand);

    mLayout->addSpacing(150);


}

MainPage::Footer::Footer()
{
    setStyleClass("introfooter");
    auto mLayout = setLayout(cpp14::make_unique<WVBoxLayout>());
    auto mogatTitleText = mLayout->addWidget(cpp14::make_unique<WText>("Mogat"),0,Wt::AlignmentFlag::Center);
    mogatTitleText->setStyleClass("introMogatSubTitle");
    auto text = mLayout->addWidget(cpp14::make_unique<WText>(legalNoitice),0,Wt::AlignmentFlag::Center|Wt::AlignmentFlag::Bottom);
    text->setStyleClass("introlegalNotice");
    auto text2 = mLayout->addWidget(cpp14::make_unique<WText>("© 2017 MOGAT • powered by Wt & Qt & github"),0,Wt::AlignmentFlag::Center);
    text2->setStyleClass("introcopyRight");
}
