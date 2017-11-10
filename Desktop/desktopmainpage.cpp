#include "desktopmainpage.h"

#include "intro.h"


MainPage::DesktopMainPage::DesktopMainPage(int _w, int _h, double _r)
    :Ratio(_r),
      Width(_w),
      Height(_h)
{


    mLayout = setLayout(cpp14::make_unique<WVBoxLayout>());
    mLayout->setContentsMargins(0,0,0,0);

    mLayout->addWidget(cpp14::make_unique<intro::Header>(),0,AlignmentFlag::Top|AlignmentFlag::Justify);

    mLayout->addWidget(cpp14::make_unique<Body>(),1,Wt::AlignmentFlag::Justify|AlignmentFlag::Center);

    mLayout->addWidget(cpp14::make_unique<intro::Footer>(),0,AlignmentFlag::Justify|AlignmentFlag::Bottom);
}





MainPage::Body::Body()
{

    auto mLayout = setLayout(cpp14::make_unique<WVBoxLayout>());

    this->MenuBarForMobile(mLayout);

    mContentLayout = mLayout->addLayout(cpp14::make_unique<WVBoxLayout>(),0,Wt::AlignmentFlag::Center);

    mContentWidget = mContentLayout->addWidget(cpp14::make_unique<ContentWidget>(),0,AlignmentFlag::Center);

    this->f_Mogat();

}

void MainPage::Body::MenuBarForDesktop(WVBoxLayout* layout)
{


    menuBar = layout->addWidget(cpp14::make_unique<WToolBar>(),0,Wt::AlignmentFlag::Center|AlignmentFlag::Top);


    std::vector<std::string> buttonidList;

    auto MogatButton = cpp14::make_unique<WPushButton>("MOGAT");
    MogatButton.get()->setIcon(WLink("img/btn-flat.jpg"));
    MogatButton.get()->setStyleClass("mainBtn");
    MogatButton.get()->clicked().connect(this,&Body::f_Mogat);
    buttonidList.push_back(MogatButton->id());
    menuBar->addButton(std::move(MogatButton));


    auto ObjectiveButton = cpp14::make_unique<WPushButton>("OBJECTIVES");
    ObjectiveButton.get()->setIcon(WLink("img/btn-flat.jpg"));
    ObjectiveButton.get()->setStyleClass("mainBtn");
    ObjectiveButton.get()->clicked().connect(this,&Body::f_objective);
    buttonidList.push_back(ObjectiveButton->id());
    menuBar->addButton(std::move(ObjectiveButton));

    auto ResourceButton = cpp14::make_unique<WPushButton>("RESOURCES");
    ResourceButton.get()->setIcon(WLink("img/btn-flat.jpg"));
    ResourceButton.get()->setStyleClass("mainBtn");
    ResourceButton.get()->clicked().connect(this,&Body::f_resource);
    buttonidList.push_back(ResourceButton->id());
    menuBar->addButton(std::move(ResourceButton));

    auto NewsButton = cpp14::make_unique<WPushButton>("NEWS");
    NewsButton.get()->setIcon(WLink("img/btn-flat.jpg"));
    NewsButton.get()->setStyleClass("mainBtn");
    NewsButton.get()->clicked().connect(this,&Body::f_News);
    buttonidList.push_back(NewsButton->id());
    menuBar->addButton(std::move(NewsButton));

    auto CollabratorsButton = cpp14::make_unique<WPushButton>("COLLABRATORS");
    CollabratorsButton.get()->setIcon(WLink("img/btn-flat.jpg"));
    CollabratorsButton.get()->setStyleClass("mainBtn");
    CollabratorsButton.get()->clicked().connect(this,&Body::f_collabrators);
    buttonidList.push_back(CollabratorsButton->id());
    menuBar->addButton(std::move(CollabratorsButton));

    auto ContactButton = cpp14::make_unique<WPushButton>("CONTACT");
    ContactButton.get()->setIcon(WLink("img/btn-flat.jpg"));
    ContactButton.get()->setStyleClass("mainBtn");
    ContactButton.get()->clicked().connect(this,&Body::f_contact);
    buttonidList.push_back(ContactButton->id());
    menuBar->addButton(std::move(ContactButton),Wt::AlignmentFlag::Right);

    auto AboutButton = cpp14::make_unique<WPushButton>("ABOUT");
    AboutButton.get()->setIcon(WLink("img/btn-flat.jpg"));
    AboutButton.get()->setStyleClass("mainBtn");
    AboutButton.get()->clicked().connect(this,&Body::f_About);
    buttonidList.push_back(AboutButton->id());



    menuBar->addButton(std::move(AboutButton),Wt::AlignmentFlag::Right);


}

void MainPage::Body::MenuBarForMobile(WVBoxLayout *layout)
{

    Wt::WNavigationBar *navigation =
        layout->addWidget(Wt::cpp14::make_unique<Wt::WNavigationBar>());
    navigation->setTitle("MOGAT",
                 "http://www.google.com/search?q=MOGAT");


    navigation->setResponsive(true);

    Wt::WStackedWidget *contentsStack = layout->addWidget(Wt::cpp14::make_unique<Wt::WStackedWidget>());
    contentsStack->addStyleClass("contents");

    Wt::WAnimation animation(Wt::AnimationEffect::Fade,
                 Wt::TimingFunction::Linear,
                 200);
    contentsStack->setTransitionAnimation(animation, true);


    auto leftMenu = Wt::cpp14::make_unique<Wt::WMenu>(contentsStack);
    auto leftMenu_ = navigation->addMenu(std::move(leftMenu));

    auto searchResult = Wt::cpp14::make_unique<Wt::WText>("Buy or Sell... Bye!");
    auto searchResult_ = searchResult.get();

    auto menuitem = leftMenu_->addItem("icon/home.svg","HOME", Wt::cpp14::make_unique<Wt::WText>("There is no better place!"));
    menuitem->setStyleClass("mainBtn");

    leftMenu_->addItem("icon/home.svg","OBJECTIVES", Wt::cpp14::make_unique<Wt::WText>("Layout contents"))->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/layout"));
    leftMenu_->addItem("icon/home.svg","RESOURCES", std::move(searchResult));
    leftMenu_->addItem("icon/home.svg","NEWS", Wt::cpp14::make_unique<Wt::WText>("News"))->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/news"));
    leftMenu_->addItem("icon/home.svg","COLLABRATORS", Wt::cpp14::make_unique<Wt::WText>("COLLABRATORS"))->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/collabrator"));
    leftMenu_->addItem("icon/home.svg","ABOUT", Wt::cpp14::make_unique<Wt::WText>("About"))->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/about"));
    leftMenu_->addItem("icon/home.svg","CONTACT", Wt::cpp14::make_unique<Wt::WText>("Contacs"))->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/contact"));

    // Setup a Right-aligned menu.
    auto rightMenu = Wt::cpp14::make_unique<Wt::WMenu>();
    auto rightMenu_ = navigation->addMenu(std::move(rightMenu), Wt::AlignmentFlag::Right);

    // Create a popup submenu for the Help menu.
    auto popupPtr = Wt::cpp14::make_unique<Wt::WPopupMenu>();
    auto popup = popupPtr.get();
    popup->addItem("Contents");
    popup->addItem("Index");
    popup->addSeparator();
    popup->addItem("About");

    popup->itemSelected().connect([=] (Wt::WMenuItem *item) {
        auto messageBox = popup->addChild(
                Wt::cpp14::make_unique<Wt::WMessageBox>
                ("Help",
                 Wt::WString("<p>Showing Help: {1}</p>").arg(item->text()),
                 Wt::Icon::Information, Wt::StandardButton::Ok));

        messageBox->buttonClicked().connect([=] {
            popup->removeChild(messageBox);
        });

        messageBox->show();
    });

    auto item = Wt::cpp14::make_unique<Wt::WMenuItem>("Help");
    item->setMenu(std::move(popupPtr));
    rightMenu_->addItem(std::move(item));

    // Add a Search control.
    auto editPtr = Wt::cpp14::make_unique<Wt::WLineEdit>();
    auto edit = editPtr.get();
    edit->setPlaceholderText("Enter a search item");

    edit->enterPressed().connect([=] {
        leftMenu_->select(2); // is the index of the "Sales"
        searchResult_->setText(Wt::WString("Nothing found for {1}.")
                              .arg(edit->text()));
    });

    navigation->addSearch(std::move(editPtr), Wt::AlignmentFlag::Right);

}

void MainPage::Body::f_Mogat()
{
    mContentWidget->clear();

    auto titleText = mContentWidget->addWidget(cpp14::make_unique<WText>("The outcomes of the project?"));


    auto longText  = mContentWidget->addWidget(cpp14::make_unique<WText>("<p align=\"justify\">●  The outcomes of this project will help the target groups to overcome the constraints of current situation in L2 courses thanks to</p> "
                                                                         "<p align=\"justify\">●  The introduction of an advanced L2 programme for the Tourism Sector using a gamified learning methodology with  knowledge competitions;</p>"
                                                                         "<p align=\"justify\">●  An industry oriented approach: the project is supported by major HRD departments of European business stakeholders </p>"
                                                                         "<p align=\"justify\">●  They will participate in the L2 tournaments and become direct beneficiaries of the project providing a mobile and ubiquitous learning and training opportunity</p>"
                                                                         "<p align=\"justify\">●  Embedding learning analytics in a game: for the learners in the sense of  quantified self, for the institutions and enterprises in the form of anonymous collective diagnostics;</p>"
                                                                         "<p align=\"justify\">●  A strong personalized learner orientation with a new motivating and engaging gamification approach, which will be further evaluated in the course of  the project.</p>"
                                                                         ""
                                                                         "<p><b>IMPACT desired</b></p>"
                                                                         "<p>The project will describe organisational models, suggest delivery structures and provide a basis for assessing the potentials based on the experiences gained in its activities. The valorisation strategy and the project model itself  will have a positive impact since it will show how to increase access and retention in life long learning  for the specific target group in the tourism industry.</p>"
                                                                         "<p>Teachers, trainers, educational providers and stakeholders will learn about a suitable model of learning that can be used in the tourism sector  and that has the potential of raising attractiveness for learning foreign languages. Raising of awareness for the problem and the possibilities of modern language learning and training for tourism enterprises and their staff as well as schools and universities operating in the sector of tourism and stakeholders in the tourism industry will be done in all countries of the project and further. An active analytics infrastructure will be created and at the disposal of any interested person or organisation. Quote from an UNESCO publication (Nov. 2012): \"Compared to many other sectors, educational institutions are currently 'driving blind'. They should invest in ANALYTICS INFRASTRUCTURE for two reasons: to optimise student success, and to enable their own researchers to ask foundational questions about learning and teaching in the 21st century\".</p>"));

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

}



MainPage::ContentWidget::ContentWidget()
{

}
