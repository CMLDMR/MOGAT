#include "mainapplication.h"

MainApplication::MainApplication(const Wt::WEnvironment &env)
    :WApplication(env),whChanged(this,"whChanged"),_OrientationChanged(this,"_OrientationChanged"),
      _PixelRatio(this,"_PixelRatio")

{



//    p_wtTheme = std::make_shared<Wt::WBootstrapTheme>();
//    p_wtTheme->setVersion(Wt::WBootstrapTheme::Version::v3);
//    p_wtTheme.get()->setResponsive(true);
//    Wt::WApplication::instance()->setTheme(p_wtTheme);
//    Wt::WApplication::instance()->setTitle("Mogat Official Page");

    WApplication::useStyleSheet(WLink("css/intro.css"));
    WApplication::useStyleSheet(WLink("css/mainPage.css"));

    Wt::WApplication::instance()->setBodyClass("RootGovde");

//    root()->addStyleClass("container");

    WApplication::instance()->addMetaHeader("viewport","width=device.width, initial-scale=1.0");

    this->getDimensionfBrowser();


    this->OrientationChanged().connect(this,&MainApplication::getDimensionfBrowser);

    root()->doJavaScript("window.addEventListener(\"orientationchange\",function(){" + _OrientationChanged.createCall({"4"}) + "},false);");



}

void MainApplication::initMogat()
{
    root()->clear();
    root()->addWidget(Wt::cpp14::make_unique<Singleton>(this->viewPortWidth,this->viewPortHeight));
}

JSignal<int, int> &MainApplication::ViewPortDimension()
{
    return whChanged;
}

JSignal<int> &MainApplication::OrientationChanged()
{
    return _OrientationChanged;
}

JSignal<float> &MainApplication::PixelRatio()
{

    return _PixelRatio;
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

void MainApplication::f_OrientationChanged()
{

}
