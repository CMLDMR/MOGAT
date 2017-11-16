#ifndef SCOPEPAGEWIDGET_H
#define SCOPEPAGEWIDGET_H

#include <QtCore/qglobal.h>


#include <Wt/WContainerWidget.h>
#include <Wt/WWidget.h>
#include <Wt/WInteractWidget.h>

#include <Wt/WHBoxLayout.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WText.h>
#include <Wt/WLink.h>
#include <Wt/WImage.h>

#include <memory>



using namespace Wt;


class ScopePageWidget : public WContainerWidget
{
public:
    ScopePageWidget();
};

#endif // SCOPEPAGEWIDGET_H
