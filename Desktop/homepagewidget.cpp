#include "homepagewidget.h"

HomePage::HomePageWidget::HomePageWidget()
{

    setId("HomePageWidget");



    setContentAlignment(AlignmentFlag::Justify);

    mMainContainer = addWidget(cpp14::make_unique<WContainerWidget>());

    this->initLayout(mMainContainer);

}

void HomePage::HomePageWidget::initLayout(WContainerWidget *container)
{

    auto mLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

    mLayout->addWidget(cpp14::make_unique<WImage>(WLink("img/homepic1.png")))->addStyleClass("homeimg");


    mLayout->addWidget(cpp14::make_unique<WText>("<p>The Outcomes of the Project</p>"))->addStyleClass("outComes");

    {
        auto container = mLayout->addWidget(cpp14::make_unique<WContainerWidget>());

        auto layout = container->setLayout(cpp14::make_unique<WHBoxLayout>());


        layout->addWidget(cpp14::make_unique<WText>("<strong>The outcomes of this project will help the target groups to overcome the constraints of current situation in L2 courses thanks to</strong>"
                                            "<p>■ the introduction of an advanced L2 programme for the Tourism Sector using a gamified learning methodology with  knowledge competitions;</p>"
                                            "<p>■ an industry oriented approach: the project is supported by major HRD departments of European business stakeholders</p>"
                                            "<p>■ they will participate in the L2 tournaments and become direct beneficiaries of the project;</p>"
                                            "<p>■ providing a mobile and ubiquitous learning and training opportunity;</p>"
                                            "<p>■ embedding learning analytics in a game: for the learners in the sense of  quantified self, for the institutions and enterprises in the form of anonymous collective diagnostics;</p>"
                                            "<p>■ a strong personalized learner orientation with a new motivating and engaging gamification approach, which will be further evaluated in the course of  the project.</p>"))->addStyleClass("homeText");

        layout->addWidget(cpp14::make_unique<WImage>(WLink("img/outcomesproject.png")))->addStyleClass("outcomesproject");
        mLayout->addWidget(cpp14::make_unique<WImage>(WLink("img/outcomesproject.png")),0,AlignmentFlag::Center)->addStyleClass("outcomesprojectmobile");

    }





    {

        auto container = mLayout->addWidget(cpp14::make_unique<WContainerWidget>());

        auto layout = container->setLayout(cpp14::make_unique<WHBoxLayout>());

        layout->addWidget(cpp14::make_unique<WImage>(WLink("img/impactdesired.png")),0,AlignmentFlag::Middle)->addStyleClass("outcomesproject");

        layout->addWidget(cpp14::make_unique<WText>("<p><b>IMPACT desired</b></p>"
                         "<p>The project will describe organisational models, "
                                                    "suggest delivery structures and provide a basis for assessing the "
                                                    "potentials based on the experiences gained in its activities. The valorisation "
                                                    "strategy and the project model itself  will have a positive impact since it will "
                                                    "show how to increase access and retention in life long learning  for the specific "
                                                    "target group in the tourism industry.</p>"
                         "<p>Teachers, trainers, educational providers and stakeholders will learn about a suitable model of learning "
                                                    "that can be used in the tourism sector  and that has the potential of raising attractiveness "
                                                    "for learning foreign languages. Raising of awareness for the problem and the possibilities "
                                                    "of modern language learning and training for tourism enterprises and their staff as well as "
                                                    "schools and universities operating in the sector of tourism and stakeholders in the tourism "
                                                    "industry will be done in all countries of the project and further. An active analytics infrastructure "
                                                    "will be created and at the disposal of any interested person or organisation. Quote from an "
                                                    "UNESCO publication (Nov. 2012): \"Compared to many other sectors, educational institutions are "
                                                    "currently 'driving blind'. They should invest in ANALYTICS INFRASTRUCTURE for two reasons: to "
                                                    "optimise student success, and to enable their own researchers to ask foundational questions about "
                                                    "learning and teaching in the 21st century\".</p>"))->addStyleClass("homeText");

        mLayout->addWidget(cpp14::make_unique<WImage>(WLink("img/impactdesired.png")),0,AlignmentFlag::Center)->addStyleClass("outcomesprojectmobile");

    }

}

