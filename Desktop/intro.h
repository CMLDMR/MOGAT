#ifndef INTRO_H
#define INTRO_H

#include <QtCore/qglobal.h>
#include <QString>

#include <Wt/WContainerWidget.h>

#include <Wt/WHBoxLayout.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WSignal.h>
#include <Wt/WImage.h>
#include <Wt/WText.h>
#include <Wt/WCssDecorationStyle.h>
#include <Wt/WComboBox>
#include <Wt/WPopupMenu.h>
#include <Wt/WMenuItem.h>
#include <Wt/WPushButton.h>
#include <Wt/WMessageBox.h>
#include <Wt/WBreak.h>
#include <Wt/WMenu.h>




using namespace Wt;

namespace intro {

    class Header;
    class Body;
    class Footer;

    ///
    /// \brief The Intro class
    /// Compilation of Header, Body and Footer Source Code
    class Intro : public WContainerWidget
    {
    public:
        Intro(int _w = 0 , int _h = 0 , double _ratio = 1);

        Header* mHeader;
        Body* mBody;
        Footer* mFooter;

    private:

        int width;
        int height;
        double ratio;


    };




    ///
    /// \brief intro page's Header Design Code
    /// This Class include Title, Logo Origin cs...
    class Header : public WContainerWidget
    {
    public:
        Header(int _w = 0 , int _h = 0 , double _ratio = 1);

        WImage* mEUFlag;

        WHBoxLayout* mLayout;

        bool isVertical() const;

    private:

        double Ratio;
        int Width;
        int Height;

        bool mVertical;

    };


    ///
    /// \brief intro page's Body Design Code
    /// This Class inlcude catch-phrase
    class Body : public WContainerWidget
    {
    public:
        Body(int _w = 0 , int _h = 0 , double _r = 1);

        Signal<int> &EnterClicked();

        bool isVertical() const;

    private:
        Signal<int> _EnterClicked;

        void eEnterClick();

        int Width;
        int Height;
        double Ratio;

        bool mVertical;
    };

    ///
    /// \brief intro page's Footer Design Code
    /// This Class include Legal information about MOGAT, its own documentary,
    /// application or any others
    class Footer : public WContainerWidget
    {
    public:
        Footer(int _w, int _h , double _r);

        bool isVertical() const;

    private:

        int Width;
        int Height;
        double Ratio;
         bool mVertical;

        const std::string legalNoitice{"This project has been financed with the support of the European Commission."
                                        "The authors are solely responsible for this publication and the Commission does not accept responsibility for the use that could be made of the information contained within it."
                                        "All the content on this website, including but not limited to, the name, the logo, the web pages content (text and images) and any downloadable file, belong to MOGAT. The use of this content is licensed under a Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License."};
    };




    class FlagWidget : public WContainerWidget
    {
    public:
        FlagWidget(int _w , int _h , double _r);

        bool isVertical() const;

    private:
        int Width;
        int Height;
        double Ratio;

        bool mVertical;
    };


}





#endif // INTRO_H
