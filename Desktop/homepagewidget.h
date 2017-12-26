#ifndef HOMEPAGEWIDGET_H
#define HOMEPAGEWIDGET_H

#include <QtCore/qglobal.h>
#include <QString>
#include <QRegExp>

#include <Wt/WContainerWidget.h>
#include <Wt/WWidget.h>
#include <Wt/WInteractWidget.h>

#include <Wt/WHBoxLayout.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WText.h>
#include <Wt/WLink.h>
#include <Wt/WImage.h>
#include <Wt/WCssDecorationStyle.h>
#include <Wt/WTextArea.h>
#include <Wt/WTextEdit.h>
#include <Wt/WLabel.h>
#include <Wt/WBreak.h>

#include "db.h"
#include "mongoheaders.h"
#include "bootstrap.h"

#include <memory.h>


using namespace Wt;


namespace HomePage {

using bsoncxx::builder::basic::document;
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;






    class HomePageWidget : public WContainerWidget
    {
    public:
        HomePageWidget(mongocxx::database* _db);

        WContainerWidget* mMainContainer;

        void initLayout(WContainerWidget* container);

        void setNewsDetail(std::string NewsOid);

    private:
        mongocxx::database* db;
    };









    class NewsListWidget : public WContainerWidget
    {
    public:
        NewsListWidget(mongocxx::database* _db);

        struct NewsItem
        {
            std::string oid;
            std::string title;
            std::string html;
            std::string iconPath;
        };

        std::vector<NewsItem> NewsList;

        Signal<std::string> & ClickedNewsItem(){ return  ClickedNewsItem_;}

    private:
        mongocxx::database* db;

        Signal<std::string> ClickedNewsItem_;
    };









    class AnounceListWidget : public WContainerWidget
    {
    public:
        AnounceListWidget(mongocxx::database* _db);


    private:
        mongocxx::database* db;
    };









    class SuppotersWidget : public WContainerWidget
    {
    public:
        SuppotersWidget(mongocxx::database* _db);


    private:
        mongocxx::database* db;
    };
}


#endif // HOMEPAGEWIDGET_H
