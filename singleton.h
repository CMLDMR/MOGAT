#ifndef SINGLETON_H
#define SINGLETON_H

#include <QtCore/qglobal.h>

#include <Wt/WContainerWidget>
#include <Wt/WApplication>
#include <Wt/WText>

#include <iostream>

#include "Desktop/intro.h"
#include "Desktop/desktopmainpage.h"

using namespace Wt;

///
/// \brief The Singleton class
/// Main Application skeleton. this class is contruct main of the Mogat web services
class Singleton : public WContainerWidget
{
public:
    Singleton(int _width = 0, int _height = 0 , double _ratio = 1);

private:

    ///
    /// \brief mIntroPage
    /// First Page at start up
    intro::Intro* mIntroPage;

    ///
    /// \brief mDesktopMainPage
    /// Clear Content and init Main page Elements
    MainPage::DesktopMainPage* mDesktopMainPage;

    void initMainPage();

    ///
    /// \brief Width
    /// Viewport Width and Height
    int Width;
    int Height;
    double Ratio;




};

#endif // SINGLETON_H
