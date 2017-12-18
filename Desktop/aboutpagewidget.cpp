#include "aboutpagewidget.h"




AboutPageWidget::AboutPageWidget()
{

    setId("AboutPageWidget");

    setMaximumSize(1280,WLength::Auto);

    addWidget(cpp14::make_unique<WText>("<h2>About</h2>"));

    addWidget(cpp14::make_unique<WText>("<p>In a (professional tourism) world which has become digitalized in information transfer, storage, and communication, making personal and facilitating the FOREIGN LANGUAGE (L2) learning process has become an absolute necessity, because understanding and communication in a L2 is a basic skill for every citizen. Another basic skill mentioned in all relevant publications of the EU are key competences in the use of modern forms of ICT (DIGITAL COMPETENCES), and with our project we address directly both sectors. But we address another, very important and always asked for aim in EU-projects: the possibility to MEASURE, to ANALYSE learning outcomes. As a UNESCO study put it (Nov. 2012): Compared to many other sectors, educational institutions are currently 'driving blind'. They should invest in ANALYTICS INFRASTRUCTURE for two reasons: to optimise student success, and to enable their own researchers to ask foundational questions about learning and teaching in the 21st century.</p>"));





}



AboutPageWidget::~AboutPageWidget()
{
}
