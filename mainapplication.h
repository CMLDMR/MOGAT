#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H



#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WEnvironment.h>
#include <Wt/WJavaScript.h>



#include "singleton.h"

#include <iostream>
#include <memory>



using namespace Wt;

#include <QtCore/qglobal.h>

///
/// \brief The MainApplication class
/// This is Web Application Server. Contruct and Manage Page. Deliver the some neccessary variabla from platform or host
class MainApplication : public WApplication
{
public:
    MainApplication(const WEnvironment& env);


    ///
    /// \brief start initializing www.mogat.eu web.
    ///
    void initMogat();

    ///
    /// \brief ViewPortDimension
    /// \return
    /// Emit Signal that captured browserviewport Dimensions like Width and Height.
    JSignal<int,int>& ViewPortDimension();

    ///
    /// \brief f_whChanged
    /// \param w
    /// \param h
    /// Slot for Capturing Dimension of the Browser.
    void f_whChanged(int w, int h);


    ///
    /// \brief run Javascript code for get browser dimension
    ///
    void getDimensionfBrowser();

private:




    int viewPortWidth, viewPortHeight;

    JSignal<int,int> whChanged;


};

#endif // MAINAPPLICATION_H
