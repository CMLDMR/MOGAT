#ifndef DESKTOPMAINPAGE_H
#define DESKTOPMAINPAGE_H

#include <QtCore/qglobal.h>
#include <QString>


#include <Wt/WContainerWidget.h>

#include <Wt/WHBoxLayout.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WSignal.h>
#include <Wt/WImage.h>
#include <Wt/WText.h>
#include <Wt/WCssDecorationStyle.h>
#include <Wt/WNavigationBar.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WMenu.h>
#include <Wt/WToolBar.h>
#include <Wt/WPushButton.h>
#include <Wt/WComboBox>
#include <Wt/WPopupMenu.h>
#include <Wt/WMenuItem.h>
#include <Wt/WPushButton.h>
#include <Wt/WMessageBox.h>
#include <Wt/WBreak.h>
#include <Wt/WLineEdit.h>

class AboutPageWidget;
class ObjectivePageWidget;
class ScopePageWidget;
class HomePageWidget;

using namespace Wt;

namespace MainPage {


    class FlagWidget;
    class Header;
    class Footer;
    class ContentWidget;






    ///
    /// \brief The DesktopMainPage class
    /// Main Page Container Class.
    class DesktopMainPage : public WContainerWidget
    {
    public:
        DesktopMainPage(int _w , int _h , double _r );


        WVBoxLayout* mLayout;

    private:
        int Width;
        int Height;
        double Ratio;
    };




    ///
    /// \brief The Body class
    ///
    class Body : public WContainerWidget
    {
    public:
        Body();

        WNavigationBar* mNavigationBar;

        WStackedWidget* mContent;

        WToolBar* menuBar;

        WVBoxLayout* mContentLayout;

        ContentWidget* mContentWidget;

        void MenuBarForDesktop(WVBoxLayout *layout);

        void MenuBarForMobile(WVBoxLayout *layout);

        void f_Mogat();

        void f_Scope();

        void f_objective();

        void f_resource();

        void f_News();

        void f_collabrators();

        void f_About();

        void f_contact();

        void f_relocateFooter();


        Wt::WStackedWidget *contentsStack;


    };



    class ContentWidget : public WContainerWidget
    {
    public:
        ContentWidget();
    };


}


#endif // DESKTOPMAINPAGE_H
