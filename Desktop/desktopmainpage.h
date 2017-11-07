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
    /// \brief The Header class
    /// Main Page Header Container Class
    class Header : public WContainerWidget
    {
    public:
        Header(int _w, int _h, double _r);

        WImage* mEUFlag;

        WHBoxLayout* mLayout;

        bool isVertical() const;

    private:
        int Width;
        int Height;
        double Ratio;

        bool mVertical;
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

        void f_Mogat();

        void f_objective();

        void f_resource();

        void f_News();

        void f_collabrators();

        void f_About();

        void f_contact();
    };





    ///
    /// \brief Main page's Footer Design Code
    /// This Class include Legal information about MOGAT, its own documentary,
    /// application or any others
    class Footer : public WContainerWidget
    {
    public:
        Footer();

    private:
        const std::string legalNoitice{"This project has been financed with the support of the European Commission."
                                        "The authors are solely responsible for this publication and the Commission does not accept responsibility for the use that could be made of the information contained within it."
                                        "All the content on this website, including but not limited to, the name, the logo, the web pages content (text and images) and any downloadable file, belong to MOGAT. The use of this content is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License."};
    };


    ///
    /// \brief The FlagWidget class
    ///
    class FlagWidget : public WContainerWidget
    {
    public:
        FlagWidget();
    };






    class ContentWidget : public WContainerWidget
    {
    public:
        ContentWidget();
    };


}


#endif // DESKTOPMAINPAGE_H
