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

using namespace Wt;

namespace MainPage {


    class DesktopMainPage : public WContainerWidget
    {
    public:
        DesktopMainPage();
    };
}


#endif // DESKTOPMAINPAGE_H
