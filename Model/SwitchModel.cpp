#include "SwitchModel.h"

SwitchModel::SwitchModel(SwitchModel::SwitchType switchType, SwitchModel::SwitchID switchID) : ObjectModel(ObjectModel::OBJECT_SWITCH, switchID)
{
    this->switchType = switchType;
    this->switchID = switchID;
    this->switchState = STATE_NORMAL;
    this->switchToggle = TOGGLE_OFF;
    setPixmap(getResource());
}

void SwitchModel::setControlAction(ActionModel *controlAction)
{
    controlAction->setCheckable(true);
    this->controlAction = controlAction;
    connect(controlAction, SIGNAL(toggled(bool)), this, SLOT(actionToggle(bool)));
}

void SwitchModel::toggle()
{
    controlAction->toggle();
}

void SwitchModel::setToggle(bool switchState)
{
    controlAction->setChecked(switchState);
}

void SwitchModel::setReservation(bool reservation)
{
    this->switchReservation = reservation;
}

bool SwitchModel::isReserved()
{
    return switchReservation;
}

bool SwitchModel::getSwitchState()
{
    return switchToggle;
}

ActionModel *SwitchModel::getControlAction()
{
    return controlAction;
}

QString SwitchModel::getResource()
{
    switch (switchState) {
    case SwitchModel::STATE_NORMAL:
        return ":/control/resources/objects/object_switch_" + QString::number(switchID) + "_normal.png";
    case SwitchModel::STATE_LEFT:
        return ":/control/resources/objects/object_switch_" + QString::number(switchID) + "_left.png";
    case SwitchModel::STATE_RIGHT:
        return ":/control/resources/objects/object_switch_" + QString::number(switchID) + "_right.png";
    }
}

QIcon SwitchModel::getIcon()
{
    switch (switchState) {
    case SwitchModel::STATE_NORMAL:
        return QIcon(":/control/resources/icons/icon_bar_switch_normal.svg");
    case SwitchModel::STATE_LEFT:
        return QIcon(":/control/resources/icons/icon_bar_switch_left.svg");
    case SwitchModel::STATE_RIGHT:
        return QIcon(":/control/resources/icons/icon_bar_switch_right.svg");
    }
}

SwitchModel::SwitchID SwitchModel::getSwitchID()
{
    return switchID;
}

void SwitchModel::actionToggle(bool state)
{
    switch (switchType) {
    case SwitchModel::TYPE_LEFT:
        if (state) {
            switchState = STATE_LEFT;
            switchToggle = TOGGLE_ON;
            setPixmap(getResource());
            controlAction->setIcon(getIcon());
        } else {
            switchState = STATE_NORMAL;
            switchToggle = TOGGLE_OFF;
            setPixmap(getResource());
            controlAction->setIcon(getIcon());
        }
        break;
    case SwitchModel::TYPE_RIGHT:
        if (state) {
            switchState = STATE_RIGHT;
            switchToggle = TOGGLE_ON;
            setPixmap(getResource());
            controlAction->setIcon(getIcon());
        } else {
            switchState = STATE_NORMAL;
            switchToggle = TOGGLE_OFF;
            setPixmap(getResource());
            controlAction->setIcon(getIcon());
        }
        break;
    }
    emit objectChanged();
}
