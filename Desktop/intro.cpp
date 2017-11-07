#include "intro.h"

intro::Intro::Intro(int _w, int _h, double _ratio)
    :width(_w),
      height(_h),
      ratio(_ratio)
{

    setContentAlignment(Wt::AlignmentFlag::Center);
    auto mLayout = setLayout(cpp14::make_unique<WVBoxLayout>());
    mHeader = mLayout->addWidget(cpp14::make_unique<Header>(ratio));
    mBody = mLayout->addWidget(cpp14::make_unique<Body>(width,height),0,Wt::AlignmentFlag::Middle);
    mFooter = mLayout->addWidget(cpp14::make_unique<Footer>(),0,Wt::AlignmentFlag::Bottom);
    setStyleClass("introMain");
}




intro::Header::Header(double _ratio)
{

    mLayout = setLayout(cpp14::make_unique<WHBoxLayout>());
    mLayout->setContentsMargins(0,0,0,0);




    auto MainContainer = mLayout->addWidget(cpp14::make_unique<WContainerWidget>());

    setStyleClass("introheader");

//    document.getElementById("myP").style.fontSize = "xx-large";








    auto mSubLayout = MainContainer->setLayout(cpp14::make_unique<WHBoxLayout>());
    mSubLayout->setContentsMargins(0,0,0,0);


    mEUFlag = mSubLayout->addWidget(cpp14::make_unique<WImage>(WLink("/img/EurpanCommisionFlag.jpg")),0,Wt::AlignmentFlag::Right);

    auto mDevLayout = mSubLayout->addLayout(cpp14::make_unique<WVBoxLayout>(),0,Wt::AlignmentFlag::Left);
    auto mTitle = mDevLayout->addWidget(cpp14::make_unique<WText>("Development of Innovation"),0,Wt::AlignmentFlag::Center);
    mTitle->setStyleClass("introDevelopment_of_Innovation");
    QString str = QString("var title = document.getElementById(\"%1\");"
                          "title.style.fontSize = \"%2px\";"
                          "console.log(title.style.fontSize);"
                          "console.log(%3);").arg(mTitle->id().c_str()).arg(_ratio*18).arg(_ratio).toStdString().c_str();

    std::cout << "Ratio: " << _ratio << std::endl;
    std::cout << str.toStdString() << std::endl;

    mTitle->doJavaScript(str.toStdString());


    auto mflagWidget = mDevLayout->addWidget(cpp14::make_unique<FlagWidget>(),1,Wt::AlignmentFlag::Justify);

}






intro::Body::Body(int _w, int _h)
    :Width(_w),
      Height(_h)
{

    setId("introBody");

    setStyleClass("introBody");
    setMinimumSize( WLength::Auto , _h-138-100 );
    std::cout << "W: " << Width << "Height : " << Height << std::endl;

    setMargin(WLength::Auto,Wt::AllSides);

    setContentAlignment(Wt::AlignmentFlag::Center|Wt::AlignmentFlag::Middle);
    auto mLayout = setLayout(cpp14::make_unique<WVBoxLayout>());

    mLayout->addStretch(1);

    {
        auto mlogolayout = mLayout->addLayout(cpp14::make_unique<WHBoxLayout>(),0,Wt::AlignmentFlag::Middle);
        auto logoimg = mlogolayout->addWidget(cpp14::make_unique<WImage>(WLink("img/Logo1.png")),0,Wt::AlignmentFlag::Right);

        auto mlogoTextLayout = mlogolayout->addLayout(cpp14::make_unique<WVBoxLayout>());
        mlogoTextLayout->addStretch(1);
        auto text = mlogoTextLayout->addWidget(cpp14::make_unique<WText>("MOGAT"),0,Wt::AlignmentFlag::Left);
        text->setStyleClass("introMogat");
        mlogoTextLayout->addStretch(1);
    }

    {
        auto text = mLayout->addWidget(cpp14::make_unique<WText>("MOBILE TOOLS AND GAMIFICATION\nAS A NEW LANGUAGE ASSESSMENT SYSTEM IN TOURISM"),0,Wt::AlignmentFlag::Center|Wt::AlignmentFlag::Middle);
        text->setStyleClass("intromobileText");
    }

    {
        mLayout->addStretch(1);
        auto text = mLayout->addWidget(cpp14::make_unique<WText>("ENTER"),0,Wt::AlignmentFlag::Center);
        text->clicked().connect(this,&intro::Body::eEnterClick);
        text->setStyleClass("introenter");
        mLayout->addStretch(1);
    }


}



Signal<int> &intro::Body::EnterClicked()
{
    return _EnterClicked;
}

void intro::Body::eEnterClick()
{

    _EnterClicked.emit(1);

}



intro::Footer::Footer()
{
    setId("introFooter");
    setStyleClass("introfooter");
    auto mLayout = setLayout(cpp14::make_unique<WVBoxLayout>());
    auto mogatTitleText = mLayout->addWidget(cpp14::make_unique<WText>("Mogat"),0,Wt::AlignmentFlag::Center);
    mogatTitleText->setStyleClass("introMogatSubTitle");
    auto text = mLayout->addWidget(cpp14::make_unique<WText>(legalNoitice),0,Wt::AlignmentFlag::Center|Wt::AlignmentFlag::Bottom);
    text->setStyleClass("introlegalNotice");
    auto text2 = mLayout->addWidget(cpp14::make_unique<WText>("© 2017 MOGAT • powered by Wt & Qt & github"),0,Wt::AlignmentFlag::Center);
    text2->setStyleClass("introcopyRight");
}

intro::FlagWidget::FlagWidget()
{
    auto mflagLayout = setLayout(cpp14::make_unique<WHBoxLayout>());


    auto turkish = mflagLayout->addWidget(cpp14::make_unique<WImage>(WLink("img/flags/tr.jpg")),0,Wt::AlignmentFlag::Center);
    turkish->setMaximumSize(46,28);


    auto english = mflagLayout->addWidget(cpp14::make_unique<WImage>(WLink("img/flags/en.jpg")),0,Wt::AlignmentFlag::Center);
    english->setMaximumSize(46,28);



    auto italian = mflagLayout->addWidget(cpp14::make_unique<WImage>(WLink("img/flags/it.jpg")),0,Wt::AlignmentFlag::Center);
    italian->setMaximumSize(46,28);

    auto german = mflagLayout->addWidget(cpp14::make_unique<WImage>(WLink("img/flags/de.jpg")),0,Wt::AlignmentFlag::Center);
    german->setMaximumSize(46,28);

    english->decorationStyle().setCursor(Wt::Cursor::PointingHand);
    turkish->decorationStyle().setCursor(Wt::Cursor::PointingHand);
    italian->decorationStyle().setCursor(Wt::Cursor::PointingHand);
    german->decorationStyle().setCursor(Wt::Cursor::PointingHand);
}
