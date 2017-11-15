#include "scopepagewidget.h"

ScopePageWidget::ScopePageWidget()
{

    addWidget(cpp14::make_unique<WText>("<h2>Scope</h2>"));

    addWidget(cpp14::make_unique<WText>("<p>This project is carried out by the collaboration of four countries  Turkey, Italy, Germany and England. The scope of MoGaT includes the planning, design, development, testing, and transition of gamified learning and testing in social networks for various professions in tourism, available on an easy-access internet platform.</p>"));

}
