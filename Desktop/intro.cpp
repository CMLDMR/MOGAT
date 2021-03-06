#include "intro.h"

intro::Intro::Intro()
{

    auto mLayout = setLayout(cpp14::make_unique<WVBoxLayout>());
    mLayout->setContentsMargins(0,0,0,0);
    mHeader = mLayout->addWidget(cpp14::make_unique<Header>(),0,AlignmentFlag::Justify);
    mBody = mLayout->addWidget(cpp14::make_unique<Body>(),1,Wt::AlignmentFlag::Justify);
    mFooter = mLayout->addWidget(cpp14::make_unique<Footer>());
}


intro::Header::Header()
{

    addStyleClass("header");
    setMargin(0,AllSides);
    setPadding(0,AllSides);

    auto mLayout = setLayout(cpp14::make_unique<WHBoxLayout>());
    mLayout->setContentsMargins(0,0,0,0);

    auto MainContainer = mLayout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Center);
    MainContainer->setStyleClass("mainContainer");

    auto mSubLayout = MainContainer->setLayout(cpp14::make_unique<WHBoxLayout>());
    mSubLayout->setContentsMargins(0,0,0,0);

    auto euroFlag = mSubLayout->addWidget(cpp14::make_unique<WLabel>(""),0,Wt::AlignmentFlag::Right|AlignmentFlag::Middle);
    euroFlag->addStyleClass("euroflag");

    auto mTitle = mSubLayout->addWidget(cpp14::make_unique<WText>("Erasmus+"),0,Wt::AlignmentFlag::Center|AlignmentFlag::Middle);

    mTitle->setStyleClass("headerTitle");

    mSubLayout->addStretch(1);

    mSubLayout->addSpacing(20);

    auto flagWidget = mSubLayout->addWidget(cpp14::make_unique<FlagWidget>(),0,Wt::AlignmentFlag::Right|AlignmentFlag::Middle);

    flagWidget->setPadding(0,AllSides);

    flagWidget->setMargin(0,AllSides);

    flagWidget->setStyleClass("flagwidget");


    auto flagWidgetLandScape = mSubLayout->addWidget(cpp14::make_unique<FlagWidget>(),0,Wt::AlignmentFlag::Right|AlignmentFlag::Middle);

    flagWidgetLandScape->setPadding(0,AllSides);

    flagWidgetLandScape->setMargin(0,AllSides);

    flagWidgetLandScape->addStyleClass("flagwidgetLandScape");

    flagWidgetLandScape->setWidth(WLength::Auto);
}


intro::Body::Body()
{

    addStyleClass("introBody");

    auto mLayout = setLayout(cpp14::make_unique<WVBoxLayout>());
    mLayout->setContentsMargins(0,0,0,0);

    mLayout->addStretch(1);
    {

        auto logoContainer = mLayout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Center);

        auto mlogolayout = logoContainer->setLayout(cpp14::make_unique<WHBoxLayout>());
        auto logoimg = mlogolayout->addWidget(cpp14::make_unique<WLabel>(""),0,Wt::AlignmentFlag::Center);
        logoimg->setStyleClass("MogatLogo");

        auto mlogoTextLayout = mlogolayout->addLayout(cpp14::make_unique<WVBoxLayout>());
        mlogoTextLayout->addStretch(1);
        auto text = mlogoTextLayout->addWidget(cpp14::make_unique<WText>("MOGAT"),0,Wt::AlignmentFlag::Center);
        text->addStyleClass("MogatTitle shadow");
        mlogoTextLayout->addStretch(1);
    }



    mLayout->addStretch(1);
    {
        auto text = mLayout->addWidget(cpp14::make_unique<WText>("MOBILE TOOLS AND GAMIFICATION\n"
                                                                 "AS A NEW LANGUAGE ASSESSMENT SYSTEM IN TOURISM"),0,Wt::AlignmentFlag::Center|Wt::AlignmentFlag::Middle);
        text->addStyleClass("MogatDes shadow");
    }

    mLayout->addStretch(1);
    {
        auto text = mLayout->addWidget(cpp14::make_unique<WText>("ENTER"),0,Wt::AlignmentFlag::Center);
        text->clicked().connect(this,&intro::Body::eEnterClick);
        text->addStyleClass("MogatEnt");
    }


    mLayout->addStretch(1);

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

    setId("footerid");
    setContentAlignment(AlignmentFlag::Center);
    setStyleClass("footer");
    auto mLayout = setLayout(cpp14::make_unique<WVBoxLayout>());
    auto mogatTitleText = mLayout->addWidget(cpp14::make_unique<WText>("Mogat"),0,Wt::AlignmentFlag::Center);
    mogatTitleText->addStyleClass("mogatSubTitle");

    {
        auto container = mLayout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Center);

        auto text = container->addWidget(cpp14::make_unique<WText>(legalNoitice));

        container->setContentAlignment(AlignmentFlag::Justify);

        text->setTextAlignment(AlignmentFlag::Justify);

        text->setMaximumSize(1280,WLength::Auto);
        text->addStyleClass("legalNotice");


    }



    auto text2 = mLayout->addWidget(cpp14::make_unique<WText>("© 2017 MOGAT • powered by Wt & Qt & github"),0,Wt::AlignmentFlag::Center);
//    text2->setStyleClass("introcopyRight");

//    this->doJavaScript("var rect = document.getElementById(\"footerid\").getBoundingClientRect();"
//                       "console.log(rect.top, rect.right, rect.bottom, rect.left, rect.width, rect.height );"
//                       ""
//                       "var w = window.innerWidth"
//                       "|| document.documentElement.clientWidth"
//                       "|| document.body.clientWidth;"
//                       "var h = window.innerHeight"
//                       "|| document.documentElement.clientHeight"
//                       "|| document.body.clientHeight;"
//                       "console.log(\"width: \" + w + \" Height: \" + h)");


}



intro::FlagWidget::FlagWidget()
{
    setMargin(0,Wt::AllSides);
    auto mLayout = setLayout(cpp14::make_unique<WHBoxLayout>());
    mLayout->setContentsMargins(0,0,0,0);

//    setMaximumSize(WLength::Auto,45);


    {
        auto mobileContainer = mLayout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Left);
        mobileContainer->addStyleClass("MobileFlagWidget");

        auto mflagLayout = mobileContainer->setLayout(cpp14::make_unique<WHBoxLayout>());

        auto container = mflagLayout->addWidget(Wt::cpp14::make_unique<Wt::WContainerWidget>(),0,AlignmentFlag::Left);

        auto popupPtr = Wt::cpp14::make_unique<Wt::WPopupMenu>();
        auto popup = popupPtr.get();


        Wt::WPushButton *button = container->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Turkish"));
        button->addStyleClass("langbtn");
        button->setMenu(std::move(popupPtr));


        auto trMenu = popup->addItem("img/flags/tr.jpg", "TR")->triggered().connect([=] {
            button->setText("Turkish");
        });

        auto enMenu = popup->addItem("img/flags/en.jpg", "EN")->triggered().connect([=] {
            button->setText("English");
        });

        auto itMenu = popup->addItem("img/flags/it.jpg", "IT")->triggered().connect([=] {
            button->setText("Italian");
        });

        auto deMenu = popup->addItem("img/flags/de.jpg", "DE")->triggered().connect([=] {
            button->setText("German");
        });
    }




    {
        auto desktopContainer = mLayout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Center);
        desktopContainer->setStyleClass("DesktopFlagWidget");

        auto mflagLayout = desktopContainer->setLayout(cpp14::make_unique<WHBoxLayout>());

        auto turkish = mflagLayout->addWidget(cpp14::make_unique<WImage>(WLink("img/flags/tr.jpg")),0,Wt::AlignmentFlag::Center);
        auto english = mflagLayout->addWidget(cpp14::make_unique<WImage>(WLink("img/flags/en.jpg")),0,Wt::AlignmentFlag::Center);
        auto italian = mflagLayout->addWidget(cpp14::make_unique<WImage>(WLink("img/flags/it.jpg")),0,Wt::AlignmentFlag::Center);
        auto german  = mflagLayout->addWidget(cpp14::make_unique<WImage>(WLink("img/flags/de.jpg")),0,Wt::AlignmentFlag::Center);


        turkish->decorationStyle().setCursor(Cursor::PointingHand);
        english->decorationStyle().setCursor(Cursor::PointingHand);
        italian->decorationStyle().setCursor(Cursor::PointingHand);
        german->decorationStyle().setCursor(Cursor::PointingHand);
    }


}

