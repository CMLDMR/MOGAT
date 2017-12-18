#ifndef USERLOGINWIDGET_H
#define USERLOGINWIDGET_H

#include <QtCore/qglobal.h>

#include <Wt/WContainerWidget.h>
#include <Wt/WWidget.h>
#include <Wt/WInteractWidget.h>

#include <Wt/WHBoxLayout.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WText.h>
#include <Wt/WLink.h>
#include <Wt/WImage.h>
#include <Wt/WCssDecorationStyle.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WTimer.h>


#include "mongoheaders.h"

#include <memory.h>

using namespace Wt;


namespace Admin {

    class ControlPanel;
    class NewsContent;


    class UserLoginWidget : public WContainerWidget
    {
    public:
        UserLoginWidget(mongocxx::database *_db);

        WLineEdit* username;
        WLineEdit* password;
        WPushButton* loginButton;

        mongocxx::database* db;

        WHBoxLayout* mLayout;
        WContainerWidget* mContainer;

        WText* userloginFail;

        Wt::WTimer* mtimer;
        void timeout();
        int timerValue;

        void login();
    };

    class ControlPanel : public WContainerWidget
    {
        public:
        ControlPanel(mongocxx::database* _db);
    };



    class NewsContent : public WContainerWidget
    {
        public:
        NewsContent(mongocxx::database* _db);

    };

}



#endif // USERLOGINWIDGET_H
