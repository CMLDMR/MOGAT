#include "mainapplication.h"

MainApplication::MainApplication(const Wt::WEnvironment &env)
    :WApplication(env),whChanged(this,"whChanged")
{
    WApplication::useStyleSheet(WLink("css/intro.css"));
    WApplication::useStyleSheet(WLink("css/mainPage.css"));

    Wt::WApplication::instance()->setBodyClass("RootGovde");

    this->getDimensionfBrowser();

}

void MainApplication::initMogat()
{
    root()->addWidget(Wt::cpp14::make_unique<Singleton>(this->viewPortWidth,this->viewPortHeight));
}

JSignal<int, int> &MainApplication::ViewPortDimension()
{
    return whChanged;
}

void MainApplication::f_whChanged(int w, int h)
{

    this->viewPortHeight = h;
    this->viewPortWidth = w;
    this->initMogat();

}

void MainApplication::getDimensionfBrowser()
{

    this->ViewPortDimension().connect(this,&MainApplication::f_whChanged);

    root()->doJavaScript(""
                         "var w = Math.max(document.documentElement.clientWidth, window.innerWidth || 0);"
                         "var h = Math.max(document.documentElement.clientHeight, window.innerHeight || 0);"
                         +whChanged.createCall({"w,h"})+
                         ";");

}
