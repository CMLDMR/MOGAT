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

    mContainer = mLayout->addWidget(cpp14::make_unique<WContainerWidget>(),1,AlignmentFlag::Justify);

    auto layout = mContainer->setLayout(cpp14::make_unique<WHBoxLayout>());


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
    }

    auto col = db->collection(DB::User::collection);

    try {
        bsoncxx::stdx::optional<bsoncxx::document::value> result = col.find_one(doc.view());

        if( result )
        {
            if( !result.value().view().empty() )
            {
                userloginFail->setText(WString::fromUTF8(result.value().view()[DB::User::name.c_str()].get_utf8().value.to_string().c_str()));

                mContainer->clear();
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


}

Admin::ControlPanel::ControlPanel(mongocxx::database *_db)
{

}
