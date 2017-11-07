#include "desktopmainpage.h"



MainPage::DesktopMainPage::DesktopMainPage(int _w, int _h, double _r)
    :Ratio(_r),
      Width(_w),
      Height(_h)
{

    setStyleClass("DesktopMainPage");

    mLayout = setLayout(cpp14::make_unique<WVBoxLayout>());

    mLayout->addWidget(cpp14::make_unique<Header>(Width,Height,Ratio));

    mLayout->addWidget(cpp14::make_unique<Body>(),0,Wt::AlignmentFlag::Center);

    mLayout->addWidget(cpp14::make_unique<Footer>());
}

MainPage::Header::Header(int _w , int _h , double _r)
    :Ratio(_r),
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


    auto MainContainer = mLayout->addWidget(cpp14::make_unique<WContainerWidget>(),0,Wt::AlignmentFlag::Center);

//    MainContainer->decorationStyle().setBorder(WBorder(Wt::BorderStyle::Solid),Wt::AllSides);

    MainContainer->setMinimumSize(WLength(960),WLength::Auto);

    setStyleClass("mainheader");

    auto mSubLayout = MainContainer->setLayout(cpp14::make_unique<WHBoxLayout>());
    mSubLayout->setContentsMargins(0,0,0,0);


    mEUFlag = mSubLayout->addWidget(cpp14::make_unique<WImage>(WLink("/img/EurpanCommisionFlag.jpg")),0,Wt::AlignmentFlag::Center|Wt::AlignmentFlag::Middle);

    {
        double d_width = 115;
        double d_hegith = 92;

        if( Ratio != 1 )
        {
            isVertical() ? d_width *= Ratio/2 : d_width *= Ratio/3;
            isVertical() ? d_hegith *= Ratio/2 : d_hegith *= Ratio/3;
        }



        QString str = QString("var title = document.getElementById(\"%1\");"
                              "title.style.width = \"%2px\";"
                              "title.style.height = \"%3px\";").arg(mEUFlag->id().c_str()).arg((int)d_width).arg((int)d_hegith).toStdString().c_str();
        mEUFlag->doJavaScript(str.toStdString());
    }


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

bool MainPage::Header::isVertical() const
{
    return mVertical;
}

MainPage::Footer::Footer()
{
    setStyleClass("mainfooter");
    auto mLayout = setLayout(cpp14::make_unique<WVBoxLayout>());
    auto mogatTitleText = mLayout->addWidget(cpp14::make_unique<WText>("Mogat"),0,Wt::AlignmentFlag::Center);
    mogatTitleText->setStyleClass("introMogatSubTitle");
    auto text = mLayout->addWidget(cpp14::make_unique<WText>(legalNoitice),0,Wt::AlignmentFlag::Center|Wt::AlignmentFlag::Bottom);
    text->setStyleClass("introlegalNotice");
    auto text2 = mLayout->addWidget(cpp14::make_unique<WText>("© 2017 MOGAT • powered by Wt & Qt & github"),0,Wt::AlignmentFlag::Center);
    text2->setStyleClass("introcopyRight");
}

MainPage::Body::Body()
{
    setStyleClass("desktopMainBody");
    setMaximumSize(960,WLength::Auto);
    auto mLayout = setLayout(cpp14::make_unique<WVBoxLayout>());



    menuBar = mLayout->addWidget(cpp14::make_unique<WToolBar>());

    auto MogatButton = cpp14::make_unique<WPushButton>("MOGAT");
    MogatButton.get()->setIcon(WLink("img/btn-flat.jpg"));
    MogatButton.get()->setStyleClass("mainBtn");
    MogatButton.get()->clicked().connect(this,&Body::f_Mogat);
    menuBar->addButton(std::move(MogatButton));


    auto ObjectiveButton = cpp14::make_unique<WPushButton>("OBJECTIVES");
    ObjectiveButton.get()->setIcon(WLink("img/btn-flat.jpg"));
    ObjectiveButton.get()->setStyleClass("mainBtn");
    ObjectiveButton.get()->clicked().connect(this,&Body::f_objective);
    menuBar->addButton(std::move(ObjectiveButton));



    auto ResourceButton = cpp14::make_unique<WPushButton>("RESOURCES");
    ResourceButton.get()->setIcon(WLink("img/btn-flat.jpg"));
    ResourceButton.get()->setStyleClass("mainBtn");
    ResourceButton.get()->clicked().connect(this,&Body::f_resource);
    menuBar->addButton(std::move(ResourceButton));


    auto NewsButton = cpp14::make_unique<WPushButton>("NEWS");
    NewsButton.get()->setIcon(WLink("img/btn-flat.jpg"));
    NewsButton.get()->setStyleClass("mainBtn");
    NewsButton.get()->clicked().connect(this,&Body::f_News);
    menuBar->addButton(std::move(NewsButton));

    auto CollabratorsButton = cpp14::make_unique<WPushButton>("COLLABRATORS");
    CollabratorsButton.get()->setIcon(WLink("img/btn-flat.jpg"));
    CollabratorsButton.get()->setStyleClass("mainBtn");
    CollabratorsButton.get()->clicked().connect(this,&Body::f_collabrators);
    menuBar->addButton(std::move(CollabratorsButton));

    auto ContactButton = cpp14::make_unique<WPushButton>("CONTACT");
    ContactButton.get()->setIcon(WLink("img/btn-flat.jpg"));
    ContactButton.get()->setStyleClass("mainBtn");
    ContactButton.get()->clicked().connect(this,&Body::f_contact);
    menuBar->addButton(std::move(ContactButton),Wt::AlignmentFlag::Right);

    auto AboutButton = cpp14::make_unique<WPushButton>("ABOUT");
    AboutButton.get()->setIcon(WLink("img/btn-flat.jpg"));
    AboutButton.get()->setStyleClass("mainBtn");
    AboutButton.get()->clicked().connect(this,&Body::f_About);
    menuBar->addButton(std::move(AboutButton),Wt::AlignmentFlag::Right);

    mLayout->addStretch(1);



    mContentLayout = mLayout->addLayout(cpp14::make_unique<WVBoxLayout>(),0,Wt::AlignmentFlag::Center);


    mContentWidget = mContentLayout->addWidget(cpp14::make_unique<ContentWidget>());






    this->f_Mogat();


}

void MainPage::Body::f_Mogat()
{
    mContentWidget->clear();

    auto homeimg = mContentWidget->addWidget(cpp14::make_unique<WImage>(WLink("img/homepagePicture.png")));

    homeimg->setStyleClass("mainHomeIMG");


    auto titleText = mContentWidget->addWidget(cpp14::make_unique<WText>("The outcomes of the project?"));
    titleText->setStyleClass("mainPageTitle");

    auto longText  = mContentWidget->addWidget(cpp14::make_unique<WText>("<p align=\"justify\">●The outcomes of this project will help the target groups to overcome the constraints of current situation in L2 courses thanks to</p> "
                                                                         "<p align=\"justify\">●The introduction of an advanced L2 programme for the Tourism Sector using a gamified learning methodology with  knowledge competitions;</p>"
                                                                         "<p align=\"justify\">●An industry oriented approach: the project is supported by major HRD departments of European business stakeholders </p>"
                                                                         "<p align=\"justify\">●They will participate in the L2 tournaments and become direct beneficiaries of the project providing a mobile and ubiquitous learning and training opportunity</p>"
                                                                         "<p align=\"justify\">●Embedding learning analytics in a game: for the learners in the sense of  quantified self, for the institutions and enterprises in the form of anonymous collective diagnostics;</p>"
                                                                         "<p align=\"justify\">●A strong personalized learner orientation with a new motivating and engaging gamification approach, which will be further evaluated in the course of  the project.</p>"
                                                                         ""
                                                                         "<p><b>IMPACT desired</b></p>"
                                                                         "<p>The project will describe organisational models, suggest delivery structures and provide a basis for assessing the potentials based on the experiences gained in its activities. The valorisation strategy and the project model itself  will have a positive impact since it will show how to increase access and retention in life long learning  for the specific target group in the tourism industry.</p>"
                                                                         "<p>Teachers, trainers, educational providers and stakeholders will learn about a suitable model of learning that can be used in the tourism sector  and that has the potential of raising attractiveness for learning foreign languages. Raising of awareness for the problem and the possibilities of modern language learning and training for tourism enterprises and their staff as well as schools and universities operating in the sector of tourism and stakeholders in the tourism industry will be done in all countries of the project and further. An active analytics infrastructure will be created and at the disposal of any interested person or organisation. Quote from an UNESCO publication (Nov. 2012): \"Compared to many other sectors, educational institutions are currently 'driving blind'. They should invest in ANALYTICS INFRASTRUCTURE for two reasons: to optimise student success, and to enable their own researchers to ask foundational questions about learning and teaching in the 21st century\".</p>"));

    longText->setStyleClass("longText");
}

void MainPage::Body::f_objective()
{

    mContentWidget->clear();

    auto title = mContentWidget->addWidget(cpp14::make_unique<WText>("<h1>Objective Content Will be Added</h1>"));


    auto content = mContentWidget->addWidget(cpp14::make_unique<WText>("Contrary to popular belief, Lorem Ipsum is not simply random text. It has roots in a piece of classical Latin literature from 45 BC, making it over 2000 years old. Richard McClintock, a Latin professor at Hampden-Sydney College in Virginia, looked up one of the more obscure Latin words, consectetur, from a Lorem Ipsum passage, and going through the cites of the word in classical literature, discovered the undoubtable source. Lorem Ipsum comes from sections 1.10.32 and 1.10.33 of \"de Finibus Bonorum et Malorum\" (The Extremes of Good and Evil) by Cicero, written in 45 BC. This book is a treatise on the theory of ethics, very popular during the Renaissance. The first line of Lorem Ipsum, \"Lorem ipsum dolor sit amet..\", comes from a line in section 1.10.32"));

    content->setStyleClass("longText");

}

void MainPage::Body::f_resource()
{

    mContentWidget->clear();

    auto title = mContentWidget->addWidget(cpp14::make_unique<WText>("<h1>Resource Content Will be Added</h1>"));


    auto content = mContentWidget->addWidget(cpp14::make_unique<WText>("Contrary to popular belief, Lorem Ipsum is not simply random text. It has roots in a piece of classical Latin literature from 45 BC, making it over 2000 years old. Richard McClintock, a Latin professor at Hampden-Sydney College in Virginia, looked up one of the more obscure Latin words, consectetur, from a Lorem Ipsum passage, and going through the cites of the word in classical literature, discovered the undoubtable source. Lorem Ipsum comes from sections 1.10.32 and 1.10.33 of \"de Finibus Bonorum et Malorum\" (The Extremes of Good and Evil) by Cicero, written in 45 BC. This book is a treatise on the theory of ethics, very popular during the Renaissance. The first line of Lorem Ipsum, \"Lorem ipsum dolor sit amet..\", comes from a line in section 1.10.32"));

    content->setStyleClass("longText");
}

void MainPage::Body::f_News()
{
    mContentWidget->clear();
    auto title = mContentWidget->addWidget(cpp14::make_unique<WText>("<h1>News Content Will be Added</h1>"));


    auto content = mContentWidget->addWidget(cpp14::make_unique<WText>("Contrary to popular belief, Lorem Ipsum is not simply random text. It has roots in a piece of classical Latin literature from 45 BC, making it over 2000 years old. Richard McClintock, a Latin professor at Hampden-Sydney College in Virginia, looked up one of the more obscure Latin words, consectetur, from a Lorem Ipsum passage, and going through the cites of the word in classical literature, discovered the undoubtable source. Lorem Ipsum comes from sections 1.10.32 and 1.10.33 of \"de Finibus Bonorum et Malorum\" (The Extremes of Good and Evil) by Cicero, written in 45 BC. This book is a treatise on the theory of ethics, very popular during the Renaissance. The first line of Lorem Ipsum, \"Lorem ipsum dolor sit amet..\", comes from a line in section 1.10.32"));

    content->setStyleClass("longText");
}

void MainPage::Body::f_collabrators()
{
    mContentWidget->clear();
    auto title = mContentWidget->addWidget(cpp14::make_unique<WText>("<h1>COLLABRATORS Content Will be Added</h1>"));


    auto content = mContentWidget->addWidget(cpp14::make_unique<WText>("Contrary to popular belief, Lorem Ipsum is not simply random text. It has roots in a piece of classical Latin literature from 45 BC, making it over 2000 years old. Richard McClintock, a Latin professor at Hampden-Sydney College in Virginia, looked up one of the more obscure Latin words, consectetur, from a Lorem Ipsum passage, and going through the cites of the word in classical literature, discovered the undoubtable source. Lorem Ipsum comes from sections 1.10.32 and 1.10.33 of \"de Finibus Bonorum et Malorum\" (The Extremes of Good and Evil) by Cicero, written in 45 BC. This book is a treatise on the theory of ethics, very popular during the Renaissance. The first line of Lorem Ipsum, \"Lorem ipsum dolor sit amet..\", comes from a line in section 1.10.32"));

    content->setStyleClass("longText");
}

void MainPage::Body::f_About()
{
    mContentWidget->clear();
    auto title = mContentWidget->addWidget(cpp14::make_unique<WText>("<h1>About Content Will be Added</h1>"));


    auto content = mContentWidget->addWidget(cpp14::make_unique<WText>("Contrary to popular belief, Lorem Ipsum is not simply random text. It has roots in a piece of classical Latin literature from 45 BC, making it over 2000 years old. Richard McClintock, a Latin professor at Hampden-Sydney College in Virginia, looked up one of the more obscure Latin words, consectetur, from a Lorem Ipsum passage, and going through the cites of the word in classical literature, discovered the undoubtable source. Lorem Ipsum comes from sections 1.10.32 and 1.10.33 of \"de Finibus Bonorum et Malorum\" (The Extremes of Good and Evil) by Cicero, written in 45 BC. This book is a treatise on the theory of ethics, very popular during the Renaissance. The first line of Lorem Ipsum, \"Lorem ipsum dolor sit amet..\", comes from a line in section 1.10.32"));

    content->setStyleClass("longText");
}

void MainPage::Body::f_contact()
{
    mContentWidget->clear();
    auto title = mContentWidget->addWidget(cpp14::make_unique<WText>("<h1>Contact Content Will be Added</h1>"));

    auto content = mContentWidget->addWidget(cpp14::make_unique<WText>("Contrary to popular belief, Lorem Ipsum is not simply random text. It has roots in a piece of classical Latin literature from 45 BC, making it over 2000 years old. Richard McClintock, a Latin professor at Hampden-Sydney College in Virginia, looked up one of the more obscure Latin words, consectetur, from a Lorem Ipsum passage, and going through the cites of the word in classical literature, discovered the undoubtable source. Lorem Ipsum comes from sections 1.10.32 and 1.10.33 of \"de Finibus Bonorum et Malorum\" (The Extremes of Good and Evil) by Cicero, written in 45 BC. This book is a treatise on the theory of ethics, very popular during the Renaissance. The first line of Lorem Ipsum, \"Lorem ipsum dolor sit amet..\", comes from a line in section 1.10.32"));

    content->setStyleClass("longText");
}

MainPage::FlagWidget::FlagWidget()
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

MainPage::ContentWidget::ContentWidget()
{

}
