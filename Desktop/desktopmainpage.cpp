#include "desktopmainpage.h"
#include "aboutpagewidget.h"
#include "objectivepagewidget.h"
#include "scopepagewidget.h"
#include "homepagewidget.h"

#include "intro.h"


MainPage::DesktopMainPage::DesktopMainPage(int _w, int _h, double _r)
    :Ratio(_r),
      Width(_w),
      Height(_h)
{

    mLayout = setLayout(cpp14::make_unique<WVBoxLayout>());

    mLayout->setContentsMargins(0,0,0,0);

    auto mheader = mLayout->addWidget(cpp14::make_unique<intro::Header>(),0,AlignmentFlag::Top|AlignmentFlag::Justify);

    mLayout->addWidget(cpp14::make_unique<Body>(),0,Wt::AlignmentFlag::Center);

    mLayout->addWidget(cpp14::make_unique<intro::Footer>(),0,AlignmentFlag::Justify);

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

    setMaximumSize(WLength(1280),WLength::Auto);

    Wt::WNavigationBar *navigation =
        layout->addWidget(Wt::cpp14::make_unique<Wt::WNavigationBar>());

    navigation->setTitle("MOGAT","192.168.3.220");

    navigation->setId("navigationID");

    navigation->addStyleClass("navfont");

    navigation->setResponsive(true);

    Wt::WAnimation animation(Wt::AnimationEffect::Fade,
                 Wt::TimingFunction::Linear,
                 200);

    auto leftMenu = Wt::cpp14::make_unique<Wt::WMenu>();

    auto leftMenu_ = navigation->addMenu(std::move(leftMenu),AlignmentFlag::Left);

    auto homeItem = leftMenu_->addItem("icon/btn-flat.jpg","HOME", this,&Body::f_Mogat);

    auto scopeItem = leftMenu_->addItem("icon/btn-flat.jpg","SCOPE", this,&Body::f_Scope);

    auto objItem = leftMenu_->addItem("icon/btn-flat.jpg","OBJECTIVE", this,&Body::f_objective);

    auto rightMenu = Wt::cpp14::make_unique<Wt::WMenu>();

    auto rightMenu_ = navigation->addMenu(std::move(rightMenu),AlignmentFlag::Right);

    auto aboutItem = rightMenu_->addItem("icon/btn-flat.jpg","ABOUT", this,&Body::f_About);

}

void MainPage::Body::f_Mogat()
{
    mContentWidget->clear();

    mContentWidget->addWidget(cpp14::make_unique<HomePageWidget>());


    this->f_relocateFooter();

}

void MainPage::Body::f_Scope()
{
    mContentWidget->clear();

    mContentWidget->addWidget(cpp14::make_unique<ScopePageWidget>());

    this->f_relocateFooter();
}

void MainPage::Body::f_objective()
{

    mContentWidget->clear();

    mContentWidget->addWidget(cpp14::make_unique<ObjectivePageWidget>());

    this->f_relocateFooter();

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

    mContentWidget->addWidget(cpp14::make_unique<AboutPageWidget>());
}

void MainPage::Body::f_contact()
{
    mContentWidget->clear();
    auto title = mContentWidget->addWidget(cpp14::make_unique<WText>("<h1>Contact Content Will be Added</h1>"));

    auto content = mContentWidget->addWidget(cpp14::make_unique<WText>("Contrary to popular belief, Lorem Ipsum is not simply random text. It has roots in a piece of classical Latin literature from 45 BC, making it over 2000 years old. Richard McClintock, a Latin professor at Hampden-Sydney College in Virginia, looked up one of the more obscure Latin words, consectetur, from a Lorem Ipsum passage, and going through the cites of the word in classical literature, discovered the undoubtable source. Lorem Ipsum comes from sections 1.10.32 and 1.10.33 of \"de Finibus Bonorum et Malorum\" (The Extremes of Good and Evil) by Cicero, written in 45 BC. This book is a treatise on the theory of ethics, very popular during the Renaissance. The first line of Lorem Ipsum, \"Lorem ipsum dolor sit amet..\", comes from a line in section 1.10.32"));

}

void MainPage::Body::f_relocateFooter()
{
    this->doJavaScript("var rect = document.getElementById(\"footerid\").getBoundingClientRect();"
                        "console.log(rect.top, rect.right, rect.bottom, rect.left, rect.width, rect.height );"
                        ""
                        "var w = window.innerWidth"
                        "|| document.documentElement.clientWidth"
                        "|| document.body.clientWidth;"
                        "var h = window.innerHeight"
                        "|| document.documentElement.clientHeight"
                        "|| document.body.clientHeight;"
                        "console.log(\"width: \" + w + \" Height: \" + h);"
                        "if( rect.bottom + 3 < h )"
                        "{"
                        "console.log(\"set position relative\");"
                        "document.getElementById(\"footerid\").style.position = \"relative\";"
                        "}else{"
                        "console.log(\"set position fixed bottom:0px\");"
//                        "document.getElementById(\"footerid\").style.bottom = \"-3px\";"
                        "document.getElementById(\"footerid\").style.position = \"relative\";"
                        "}");
}



MainPage::ContentWidget::ContentWidget()
{

}
