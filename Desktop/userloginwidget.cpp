#include "userloginwidget.h"

#include "mongoheaders.h"
#include "db.h"





Admin::UserLoginWidget::UserLoginWidget(mongocxx::database *_db)
    :db(_db)
{

    mtimer = addChild(std::make_unique<WTimer>());
    mtimer->setInterval(std::chrono::seconds(1));
    mtimer->timeout().connect(this,&Admin::UserLoginWidget::timeout);

    mLayout = setLayout(cpp14::make_unique<WHBoxLayout>());

    mContainer = mLayout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Justify);
    mContainer->setId("mContentContainer");

    auto layout = mContainer->setLayout(cpp14::make_unique<WHBoxLayout>());

    auto title = layout->addWidget(cpp14::make_unique<WText>("<h3>Authorized Login</h3>"));


    layout->addStretch(1);
    auto vLayout = layout->addLayout(cpp14::make_unique<WVBoxLayout>());
    layout->addStretch(1);


    vLayout->addSpacing(150);
    vLayout->addStretch(1);
    auto gridLayout = vLayout->addLayout(cpp14::make_unique<WGridLayout>());
    vLayout->addStretch(1);

    vLayout->addSpacing(150);

    gridLayout->addWidget(cpp14::make_unique<WText>("Username"),0,0,AlignmentFlag::Center|AlignmentFlag::Middle);
    gridLayout->addWidget(cpp14::make_unique<WText>("Password"),1,0,AlignmentFlag::Center|AlignmentFlag::Middle);

    username = gridLayout->addWidget(cpp14::make_unique<WLineEdit>(),0,1,AlignmentFlag::Center|AlignmentFlag::Middle);
    username->setPlaceholderText("User Name");
    password = gridLayout->addWidget(cpp14::make_unique<WLineEdit>(),1,1,AlignmentFlag::Center|AlignmentFlag::Middle);
    password->setEchoMode(EchoMode::Password);
    password->setPlaceholderText("Password");

    loginButton = gridLayout->addWidget(cpp14::make_unique<WPushButton>("Login"),2,0,0,2,AlignmentFlag::Center);

    userloginFail = gridLayout->addWidget(cpp14::make_unique<WText>("Please fill required in the Area"),3,0,0,2,AlignmentFlag::Center);

    loginButton->clicked().connect(this,&UserLoginWidget::login);
}

void Admin::UserLoginWidget::timeout()
{
    std::cout << "timer Working " << timerValue++ << std::endl;
    if( timerValue > 10 )
    {
        timerValue = 0;
        userloginFail->setText(WString("Area Enabled, Renew your identification!"));
        mtimer->stop();
        password->setEnabled(true);
        loginButton->setEnabled(true);

    }else{
        userloginFail->setText(WString("Wait, {1} will be enabled").arg(10 - timerValue));

    }
}

void Admin::UserLoginWidget::login()
{

    using bsoncxx::builder::basic::kvp;

    bsoncxx::builder::basic::document doc;

    try {
        doc.append(kvp(DB::User::username,bsoncxx::types::b_utf8{username->text().toUTF8().c_str()}));
        doc.append(kvp(DB::User::password,bsoncxx::types::b_utf8{password->text().toUTF8().c_str()}));
    } catch (bsoncxx::exception &e) {
        std::cout << "bson error: " << e.what() << std::endl;
        mContainer->addWidget(cpp14::make_unique<WText>("bson CXX error: username : password"));
        return;
    }

    auto col = db->collection(DB::User::collection);

    try {
        bsoncxx::stdx::optional<bsoncxx::document::value> result = col.find_one(doc.view());

        if( result )
        {
            if( !result.value().view().empty() )
            {
                userloginFail->setText(WString::fromUTF8(result.value().view()[DB::User::name.c_str()].get_utf8().value.to_string().c_str()));
                useroid = result.value().view()[DB::User::oid.c_str()].get_oid().value;
                std::cout<< "USER OID : " << useroid.to_string() << std::endl;
                mContainer->clear();
                mContainer->addWidget(cpp14::make_unique<ControlPanel>(db));
                mContainer->setMargin(WLength::Auto,AllSides);
            }else{
                std::cout << "Starting Timer: "<< std::endl;
                password->setEnabled(false);
                loginButton->setEnabled(false);
                timerValue = 0;
                mtimer->start();
            }
        }else{
            std::cout << "Starting Timerzx: "<< std::endl;
            password->setEnabled(false);
            loginButton->setEnabled(false);
            timerValue = 0;
            mtimer->start();
        }

    } catch (mongocxx::exception &e) {
        std::cout << "col find error: " << e.what() << std::endl;
    }

}

Admin::NewsContent::NewsContent(mongocxx::database *_db)
{

    auto mLayout = setLayout(cpp14::make_unique<WVBoxLayout>());

    auto mContaier = mLayout->addWidget(cpp14::make_unique<WContainerWidget>());

    auto layout = mContaier->setLayout(cpp14::make_unique<WVBoxLayout>());

    layout->addWidget(cpp14::make_unique<WText>("Haberler"));
}

Admin::ControlPanel::ControlPanel(mongocxx::database *_db)
    :db(_db)
{
    setId("ControlPanel");

    mLayout = setLayout(cpp14::make_unique<WHBoxLayout>());



    auto container = mLayout->addWidget(cpp14::make_unique<WContainerWidget>(),1,AlignmentFlag::Justify);



    mContentStack = container->addWidget(cpp14::make_unique<WStackedWidget>());

    mContentStack->setId("mContentStack");



    {
        auto container = cpp14::make_unique<WContainerWidget>();
        auto HaberButton = container.get()->addWidget(cpp14::make_unique<WPushButton>("News"));
        auto AnounceButton = container.get()->addWidget(cpp14::make_unique<WPushButton>("Anounces"));
        mContentStack->insertWidget(0,std::move(container));

        HaberButton->clicked().connect([=](){
            mContentStack->setCurrentIndex(1);
//            doJavaScript("fooreposition();");
        });

        AnounceButton->clicked().connect([=](){
            mContentStack->setCurrentIndex(2);
        });
    }


    {
        auto container = cpp14::make_unique<WContainerWidget>();
        auto haberler = container.get()->addWidget(cpp14::make_unique<HaberPanel>(db));
        mContentStack->insertWidget(1,std::move(container));

//        haberler->backControlPanel.connect([=](){
//            mContentStack->setCurrentIndex(0);
//        });
    }

    {
        auto container = cpp14::make_unique<WContainerWidget>();
        auto anounce = container.get()->addWidget(cpp14::make_unique<AnouncePanel>(db));
        mContentStack->insertWidget(2,std::move(container));

//        anounce->backControlPanel.connect([=](){
//            mContentStack->setCurrentIndex(0);
//        });
    }

    mContentStack->setCurrentIndex(0);




}

Admin::ControlPanel::HaberPanel::HaberPanel(mongocxx::database* _db)
    :WContainerWidget(),
    db(_db)
{

//    addStyleClass("borderLine");

    auto hLayout = setLayout(cpp14::make_unique<WHBoxLayout>());

    auto mainContainer = hLayout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Left);
    mainContainer->setContentAlignment(AlignmentFlag::Center);

    mLayout = mainContainer->setLayout(cpp14::make_unique<WVBoxLayout>());
    mLayout->addWidget(cpp14::make_unique<WText>("<h3>Your Latest News...</h3>"),0,AlignmentFlag::Center);
    mContainer = mLayout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Right);
    mContainer->setMaximumSize(300,WLength::Auto);
    mContainer->setMargin(WLength::Auto,AllSides);
    Layout = mContainer->setLayout(cpp14::make_unique<WVBoxLayout>());


    {
        haberListWidget = Layout->addWidget(cpp14::make_unique<WContainerWidget>());
        this->refreshList(haberListWidget);
    }



    {
        auto controlLayout = Layout->addLayout(cpp14::make_unique<WHBoxLayout>(),0,AlignmentFlag::Center);
        auto newNewsButton = controlLayout->addWidget(cpp14::make_unique<WPushButton>("Add New"),0,AlignmentFlag::Center);
        newNewsButton->clicked().connect(this,&Admin::ControlPanel::HaberPanel::addNews);
//        auto EditNews = controlLayout->addWidget(cpp14::make_unique<WPushButton>("Edit Selected"),0,AlignmentFlag::Center);
//        auto DeleteNews = controlLayout->addWidget(cpp14::make_unique<WPushButton>("Delete Selected"),0,AlignmentFlag::Center);
    }

    {
        auto backbutton = Layout->addWidget(cpp14::make_unique<WPushButton>("Back"));
//        backbutton->clicked().connect([=](){
//            backControlPanel.emit();
//        });
    }

    mDetailContainer = hLayout->addWidget(cpp14::make_unique<WContainerWidget>(),1,AlignmentFlag::Justify);

    {
        auto vLayout = mDetailContainer->setLayout(cpp14::make_unique<WVBoxLayout>());

        // icon select if exist image
        if(0){
            auto container = vLayout->addWidget(cpp14::make_unique<Wt::WContainerWidget>());

//            char *wtTmpDir = std::getenv("WT_TMP_DIR");
//            std::cout << "TEMPDIR: " << wtTmpDir << std::endl;

            Wt::WFileUpload *fu =
                container->addWidget(Wt::cpp14::make_unique<Wt::WFileUpload>());
            fu->setFileTextSize(500); // Set the maximum file size to 50 kB.
            WProgressBar* pBar = container->addWidget(cpp14::make_unique<WProgressBar>());

            fu->setProgressBar(pBar);
//            container->addWidget(fu->progressBar());
            fu->setMargin(10, Wt::Side::Right);

            // Provide a button to start uploading.
            Wt::WPushButton *uploadButton =
                container->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Send"));
            uploadButton->setMargin(10, Wt::Side::Left | Wt::Side::Right);

            Wt::WText *out = container->addWidget(Wt::cpp14::make_unique<Wt::WText>());

            // Upload when the button is clicked.
            uploadButton->clicked().connect([=] {

                fu->upload();
                uploadButton->disable();
            });

            // Upload automatically when the user entered a file.
            fu->changed().connect([=] {
                fu->upload();
                uploadButton->disable();
                out->setText("File upload is changed.");

            });

            // React to a succesfull upload.
            fu->uploaded().connect([=] {
                out->setText("File upload is finished.");
                std::cout << "CLINE TFONE NAME: " << fu->clientFileName().toUTF8().c_str() << std::endl;
                std::cout << "CLINE TFONE NAME: " << fu->contentDescription().toUTF8().c_str() << std::endl;
                std::cout << "CLINE TFONE NAME: " << fu->spoolFileName() << std::endl;
                QFileInfo info(QString::fromStdString(fu->spoolFileName()));

                std::cout << "File Dir: " << info.absolutePath().toStdString().c_str() << std::endl;

                QFile file(fu->spoolFileName().c_str() );
                if( file.open(QIODevice::ReadOnly) )
                {
                    QByteArray ar = file.readAll();
                    file.close();

                    file.setFileName(info.absolutePath()+"/11.jpeg");

                    std::cout << QDir::currentPath().toStdString().c_str() << std::endl;

                    if( file.open(QIODevice::ReadWrite) )
                    {
                        file.write(ar);
                        file.close();

                        QString str = QString::fromStdString(edit->text().toUTF8());
                        str.append("<img src="+info.absolutePath()+"/11.jpeg>");
                        edit->setText(str.toStdString());
                        std::cout << edit->text().toUTF8().c_str() << std::endl;
                    }
                }else{
                    std::cout << "FILE CAN NOT READ " << std::endl;
                }
            });

            // React to a file upload problem.
            fu->fileTooLarge().connect([=] {
                out->setText("File is too large.");
            });

        }




        {
            auto hlayout = vLayout->addLayout(cpp14::make_unique<WHBoxLayout>());
            mTitle = hlayout->addWidget(cpp14::make_unique<WLineEdit>(),0,AlignmentFlag::Center|AlignmentFlag::Middle);
            mTitle->setPlaceholderText("News Title");

            {
                auto _layout = vLayout->addLayout(cpp14::make_unique<WHBoxLayout>());
                auto tetx = _layout->addWidget(cpp14::make_unique<WText>("Publish"));
                mPublished = _layout->addWidget(cpp14::make_unique<WCheckBox>());
                _layout->addStretch(1);

                mNewsoid = _layout->addWidget(cpp14::make_unique<WLineEdit>());
                mNewsoid->setMaximumSize(350,WLength::Auto);
                mNewsoid->setEnabled(false);
                mDeleteNews = _layout->addWidget(cpp14::make_unique<WPushButton>("Delete This"));
                mDeleteNews->clicked().connect(this,&Admin::ControlPanel::HaberPanel::deleteNews);

            }

            auto container = vLayout->addWidget(cpp14::make_unique<Wt::WContainerWidget>());
            edit = container->addWidget(Wt::cpp14::make_unique<Wt::WTextEdit>());
            edit->setHeight(450);
            edit->setWidth(650);
            edit->setText("<p>"
                "<span style=\"font-family: 'courier new', courier; font-size: medium;\">"
                "<strong>News Content Here(Remove Content to Start)</strong></span></p>"
                  "<ul style=\"padding: 0px; margin: 0px 0px 10px 25px;\">"
                    "<li>Line 1</li>"
                    "<li>Line 2</li>"
                    "<li>Line 3</li>"
                  "</ul>");

            Wt::WPushButton *button =
            container->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Save"));
            button->setMargin(10, Wt::Side::Top | Wt::Side::Bottom);

            button->clicked().connect([=](){

                this->saveNews();

            });

            vLayout->addStretch(1);
        }
    }

    SelectedNewsIndex.connect(this,&HaberPanel::NewsDetail);

}

void Admin::ControlPanel::HaberPanel::refreshList(WContainerWidget *itemWidget)
{
    itemWidget->clear();

    auto mainContainer = itemWidget->addWidget(cpp14::make_unique<WContainerWidget>());

    auto itemLayout = mainContainer->setLayout(cpp14::make_unique<WVBoxLayout>());

    haberList = this->getHaberList();

    for(int i = 0 ; i < haberList.size() ; i++ )
    {
        auto doc = haberList[i];

        auto container = itemLayout->addWidget(cpp14::make_unique<WContainerWidget>());
        container->addStyleClass("borderLine newsListItem");
        container->setContentAlignment(AlignmentFlag::Center);
        auto layout = container->setLayout(cpp14::make_unique<WVBoxLayout>());
        layout->addWidget(cpp14::make_unique<WText>(doc.title));


        container->clicked().connect([=](){
            std::cout << "Bind Oid " << i/*<< doc[DB::News::Newsoid].get_oid().value.to_string()*/ << std::endl;
            SelectedNewsIndex.emit(i);
            mDeleteNews->setEnabled(true);
        });


    }
}

void Admin::ControlPanel::HaberPanel::NewsDetail(int index)
{
    auto doc = haberList[index];
    std::cout << "News Detail : "<<index << doc.oid << std::endl;

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_document;

    bsoncxx::builder::basic::document filter{};

    try {
        filter.append(kvp(DB::News::Newsoid,bsoncxx::oid{doc.oid}));
    } catch (bsoncxx::exception &e) {
        std::cout << "Error Parsing " << e.what() << std::endl;
    }

    auto col = db->collection(DB::News::collection);

    try {
        mongocxx::stdx::optional<bsoncxx::document::value> res = col.find_one(filter.view());

        if( res )
        {
            edit->setText(WString(res.get().view()[DB::News::html].get_utf8().value.to_string().c_str()));
            mTitle->setText(WString(res.get().view()[DB::News::title].get_utf8().value.to_string().c_str()));
            mPublished->setChecked(res.get().view()[DB::News::published].get_bool().value);
            mNewsoid->setText(res.get().view()[DB::News::Newsoid].get_oid().value.to_string());

        }
    } catch (mongocxx::exception &e) {
        std::cout << "mongocxx : " << e.what() << std::endl;
    }






}

void Admin::ControlPanel::HaberPanel::saveNews()
{

    if( mTitle->text().empty() )
    {
        auto messageBox = this->addChild(
                Wt::cpp14::make_unique<Wt::WMessageBox>
                ("Warning",
                 Wt::WString("<p>You Can not save without Title</p>"),
                 Wt::Icon::Information, Wt::StandardButton::Ok));

        messageBox->buttonClicked().connect([=] {
                        this->removeChild(messageBox);
                    });

        messageBox->show();

        return;
    }

    if( edit->text().toUTF8().size() < 250 )
    {
        auto messageBox = this->addChild(
                Wt::cpp14::make_unique<Wt::WMessageBox>
                ("Warning",
                 Wt::WString("<p>News Content is Too Short</p>"
                             "<p>Fill more than 250 Characters</p>"),
                 Wt::Icon::Information, Wt::StandardButton::Ok));

        messageBox->buttonClicked().connect([=] {
                        this->removeChild(messageBox);
                    });

        messageBox->show();

        return;
    }

    if( mNewsoid->text().toUTF8().size() )
    {
        this->changeNews();
        return;
    }



    using bsoncxx::builder::basic::kvp;

    auto col = db->collection(DB::News::collection);
    auto doc = bsoncxx::builder::basic::document{};

    try {
        doc.append(kvp(DB::News::title,bsoncxx::types::b_utf8{mTitle->text().toUTF8().c_str()}));
        doc.append(kvp(DB::News::html,bsoncxx::types::b_utf8{edit->text().toUTF8().c_str()}));
        doc.append(kvp(DB::News::clickCount,bsoncxx::types::b_int64{0}));
        doc.append(kvp(DB::News::published,bsoncxx::types::b_bool{DB::News::publishState::OFF}));
        doc.append(kvp(DB::News::authoroid,useroid));
        doc.append(kvp(DB::News::published,bsoncxx::types::b_bool{mPublished->isChecked()}));
    } catch (bsoncxx::exception &e) {
        std::cout << "bson cxx : " << e.what() << std::endl;
    }

    try {
        mongocxx::stdx::optional<mongocxx::result::insert_one> res = col.insert_one(doc.view());
        if( res )
        {
            std::cout << "res : " << res.value().result().inserted_count() << std::endl;

            this->refreshList(haberListWidget);
            this->addNews();
        }else{
            std::cout << "No Doc inserted " << std::endl;
        }
    } catch (mongocxx::exception &e) {
        std::cout << e.what() << std::endl;
    }

}

void Admin::ControlPanel::HaberPanel::deleteNews()
{

        if( !mNewsoid->text().empty() )
        {
            auto filter = bsoncxx::builder::basic::document{};
            try {
                filter.append(bsoncxx::builder::basic::kvp(DB::News::Newsoid,bsoncxx::oid{mNewsoid->text().toUTF8().c_str()}));
                auto col = db->collection(DB::News::collection);
                try {
                    mongocxx::stdx::optional<mongocxx::result::delete_result> del = col.delete_one(filter.view());
                    if( del )
                    {
                        if( del.get().deleted_count() )
                        {
                            edit->setText("");
                            mNewsoid->setText("");
                            mTitle->setText("");
                            this->refreshList(haberListWidget);
                            this->MessageBox("info","<p>Selected News Deleted</p>");
                        }else{
                            std::cout << "no Deleted News " << std::endl;
                        }
                    }else{
                        std::cout << "No Del pointer" << std::endl;
                    }
                } catch (mongocxx::exception &e) {
                    std::cout << "delete one error: " << e.what() << std::endl;
                }
            } catch (bsoncxx::exception &e) {
                std::cout << "BSON CXX Parsing Error: " << e.what() << std::endl;
            }
        }else{
            this->MessageBox("info","<p>No Deletable İtem Found</p>");
        }



}

void Admin::ControlPanel::HaberPanel::addNews()
{
    edit->setText("");
    mTitle->setText("");
    mNewsoid->setText("");
    mPublished->setChecked(false);
    mDeleteNews->setEnabled(false);
}

void Admin::ControlPanel::HaberPanel::changeNews()
{
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_document;




    auto filter = bsoncxx::builder::basic::document{};

    try {
        filter.append(kvp(DB::News::Newsoid,bsoncxx::oid{mNewsoid->text().toUTF8().c_str()}));
    } catch (bsoncxx::exception &e) {
        std::cout << "Error bsoncxx " << e.what() << std::endl;
        return;
    }


    auto col = db->collection(DB::News::collection);
    auto doc = bsoncxx::builder::basic::document{};
    auto setdoc = bsoncxx::builder::basic::document{};

    try {
        doc.append(kvp(DB::News::title,bsoncxx::types::b_utf8{mTitle->text().toUTF8().c_str()}));
        doc.append(kvp(DB::News::html,bsoncxx::types::b_utf8{edit->text().toUTF8().c_str()}));
        doc.append(kvp(DB::News::authoroid,useroid));
        doc.append(kvp(DB::News::published,bsoncxx::types::b_bool{mPublished->isChecked()}));
    } catch (bsoncxx::exception &e) {
        std::cout << "bson cxx : " << e.what() << std::endl;
        return;
    }

    try {
        setdoc.append(kvp("$set",bsoncxx::types::b_document{doc}));
    } catch (bsoncxx::exception &e) {
        std::cout << "Error $set file bsoncxx: " << std::endl;
        return;
    }

    try {
        mongocxx::stdx::optional<mongocxx::result::update> upt = col.update_one(filter.view(),setdoc.view());
        if( upt )
        {
            std::cout << "res : " << upt.get().modified_count() << std::endl;

            if( upt.get().modified_count() )
            {
                this->MessageBox("info", "<p>Content Changed</p>");
                this->refreshList(haberListWidget);
            }else{
                this->MessageBox("Warning", "<p>No Content Changed</p>");
            }
        }else{
            std::cout << "No Doc updated " << std::endl;
        }
    } catch (mongocxx::exception &e) {
        std::cout << "mongocxx update error: "<<e.what() << std::endl;
    }
}

void Admin::ControlPanel::HaberPanel::MessageBox(std::string title, std::string message)
{
    auto messageBox = this->addChild(
            Wt::cpp14::make_unique<Wt::WMessageBox>
            (title,
             Wt::WString(message),
             Wt::Icon::Information, Wt::StandardButton::Ok));

    messageBox->buttonClicked().connect([=] {
                    this->removeChild(messageBox);
                });

    messageBox->show();

    return;
}

std::vector<Admin::ControlPanel::HaberPanel::NewsItem> Admin::ControlPanel::HaberPanel::getHaberList()
{
    using bsoncxx::builder::basic::kvp;

    auto filter = bsoncxx::builder::basic::document{};

    std::vector<NewsItem> docList;

    try {
        filter.append(kvp(DB::News::authoroid,useroid));

        auto col = db->collection(DB::News::collection);

        try {

            mongocxx::options::find findOptions;

            auto findoptionKay = bsoncxx::builder::basic::document{};

            try {
                findoptionKay.append(kvp(DB::News::html,bsoncxx::types::b_bool{false}));
            } catch (bsoncxx::exception &e) {
                std::cout << "findOption Parsing Error: " << e.what() << std::endl;
            }

            findOptions.projection(findoptionKay.view());

            auto cursor = col.find(filter.view(),findOptions);

            for( auto doc : cursor )
            {
                NewsItem item;
                item.oid = doc[DB::News::Newsoid].get_oid().value.to_string();
                item.title = doc[DB::News::title].get_utf8().value.to_string();
                item.published = doc[DB::News::published].get_bool().value;
                docList.push_back(item);
            }

        } catch (mongocxx::exception& e) {
            std::cout << "error mongocxx exception: " << e.what() << std::endl;
        }

    } catch (bsoncxx::exception &e) {
        std::cout << "bsoncxx exception error: "<<e.what() << std::endl;
    }

    return docList;

}

bool Admin::ControlPanel::HaberPanel::enableNews(bool enable, NewsItem doc)
{

    std::cout << "ENABLE : " << enable << std::endl;
    bool returnValue = false;

    auto filter = bsoncxx::builder::basic::document{};
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_document;
    try {
        filter.append(kvp(DB::News::Newsoid,bsoncxx::oid{doc.oid}));
        auto updatedoc = bsoncxx::builder::basic::document{};

        try {
            updatedoc.append(kvp("$set",make_document(kvp(DB::News::published,bsoncxx::types::b_bool{enable}))));
        } catch (bsoncxx::exception &e) {
            std::cout << "Error bsoncxx : " << e.what() << std::endl;
        }

        std::cout << "FITER: " << bsoncxx::to_json(filter.view());
        std::cout << "UPDATE: " << bsoncxx::to_json(updatedoc.view());

        auto col = db->collection(DB::News::collection);
        try {

            mongocxx::stdx::optional<mongocxx::result::update> result = col.update_one(filter.view(),updatedoc.view());

            if( result )
            {
                std::cout << "RESULT UPDATE: " << result.get().modified_count() << std::endl;
                if( result.get().modified_count() ) returnValue = true;
            }else{

            }
        } catch (mongocxx::exception &e) {
            std::cout << "mongocxx error: " << e.what() << std::endl;
        }

    } catch (bsoncxx::exception &e) {
        std::cout << "bsoncxx: " << e.what() << std::endl;
    }

    return returnValue;

}

bool Admin::ControlPanel::HaberPanel::disableNews(NewsItem doc)
{

    bool returnValue = false;

    auto filter = bsoncxx::builder::basic::document{};
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_document;
    try {
        filter.append(kvp(DB::News::Newsoid,bsoncxx::oid{doc.oid}));
        auto updatedoc = bsoncxx::builder::basic::document{};

        updatedoc.append(kvp("$set",make_document(kvp(DB::News::published,bsoncxx::types::b_bool{true}))));

        auto col = db->collection(DB::News::collection);
        try {

            mongocxx::stdx::optional<mongocxx::result::update> result = col.update_one(filter.view(),updatedoc.view());


            if( result )
            {
                std::cout << "RESULT UPDATE: " << result.get().modified_count() << std::endl;
                if( result.get().modified_count() ) returnValue = true;
            }else{

            }
        } catch (mongocxx::exception &e) {
            std::cout << "mongocxx error: " << e.what() << std::endl;
        }

    } catch (bsoncxx::exception &e) {
        std::cout << "bsoncxx: " << e.what() << std::endl;
    }

    return returnValue;
}



Admin::ControlPanel::AnouncePanel::AnouncePanel(mongocxx::database *_db)
    :db(_db)
{
    setMaximumSize(400,WLength::Auto);
    addStyleClass("borderLine");

    mLayout = setLayout(cpp14::make_unique<WVBoxLayout>());
    mLayout->addWidget(cpp14::make_unique<WText>("<h3>Your Latest Anounce...</h3>"),0,AlignmentFlag::Center);
    mContainer = mLayout->addWidget(cpp14::make_unique<WContainerWidget>(),0,AlignmentFlag::Justify);
    Layout = mContainer->setLayout(cpp14::make_unique<WVBoxLayout>());


    for( int i = 0 ; i < 10 ; i++ )
    {
        Layout->addWidget(cpp14::make_unique<WText>(WString(" Artist and song name displayed in the top left corner of the video.{1}").arg(i)),0,AlignmentFlag::Justify)->addStyleClass("borderLine");
    }

    {
        auto controlLayout = Layout->addLayout(cpp14::make_unique<WHBoxLayout>(),1,AlignmentFlag::Justify);
        auto newAnounceButton = controlLayout->addWidget(cpp14::make_unique<WPushButton>("Add New"),1,AlignmentFlag::Center);
//        auto EditAnounce = controlLayout->addWidget(cpp14::make_unique<WPushButton>("Edit Selected"),1,AlignmentFlag::Center);
//        auto DeleteAnounce = controlLayout->addWidget(cpp14::make_unique<WPushButton>("Delete Selected"),1,AlignmentFlag::Center);
    }

    {
        {
            auto backbutton = Layout->addWidget(cpp14::make_unique<WPushButton>("Back"));

//            backbutton->clicked().connect([=](){
//                backControlPanel.emit();
//            });
        }
    }


}
