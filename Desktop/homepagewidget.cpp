#include "homepagewidget.h"

HomePage::HomePageWidget::HomePageWidget(mongocxx::database* _db)
    :db(_db),
      WContainerWidget()
{

    setId("HomePageWidget");

    setContentAlignment(AlignmentFlag::Justify);

    mMainContainer = addWidget(cpp14::make_unique<WContainerWidget>());

    this->initLayout(mMainContainer);

}

void HomePage::HomePageWidget::initLayout(WContainerWidget *container)
{

    container->clear();

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

        auto SubContainer = mLayout->addWidget(cpp14::make_unique<WContainerWidget>());
        SubContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_12+Bootstrap::Grid::Medium::col_md_12+Bootstrap::Grid::Small::col_sm_12);



        auto sublargeContainer = SubContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        sublargeContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_9);

        auto subsmallContainer = SubContainer->addWidget(cpp14::make_unique<WContainerWidget>());
        subsmallContainer->addStyleClass(Bootstrap::Grid::Large::col_lg_3);

        {

            auto container = sublargeContainer->addWidget(cpp14::make_unique<WContainerWidget>());
            container->addStyleClass(Bootstrap::Grid::Large::col_lg_12);

            auto layout = container->setLayout(cpp14::make_unique<WHBoxLayout>());

//            layout->addWidget(cpp14::make_unique<WImage>(WLink("img/impactdesired.png")),0,AlignmentFlag::Middle)->addStyleClass("outcomesproject");

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

//            mLayout->addWidget(cpp14::make_unique<WImage>(WLink("img/impactdesired.png")),0,AlignmentFlag::Center)->addStyleClass("outcomesprojectmobile");

        }



        {
            auto container = sublargeContainer->addWidget(cpp14::make_unique<NewsListWidget>(db));
            container->addStyleClass(Bootstrap::Grid::Large::col_lg_12);
            container->ClickedNewsItem().connect(this,&HomePageWidget::setNewsDetail);
        }



        {
            auto container = subsmallContainer->addWidget(cpp14::make_unique<AnounceListWidget>(db));
            container->addStyleClass(Bootstrap::Grid::Large::col_lg_12);
        }




        {

            auto container = subsmallContainer->addWidget(cpp14::make_unique<SuppotersWidget>(db));
            container->addStyleClass(Bootstrap::Grid::Large::col_lg_12);

        }

    }

}

void HomePage::HomePageWidget::setNewsDetail(std::string NewsOid)
{

    mMainContainer->clear();

    auto filter = document{};

    try {
        filter.append(kvp(DB::News::Newsoid,bsoncxx::oid{NewsOid.c_str()}));
    } catch (bsoncxx::exception &e) {
        mMainContainer->addWidget(cpp14::make_unique<WText>(WString("Error bson builder: {1}").arg(e.what())));
        return;
    }

    auto updateField = document{};

    try {
        updateField.append(kvp("$inc",make_document(kvp(DB::News::clickCount,bsoncxx::types::b_int64{1}))));
    } catch (bsoncxx::exception &e) {
        mMainContainer->addWidget(cpp14::make_unique<WText>(WString("Error bson builder: {1}").arg(e.what())));
    }

    auto col = db->collection(DB::News::collection);

    try {
        mongocxx::stdx::optional<bsoncxx::document::value> res = col.find_one_and_update(filter.view(),updateField.view());

        if( res )
        {

            auto container = mMainContainer->addWidget(cpp14::make_unique<WContainerWidget>());

            auto vLayout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

            std::string title = res.get().view()[DB::News::title].get_utf8().value.to_string();
            std::string content = res.get().view()[DB::News::html].get_utf8().value.to_string();

            auto titleText = vLayout->addWidget(cpp14::make_unique<WText>(title));
            titleText->addStyleClass("newsDetailWidgetTitle");
            auto contentTextWidget = vLayout->addWidget(cpp14::make_unique<WContainerWidget>());

            auto text = contentTextWidget->addWidget(cpp14::make_unique<WText>(content));

        }else{
            mMainContainer->addWidget(cpp14::make_unique<WText>(WString("mongocxx Error: no content found!")));
        }
    } catch (mongocxx::exception &e) {
        mMainContainer->addWidget(cpp14::make_unique<WText>(WString("mongocxx Error: {1}").arg(e.what())));
        return;
    }


}


HomePage::NewsListWidget::NewsListWidget(mongocxx::database *_db)
    :WContainerWidget(),
      db(_db)
{

    auto container = addWidget(cpp14::make_unique<WContainerWidget>());

    auto layout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

    layout->addWidget(cpp14::make_unique<WText>("Latest News..."),0,AlignmentFlag::Left)->addStyleClass("BodyNewsListItemWidgetLastestTitle");

    auto filter = document{};

    try {
        filter.append(kvp(DB::News::published,bsoncxx::types::b_bool{DB::News::publishState::ON}));
    } catch (bsoncxx::exception &e) {
        layout->addWidget(cpp14::make_unique<WText>(WString("Error building BSONDOC: {1}").arg(e.what())),0,AlignmentFlag::Left);
        return;
    }


    auto col = db->collection(DB::News::collection);

    try {
        auto cursor = col.find(filter.view());

        for( auto doc : cursor )
        {
            NewsItem item;

            item.oid = doc[DB::News::Newsoid].get_oid().value.to_string();
            item.html = doc[DB::News::html].get_utf8().value.to_string();
            item.title = doc[DB::News::title].get_utf8().value.to_string();
            item.iconPath = doc[DB::News::icon].get_utf8().value.to_string();
            NewsList.push_back(item);
        }

        {
            for( NewsItem item : NewsList )
            {
                auto itemWidget = layout->addWidget(cpp14::make_unique<WContainerWidget>());
                itemWidget->addStyleClass(Bootstrap::Grid::row+"BodyNewsListItemWidget");

//                itemWidget->setMaximumSize(350,WLength::Auto);

                auto hLayout = itemWidget->setLayout(cpp14::make_unique<WHBoxLayout>());


                auto img = hLayout->addWidget(cpp14::make_unique<WImage>(WLink(item.iconPath)));
                img->addStyleClass("iconimgFrame");

                auto itemcontainer = hLayout->addWidget(cpp14::make_unique<WContainerWidget>());
                itemcontainer->setContentAlignment(AlignmentFlag::Left);

                itemcontainer->addWidget(cpp14::make_unique<WText>(item.title))->addStyleClass("BodyNewsListItemTitle");

                itemcontainer->addWidget(cpp14::make_unique<WBreak>());

                QString str = QString::fromStdString(item.html);

                str.remove(QRegExp("<[^>]*>"));

                str = str.mid(0,100) + "...";

                auto content = itemcontainer->addWidget(cpp14::make_unique<WText>(str.toStdString().c_str()));

                content->setTextFormat(TextFormat::Plain);
                content->addStyleClass(Bootstrap::Grid::Large::col_lg_9 + "BodyNewsListItem");
                itemWidget->clicked().connect([=](){
                    ClickedNewsItem_.emit(item.oid);
                });
            }

            layout->addWidget(cpp14::make_unique<WText>("More News..."),0,AlignmentFlag::Center);
        }

    } catch (mongocxx::exception &e) {
        layout->addWidget(cpp14::make_unique<WText>(WString("Error find filter doc: {1}").arg(e.what())),0,AlignmentFlag::Left);
        return;
    }






}

HomePage::AnounceListWidget::AnounceListWidget(mongocxx::database *_db)
{
    auto container = addWidget(cpp14::make_unique<WContainerWidget>());

    auto layout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

    layout->addWidget(cpp14::make_unique<WText>("Anouncesments"),0,AlignmentFlag::Center);

    for( int i = 0 ; i < 5 ; i++ )
    {
        auto item = layout->addWidget(cpp14::make_unique<WContainerWidget>());

        item->setMinimumSize(250,50);
        item->decorationStyle().setBorder(WBorder(BorderStyle::Solid,BorderWidth::Thin));
    }
}

HomePage::SuppotersWidget::SuppotersWidget(mongocxx::database *_db)
{
    auto container = addWidget(cpp14::make_unique<WContainerWidget>());

    auto layout = container->setLayout(cpp14::make_unique<WVBoxLayout>());

    layout->addWidget(cpp14::make_unique<WText>("Suppoters"),0,AlignmentFlag::Center);

    for( int i = 0 ; i < 5 ; i++ )
    {
        auto item = layout->addWidget(cpp14::make_unique<WContainerWidget>());

        item->setMinimumSize(250,50);
        item->decorationStyle().setBorder(WBorder(BorderStyle::Solid,BorderWidth::Thin));
    }
}
