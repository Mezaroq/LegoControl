#include "TrafficManagerButtonModel.h"
#include <QDebug>

TrafficManagerButtonModel::TrafficManagerButtonModel(QWidget *parent) : QPushButton(parent)
{
    connect(this, SIGNAL(clicked(bool)), this, SLOT(buttonClicked(bool)));
}

void TrafficManagerButtonModel::setButtonType(TrafficManagerButtonModel::ButtonType buttonType)
{
    this->buttonType = buttonType;
}

void TrafficManagerButtonModel::setButtonCategory(TrafficManagerButtonModel::ButtonCategory buttonCategory)
{
    this->buttonCategory = buttonCategory;
}

int TrafficManagerButtonModel::getButtonIndex(TrafficManagerButtonModel::ButtonCategory buttonCategory, TrafficManagerButtonModel::ButtonType buttonType)
{
    switch (buttonCategory) {
    case TrafficManagerButtonModel::BUTTON_GENERAL:
        return buttonType;
    case TrafficManagerButtonModel::BUTTON_TRAIN_1:
        return buttonType;
    case TrafficManagerButtonModel::BUTTON_TRAIN_2:
        return (9+buttonType);
    case TrafficManagerButtonModel::BUTTON_TRAIN_3:
        return (18+buttonType);
    }
}

void TrafficManagerButtonModel::buttonClicked(bool toggled)
{
    emit managerButtonClicked(buttonCategory, buttonType, toggled);
}
