#include "intro.h"

intro::Intro::Intro(int _w, int _h, double _ratio)
    :width(_w),
      height(_h),
      ratio(_ratio)
{

    setContentAlignment(Wt::AlignmentFlag::Center);
    auto mLayout = setLayout(cpp14::make_unique<WVBoxLayout>());
    mHeader = mLayout->addWidget(cpp14::make_unique<Header>(width,height,ratio));
    mBody = mLayout->addWidget(cpp14::make_unique<Body>(width,height,ratio),0,Wt::AlignmentFlag::Middle);
    mFooter = mLayout->addWidget(cpp14::make_unique<Footer>(width,height,ratio),0,Wt::AlignmentFlag::Bottom);
    setStyleClass("introMain");
}




intro::Header::Header(int _w, int _h, double _ratio)
    :Ratio(_ratio),
      Width(_w),
      Height(_h)
{

    if( Width > Height )
    {
        mVertical = false;
    }else{
        mVertical = true;
    }


    mLayout = setLayout(cpp14::make_unique<WHBoxLayout>());
    mLayout->setContentsMargins(0,0,0,0);




    auto MainContainer = mLayout->addWidget(cpp14::make_unique<WContainerWidget>());

    setStyleClass("introheader");


    auto mSubLayout = MainContainer->setLayout(cpp14::make_unique<WHBoxLayout>());
    mSubLayout->setContentsMargins(0,0,0,0);


    mEUFlag = mSubLayout->addWidget(cpp14::make_unique<WImage>(WLink("/img/EurpanCommisionFlag.jpg")),0,Wt::AlignmentFlag::Right);

    auto mDevLayout = mSubLayout->addLayout(cpp14::make_unique<WVBoxLayout>(),0,Wt::AlignmentFlag::Left);
    auto mTitle = mDevLayout->addWidget(cpp14::make_unique<WText>("Development of Innovation"),0,Wt::AlignmentFlag::Center);
    mTitle->setStyleClass("introDevelopment_of_Innovation");

    double fontSize = 34;
    if( Ratio != 1.0 )
    {
        isVertical() ? fontSize *= Ratio/2.0 : fontSize;
    }

    QString str = QString("var title = document.getElementById(\"%1\");"
                          "title.style.fontSize = \"%2px\";"
                          "console.log(title.style.fontSize);").arg(mTitle->id().c_str()).arg(fontSize).toStdString().c_str();
    mTitle->doJavaScript(str.toStdString());



    auto mflagWidget = mDevLayout->addWidget(cpp14::make_unique<FlagWidget>(),1,Wt::AlignmentFlag::Justify);



}

bool intro::Header::isVertical() const
{
    return mVertical;
}






intro::Body::Body(int _w, int _h, double _r)
    :Width(_w),
      Height(_h),
      Ratio(_r)
{


    if( Width > Height )
    {
        mVertical = false;
    }else{
        mVertical = true;
    }


    setId("introBody");

    setStyleClass("introBody");
    setMinimumSize( WLength::Auto , _h-138-100 );

    setMargin(WLength::Auto,Wt::AllSides);

    setContentAlignment(Wt::AlignmentFlag::Center|Wt::AlignmentFlag::Middle);
    auto mLayout = setLayout(cpp14::make_unique<WVBoxLayout>());

    mLayout->addStretch(1);

    {

        auto mlogolayout = mLayout->addLayout(cpp14::make_unique<WHBoxLayout>(),0,Wt::AlignmentFlag::Middle);
        auto logoimg = mlogolayout->addWidget(cpp14::make_unique<WImage>(WLink("img/Logo1.png")),0,Wt::AlignmentFlag::Right);

        double d_width = 75;
        double d_hegith = 149;

        if( Ratio != 1 )
        {
            isVertical() ? d_width *= 1.5 : d_width /= 2;
            isVertical() ? d_hegith *= 1.5 : d_hegith /= 2;
        }



        QString str = QString("var title = document.getElementById(\"%1\");"
                              "title.style.width = \"%2px\";"
                              "title.style.height = \"%3px\";").arg(logoimg->id().c_str()).arg((int)d_width).arg((int)d_hegith).toStdString().c_str();
        logoimg->doJavaScript(str.toStdString());








        auto mlogoTextLayout = mlogolayout->addLayout(cpp14::make_unique<WVBoxLayout>());
        mlogoTextLayout->addStretch(1);
        auto text = mlogoTextLayout->addWidget(cpp14::make_unique<WText>("MOGAT"),0,Wt::AlignmentFlag::Left);
        text->setStyleClass("introMogat");
        mlogoTextLayout->addStretch(1);

        int fontSize = 64;
        if( Ratio != 1 )
        {
            isVertical() ? fontSize : fontSize = 28;
        }

        str = QString("var title = document.getElementById(\"%1\");"
                              "title.style.fontSize = \"%2px\";").arg(text->id().c_str()).arg(Ratio*fontSize).toStdString().c_str();
        text->doJavaScript(str.toStdString());

    }

    {
        mLayout->addStretch(1);
        auto text = mLayout->addWidget(cpp14::make_unique<WText>("MOBILE TOOLS AND GAMIFICATION\n"
                                                                 "AS A NEW LANGUAGE ASSESSMENT SYSTEM IN TOURISM"),0,Wt::AlignmentFlag::Center|Wt::AlignmentFlag::Middle);

        text->setStyleClass("intromobileText");

        int fontSize = 28;

        if( Ratio != 1 )
        {
            isVertical() ? fontSize : fontSize = 20;

            QString str = QString("var title = document.getElementById(\"%1\");"
                                  "title.style.fontSize = \"%2px\";").arg(text->id().c_str()).arg(Ratio/2*fontSize).toStdString().c_str();

            text->doJavaScript(str.toStdString());
        }else{

            QString str = QString("var title = document.getElementById(\"%1\");"
                                  "title.style.fontSize = \"%2px\";").arg(text->id().c_str()).arg(Ratio*fontSize).toStdString().c_str();

            text->doJavaScript(str.toStdString());
        }

    }

    {
        mLayout->addStretch(1);
        auto text = mLayout->addWidget(cpp14::make_unique<WText>("ENTER"),0,Wt::AlignmentFlag::Center);
        text->clicked().connect(this,&intro::Body::eEnterClick);
        text->setStyleClass("introenter");


        int fontSize = 64;
        if( Ratio != 1 )
        {
            isVertical() ? fontSize : fontSize = 24;
        }

        QString str = QString("var title = document.getElementById(\"%1\");"
                              "title.style.fontSize = \"%2px\";").arg(text->id().c_str()).arg(Ratio*fontSize).toStdString().c_str();
        text->doJavaScript(str.toStdString());

        mLayout->addStretch(1);
    }


}



Signal<int> &intro::Body::EnterClicked()
{
    return _EnterClicked;
}

bool intro::Body::isVertical() const
{
    return mVertical;
}

void intro::Body::eEnterClick()
{

    _EnterClicked.emit(1);

}



intro::Footer::Footer(int _w, int _h, double _r)
    :Width(_w),
      Height(_h),
      Ratio(_r)
{

    if( Width > Height )
    {
        mVertical = false;
    }else{
        mVertical = true;
    }

    setId("introFooter");
    setStyleClass("introfooter");
    auto mLayout = setLayout(cpp14::make_unique<WVBoxLayout>());
    auto mogatTitleText = mLayout->addWidget(cpp14::make_unique<WText>("Mogat"),0,Wt::AlignmentFlag::Center);
    mogatTitleText->setStyleClass("introMogatSubTitle");
    auto text = mLayout->addWidget(cpp14::make_unique<WText>(legalNoitice),0,Wt::AlignmentFlag::Center|Wt::AlignmentFlag::Bottom);
    text->setStyleClass("introlegalNotice");
    auto text2 = mLayout->addWidget(cpp14::make_unique<WText>("© 2017 MOGAT • powered by Wt & Qt & github"),0,Wt::AlignmentFlag::Center);
    text2->setStyleClass("introcopyRight");


    //mogatTitleText font restyling
    {
        int fontSize = 12;
        if( Ratio != 1.0 )
        {
            isVertical() ? fontSize = 11 : fontSize = 10;
        }

        QString str = QString("var title = document.getElementById(\"%1\");"
                              "title.style.fontSize = \"%2px\";").arg(mogatTitleText->id().c_str()).arg(Ratio*fontSize).toStdString().c_str();
        mogatTitleText->doJavaScript(str.toStdString());
    }

    //text2 font restyling
    {
        int fontSize = 10;
        if( Ratio != 1.0 )
        {
            isVertical() ? fontSize = 8 : fontSize = 6;
        }

        QString str = QString("var title = document.getElementById(\"%1\");"
                              "title.style.fontSize = \"%2px\";").arg(text->id().c_str()).arg(Ratio*fontSize).toStdString().c_str();
        text->doJavaScript(str.toStdString());
    }

    //text2 font restyling
    {
        int fontSize = 10;
        if( Ratio != 1.0 )
        {
            isVertical() ? fontSize = 8 : fontSize = 6;
        }

        QString str = QString("var title = document.getElementById(\"%1\");"
                              "title.style.fontSize = \"%2px\";").arg(text2->id().c_str()).arg(Ratio*fontSize).toStdString().c_str();
        text2->doJavaScript(str.toStdString());
    }


}

bool intro::Footer::isVertical() const
{
    return mVertical;
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
