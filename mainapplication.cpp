#include "mainapplication.h"

MainApplication::MainApplication(const Wt::WEnvironment &env)
    :WApplication(env),whChanged(this,"whChanged")
{


    std::cout << "DPI: " << env.dpiScale() << std::endl;

    p_wtTheme = std::make_shared<Wt::WBootstrapTheme>();
    p_wtTheme->setVersion(Wt::WBootstrapTheme::Version::v3);
    p_wtTheme.get()->setResponsive(true);
    Wt::WApplication::instance()->setTheme(p_wtTheme);
    Wt::WApplication::instance()->setTitle("Mogat Official Page");

    WApplication::useStyleSheet(WLink("css/intro.css"));
    WApplication::useStyleSheet(WLink("css/mainPage.css"));

    Wt::WApplication::instance()->setBodyClass("RootGovde");

    root()->addStyleClass("container");

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
