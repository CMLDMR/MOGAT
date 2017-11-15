#ifndef ABOUTPAGEWIDGET_H
#define ABOUTPAGEWIDGET_H

#include <QtCore/qglobal.h>

#include <Wt/WContainerWidget.h>
#include <Wt/WWidget.h>
#include <Wt/WInteractWidget.h>

#include <Wt/WHBoxLayout.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WText.h>

#include <memory>



using namespace Wt;



class AboutPageWidget : public WContainerWidget
{
public:
    AboutPageWidget();
    ~AboutPageWidget();

//    void operator()(AboutPageWidget* p) {
//        delete p;
//    }

};

#endif // ABOUTPAGEWIDGET_H
