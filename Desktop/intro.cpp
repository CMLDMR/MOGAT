#include "intro.h"

intro::Intro::Intro()
{

    setContentAlignment(Wt::AlignmentFlag::Center);

    auto mLayout = setLayout(cpp14::make_unique<WVBoxLayout>());

    mHeader = mLayout->addWidget(cpp14::make_unique<Header>());

//    mLayout->addSpacing(175);

    mBody = mLayout->addWidget(cpp14::make_unique<Body>(),0,Wt::AlignmentFlag::Middle);

//    mLayout->addStretch(1);

    mFooter = mLayout->addWidget(cpp14::make_unique<Footer>(),0,Wt::AlignmentFlag::Bottom);

    setStyleClass("introBody");
}

intro::Header::Header()
{

    setStyleClass("header");

//    decorationStyle().setBackgroundColor(WColor("#407077"));
    setContentAlignment(Wt::AlignmentFlag::Center);

    mLayout = setLayout(cpp14::make_unique<WHBoxLayout>());
    mLayout->setContentsMargins(0,0,0,0);


    mEUFlag = mLayout->addWidget(cpp14::make_unique<WImage>(WLink("/img/EurpanCommisionFlag.jpg")),0,Wt::AlignmentFlag::Right);

    auto mDevLayout = mLayout->addLayout(cpp14::make_unique<WVBoxLayout>());
    mDevLayout->addStretch(1);
    auto mTitle = mDevLayout->addWidget(cpp14::make_unique<WText>("Development of Innovation"),0,Wt::AlignmentFlag::Left);
    mTitle->setStyleClass("Development_of_Innovation");
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



intro::Body::Body()
{

    setContentAlignment(Wt::AlignmentFlag::Center);


    auto mLayout = setLayout(cpp14::make_unique<WVBoxLayout>());

    /// Logo ve MOGAT Text
    {
        auto mlogolayout = mLayout->addLayout(cpp14::make_unique<WHBoxLayout>());

        mlogolayout->addWidget(cpp14::make_unique<WImage>(WLink("img/Logo.png")),0,Wt::AlignmentFlag::Right);

        auto mlogoTextLayout = mlogolayout->addLayout(cpp14::make_unique<WVBoxLayout>());

        mlogoTextLayout->addStretch(1);
        auto text = mlogoTextLayout->addWidget(cpp14::make_unique<WText>("MOGAT"),0,Wt::AlignmentFlag::Left);
        text->setStyleClass("Mogat");
        mlogoTextLayout->addStretch(1);
    }


    {
        mLayout->addStretch(1);
        auto text = mLayout->addWidget(cpp14::make_unique<WText>("MOBILE TOOLS AND FAMIFICATION\nAS A NEW LANGUAGE ASSESSMENT SYSTEM IN TOURISM"),0,Wt::AlignmentFlag::Center);
        text->setStyleClass("mobileText");
    }

    {
        mLayout->addStretch(1);
        auto text = mLayout->addWidget(cpp14::make_unique<WText>("ENTER"));
        text->setStyleClass("enter");
    }
//    mLayout->addSpacing(10);
}



intro::Footer::Footer()
{
    setStyleClass("introfooter");

    auto mLayout = setLayout(cpp14::make_unique<WVBoxLayout>());

    auto mogatTitleText = mLayout->addWidget(cpp14::make_unique<WText>("Mogat"),0,Wt::AlignmentFlag::Center);
    mogatTitleText->setStyleClass("introMogatSubTitle");

    auto text = mLayout->addWidget(cpp14::make_unique<WText>(legalNoitice),0,Wt::AlignmentFlag::Center|Wt::AlignmentFlag::Bottom);

    text->setStyleClass("legalNotice");

    auto text2 = mLayout->addWidget(cpp14::make_unique<WText>("© 2017 MOGAT • powered by Wt & Qt & github"),0,Wt::AlignmentFlag::Center);

    text2->setStyleClass("introcopyRight");


}
