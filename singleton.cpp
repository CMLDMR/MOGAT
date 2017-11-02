#include "singleton.h"



Singleton::Singleton(int _width, int _height)
    :Width(_width),Height(_height)
{

//    decorationStyle().setBackgroundImage(WLink("img/Background.jpg"));

    setMinimumSize(WLength::Auto,Height);

    mIntroPage = addWidget(cpp14::make_unique<intro::Intro>());
//    mIntroPage->setStyleClass("Development_of_Innovation");

//    auto container1 = std::make_unique<Wt::WContainerWidget>();
//    container1->addWidget(std::make_unique<Wt::WText>("<h1> SOME TEST </h1>"));
//    container1->addWidget(std::make_unique<Wt::WImage>("images/img.png"));
//    Wt::WContainerWidget *child3 = container1->addWidget(std::make_unique<Wt::WContainerWidget>());
//    // Example 2:
//    // Instantiate a container widget which uses a layout manager
//    auto container2 = std::make_unique<Wt::WContainerWidget>();
//    container2->resize(Wt::WLength::Auto, 600); // give the container a fixed height.
//    auto layout = std::make_unique<Wt::WVBoxLayout>();
//    layout->addWidget(std::make_unique<Wt::WText>("Some text"));
//    layout->addWidget(std::make_unique<Wt::WImage>("images/img.png"));
//    container2->setLayout(std::move(layout));      // set the layout to the container.

//    this->addWidget(std::move(container2));
//    this->addWidget(std::move(container1));


}
