#ifndef USERLOGINWIDGET_H
#define USERLOGINWIDGET_H

#include <QtCore/qglobal.h>
#include <QImage>
#include <QFile>
#include <QByteArray>
#include <QDir>
#include <QFileInfo>

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
#include <Wt/WStackedWidget.h>
#include <Wt/WSignal.h>
#include <Wt/WTextEdit.h>

#include <Wt/WTable.h>
#include <Wt/WTableCell.h>
#include <Wt/WStandardItem.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WStringListModel.h>
#include <Wt/WTableView.h>
#include <Wt/WItemDelegate.h>
#include <Wt/WCheckBox.h>
#include <Wt/WFileUpload.h>
#include <Wt/WProgressBar.h>

#include "mongoheaders.h"

#include <memory.h>

using namespace Wt;


namespace Admin {

    class ControlPanel;
    class NewsContent;

    static bsoncxx::oid useroid;


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

        WHBoxLayout* mLayout;
        std::unique_ptr<WContainerWidget> mContainer;

        mongocxx::database* db;

        WStackedWidget* mContentStack;


        class HaberPanel : public WContainerWidget
        {
            public:
            HaberPanel(mongocxx::database *_db);
            mongocxx::database* db;

            WVBoxLayout* mLayout;
            WContainerWidget* mContainer;
            WContainerWidget* mDetailContainer;
            WVBoxLayout* Layout;
//            Signal<> backControlPanel;

            Signal<int> SelectedNewsIndex;

            Wt::WTextEdit *edit;
            WLineEdit* mTitle;
            WCheckBox* mPublished;


            WContainerWidget* haberListWidget;

            struct NewsItem
            {
                std::string oid;
                std::string title;
                bool published;
            };

            std::vector<NewsItem> haberList;


            void refreshList(WContainerWidget* itemWidget);

            void NewsDetail(int index);

        private:
            std::vector<NewsItem> getHaberList();
            bool enableNews(bool enable, NewsItem doc);
            bool disableNews( NewsItem doc);


        };




        class AnouncePanel : public WContainerWidget
        {
            public:
            AnouncePanel(mongocxx::database *_db);
            mongocxx::database* db;

            WVBoxLayout* mLayout;
            WContainerWidget* mContainer;
            WVBoxLayout* Layout;
//            Signal<> backControlPanel;


        };
    };



    class NewsContent : public WContainerWidget
    {
        public:
        NewsContent(mongocxx::database* _db);

    };

}



#endif // USERLOGINWIDGET_H
