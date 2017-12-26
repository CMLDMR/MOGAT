#ifndef HOMEPAGEWIDGET_H
#define HOMEPAGEWIDGET_H

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


#include "mongoheaders.h"

#include <memory.h>


using namespace Wt;


namespace HomePage {
    class HomePageWidget : public WContainerWidget
    {
    public:
        HomePageWidget();

        WContainerWidget* mMainContainer;

        void initLayout(WContainerWidget* container);
    };
}


#endif // HOMEPAGEWIDGET_H
