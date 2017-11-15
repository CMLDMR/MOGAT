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

#include <memory>

using namespace Wt;



class HomePageWidget : public WContainerWidget
{
public:
    HomePageWidget();
};

#endif // HOMEPAGEWIDGET_H
