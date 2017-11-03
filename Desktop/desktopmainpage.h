#ifndef DESKTOPMAINPAGE_H
#define DESKTOPMAINPAGE_H

#include <QtCore/qglobal.h>


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

using namespace Wt;

namespace MainPage {


    class Header;

    class Footer;


    ///
    /// \brief The DesktopMainPage class
    /// Main Page Container Class.
    class DesktopMainPage : public WContainerWidget
    {
    public:
        DesktopMainPage();
    };


    ///
    /// \brief The Header class
    /// Main Page Header Container Class
    class Header : public WContainerWidget
    {
    public:
        Header();

        WImage* mEUFlag;

        WHBoxLayout* mLayout;
    };




    class Body : public WContainerWidget
    {
    public:
        Body();

        WNavigationBar* mNavigationBar;

        WStackedWidget* mContent;
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
}


#endif // DESKTOPMAINPAGE_H
