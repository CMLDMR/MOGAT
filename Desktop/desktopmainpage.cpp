#include "desktopmainpage.h"



MainPage::DesktopMainPage::DesktopMainPage(int _w, int _h, double _r)
    :Ratio(_r),
      Width(_w),
      Height(_h)
{

    setStyleClass("DesktopMainPage");

    mLayout = setLayout(cpp14::make_unique<WVBoxLayout>());
    mLayout->setContentsMargins(0,0,0,0);

    mLayout->addWidget(cpp14::make_unique<Header>(Width,Height,Ratio),0,AlignmentFlag::Top|AlignmentFlag::Justify);

    mLayout->addWidget(cpp14::make_unique<Body>(Width,Height,Ratio),1,Wt::AlignmentFlag::Justify|AlignmentFlag::Center);

    mLayout->addWidget(cpp14::make_unique<Footer>(),0,AlignmentFlag::Justify|AlignmentFlag::Bottom);
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




    auto MainContainer = mLayout->addWidget(cpp14::make_unique<WContainerWidget>());

    setStyleClass("mainheader");


    auto mSubLayout = MainContainer->setLayout(cpp14::make_unique<WHBoxLayout>());
    mSubLayout->setContentsMargins(0,0,0,0);


    mEUFlag = mSubLayout->addWidget(cpp14::make_unique<WImage>(WLink("/img/EurpanCommisionFlag.jpg")),0,Wt::AlignmentFlag::Right|Wt::AlignmentFlag::Middle);

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

    auto mDevLayout = mSubLayout->addLayout(cpp14::make_unique<WVBoxLayout>(),0,Wt::AlignmentFlag::Left|AlignmentFlag::Middle);


    double fontSize = 34;
    if( Ratio != 1.0 )
    {
        if( isVertical() )
        {
            fontSize *= Ratio/2.2;

            auto mTitle = mDevLayout->addWidget(cpp14::make_unique<WText>("Development\nof\nInnovation"),0,Wt::AlignmentFlag::Center|AlignmentFlag::Middle);
            mTitle->setStyleClass("introDevelopment_of_Innovation");


            QString str = QString("var title = document.getElementById(\"%1\");"
                                  "title.style.fontSize = \"%2px\";").arg(mTitle->id().c_str()).arg(fontSize).toStdString().c_str();
            mTitle->doJavaScript(str.toStdString());


        }else{

            auto mTitle = mDevLayout->addWidget(cpp14::make_unique<WText>("Development of Innovation"),0,Wt::AlignmentFlag::Center|AlignmentFlag::Middle);
            mTitle->setStyleClass("introDevelopment_of_Innovation");

            QString str = QString("var title = document.getElementById(\"%1\");"
                                  "title.style.fontSize = \"%2px\";"
                                  "console.log(title.style.fontSize);").arg(mTitle->id().c_str()).arg(fontSize).toStdString().c_str();
            mTitle->doJavaScript(str.toStdString());
        }
    }else{
        auto mTitle = mDevLayout->addWidget(cpp14::make_unique<WText>("Development of Innovation"),0,Wt::AlignmentFlag::Center|AlignmentFlag::Middle);
        mTitle->setStyleClass("introDevelopment_of_Innovation");

        QString str = QString("var title = document.getElementById(\"%1\");"
                              "title.style.fontSize = \"%2px\";"
                              "console.log(title.style.fontSize);").arg(mTitle->id().c_str()).arg(fontSize).toStdString().c_str();
        mTitle->doJavaScript(str.toStdString());
    }

    if( Ratio > 1.0 )
    {
        mSubLayout->addWidget(cpp14::make_unique<FlagWidget>(Width,Height,Ratio),1,Wt::AlignmentFlag::Right|AlignmentFlag::Middle);
    }else{
        mDevLayout->addWidget(cpp14::make_unique<FlagWidget>(Width,Height,Ratio),1,Wt::AlignmentFlag::Justify|AlignmentFlag::Middle);
    }



}

bool MainPage::Header::isVertical() const
{
    return mVertical;
}

MainPage::Footer::Footer()
{
    decorationStyle().setBackgroundColor(WColor(38,38,38));

    auto mLayout = setLayout(cpp14::make_unique<WVBoxLayout>());

    mLayout->setContentsMargins(0,0,0,0);

    auto mogatTitleText = mLayout->addWidget(cpp14::make_unique<WText>("Mogat"),0,Wt::AlignmentFlag::Center);

    mogatTitleText->setStyleClass("introMogatSubTitle");

    auto text = mLayout->addWidget(cpp14::make_unique<WText>(legalNoitice),0,Wt::AlignmentFlag::Center|Wt::AlignmentFlag::Bottom);
    text->setStyleClass("introlegalNotice");

    auto text2 = mLayout->addWidget(cpp14::make_unique<WText>("© 2017 MOGAT • powered by Wt & Qt & github"),0,Wt::AlignmentFlag::Center);
    text2->setStyleClass("introcopyRight");
}

MainPage::Body::Body( int _w , int _h , double _r )
    :Width(_w),Height(_h),Ratio(_r)
{

    mVertical = true;
    if( Width > Height )
    {
        mVertical = false;
    }
    setStyleClass("desktopMainBody");
    auto mLayout = setLayout(cpp14::make_unique<WVBoxLayout>());

    menuBar = mLayout->addWidget(cpp14::make_unique<WToolBar>(),0,Wt::AlignmentFlag::Center|AlignmentFlag::Top);

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

//    mLayout->addStretch(1);

    mContentLayout = mLayout->addLayout(cpp14::make_unique<WVBoxLayout>(),0,Wt::AlignmentFlag::Center);

    mContentWidget = mContentLayout->addWidget(cpp14::make_unique<ContentWidget>(),0,AlignmentFlag::Center);

    if( Width > 900 )
    {
        mContentWidget->setMaximumSize(900,WLength::Auto);
    }else{
        mContentWidget->setMaximumSize(Width-20,WLength::Auto);
    }

    this->f_Mogat();

}

void MainPage::Body::f_Mogat()
{
    mContentWidget->clear();

    auto homeimg = mContentWidget->addWidget(cpp14::make_unique<WImage>(WLink("img/homepagePicture.png")));

    homeimg->setStyleClass("mainHomeIMG");


    auto titleText = mContentWidget->addWidget(cpp14::make_unique<WText>("The outcomes of the project?"));
    titleText->setStyleClass("mainPageTitle");

    {
        int fontSize = 18;
        if( Ratio != 1.0 )
        {
            isVertical() ? fontSize *= Ratio : fontSize *= (int)(Ratio/3.0*2.0);
        }

        QString str = QString("var title = document.getElementById(\"%1\");"
                              "title.style.fontSize = \"%2px\";").arg(titleText->id().c_str()).arg(fontSize).toStdString().c_str();
        titleText->doJavaScript(str.toStdString());
    }

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

    {
        int fontSize = 14;
        if( Ratio != 1.0 )
        {
            isVertical() ? fontSize *= Ratio : fontSize *= (int)(Ratio/3.0*2.0);
            std::cout << "Font Size : " << fontSize <<"  " << Ratio << " " << (Ratio/3.0*2.0) << std::endl;

        }

        QString str = QString("var title = document.getElementById(\"%1\");"
                              "title.style.fontSize = \"%2px\";").arg(longText->id().c_str()).arg(fontSize).toStdString().c_str();
        longText->doJavaScript(str.toStdString());
    }
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

bool MainPage::Body::isVertical() const
{
    return mVertical;
}

MainPage::FlagWidget::FlagWidget(int _w, int _h, double _r)
    :Width(_w),Height(_h),Ratio(_r)
{

    if( Width > Height )
    {
        mVertical = false;
    }else{
        mVertical = true;
    }


    if( Ratio != 1.0 )
    {

            /// Mobile Page Vertical
            auto mflagLayout = setLayout(cpp14::make_unique<WHBoxLayout>());

            auto container = mflagLayout->addWidget(Wt::cpp14::make_unique<Wt::WContainerWidget>(),0,AlignmentFlag::Right);

            auto statusPtr = Wt::cpp14::make_unique<Wt::WText>();
            auto status = statusPtr.get();
            status->setMargin(10, Wt::Side::Left | Wt::Side::Right);
            status->setStyleClass("LangText");

            auto popupPtr = Wt::cpp14::make_unique<Wt::WPopupMenu>();
            auto popup = popupPtr.get();

            auto trMenu = popup->addItem("img/flags/tr.jpg", "TR")->triggered().connect([=] {
                status->setText("Turkish");
            });


            auto enMenu = popup->addItem("img/flags/en.jpg", "EN")->triggered().connect([=] {
                status->setText("English");
            });

            auto itMenu = popup->addItem("img/flags/it.jpg", "IT")->triggered().connect([=] {
                status->setText("Italian");
            });

            auto deMenu = popup->addItem("img/flags/de.jpg", "DE")->triggered().connect([=] {
                status->setText("German");
            });


            container->addWidget(std::move(statusPtr));


            Wt::WPushButton *button = container->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Lang"));
            button->setMenu(std::move(popupPtr));
            button->setStyleClass("Langbtn");
            button->setMinimumSize(WLength::Auto,25);

            //mogatTitleText font restyling
            {
                int fontSize = 12;
                if( Ratio != 1.0 )
                {
                    isVertical() ? fontSize *= Ratio/2 : fontSize *= Ratio/4;
                    button->setMinimumSize(WLength::Auto,50);
                }

                QString str = QString("var title = document.getElementById(\"%1\");"
                                      "title.style.fontSize = \"%2px\";").arg(button->id().c_str()).arg(Ratio*fontSize).toStdString().c_str();
                button->doJavaScript(str.toStdString());
            }


            popup->setStyleClass("dropbtn");

            //mogatTitleText font restyling
            {
                int fontSize = 10;
                if( Ratio != 1.0 )
                {
                    isVertical() ? fontSize *= Ratio/2 : fontSize *= Ratio/3;
                }

                QString str = QString("var title = document.getElementById(\"%1\");"
                                      "title.style.fontSize = \"%2px\";").arg(popup->id().c_str()).arg(Ratio*fontSize).toStdString().c_str();
                popup->doJavaScript(str.toStdString());
            }



    }else{

        /// Desktop Page
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


}

bool MainPage::FlagWidget::isVertical() const
{
    return mVertical;
}

MainPage::ContentWidget::ContentWidget()
{

}
