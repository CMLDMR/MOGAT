#include "objectivepagewidget.h"

ObjectivePageWidget::ObjectivePageWidget()
{

    setId("ObjectivePageWidget");
    addWidget(cpp14::make_unique<WText>("<h2>Objectives</h2>"));

    addWidget(cpp14::make_unique<WText>("<p>Language competences and digital skills, the two main objects of our project, are basic skills and among the most important capacities of individuals to obtain. Higher competences and skills in the above named fields result in an increased capacity and professionalism to work at international levels, strengthens the links between formal, non-formal education, vocational training and other forms of learning, and allow increased opportunities for professional development, combined with an increased motivation and satisfaction in the daily work - all this at a systemic level as response to main challenges in employment.</p>"));

}
