#include "ControlSwitch.h"

ControlSwitch::ControlSwitch(ControlSwitch::SwitchType switchType, ControlSwitch::SwitchID switchID) : ControlObject(ControlObject::OBJECT_SWITCH, switchID)
{
    this->switchType = switchType;
    this->switchID = switchID;
    this->switchState = STATE_NORMAL;
    this->switchToggle = TOGGLE_OFF;
    setPixmap(getResource());
}

void ControlSwitch::setControlAction(ControlAction *controlAction)
{
    controlAction->setCheckable(true);
    this->controlAction = controlAction;
    connect(controlAction, SIGNAL(toggled(bool)), this, SLOT(actionToggle(bool)));
}

void ControlSwitch::toggle()
{
    controlAction->toggle();
}

void ControlSwitch::setToggle(ControlSwitch::SwitchState switchState)
{
    actionToggle(switchState);
}

void ControlSwitch::setReservation(bool reservation)
{
    this->switchReservation = reservation;
}

bool ControlSwitch::isReserved()
{
    return switchReservation;
}

bool ControlSwitch::getSwitchToggle()
{
    return switchToggle;
}

ControlAction *ControlSwitch::getControlAction()
{
    return controlAction;
}

QString ControlSwitch::getResource()
{
    switch (switchState) {
    case ControlSwitch::STATE_NORMAL:
        return ":/control/resources/objects/object_switch_" + QString::number(switchID) + "_normal.png";
    case ControlSwitch::STATE_LEFT:
        return ":/control/resources/objects/object_switch_" + QString::number(switchID) + "_left.png";
    case ControlSwitch::STATE_RIGHT:
        return ":/control/resources/objects/object_switch_" + QString::number(switchID) + "_right.png";
    }
}

QIcon ControlSwitch::getIcon()
{
    switch (switchState) {
    case ControlSwitch::STATE_NORMAL:
        return QIcon(":/control/resources/icons/icon_bar_switch_normal.svg");
    case ControlSwitch::STATE_LEFT:
        return QIcon(":/control/resources/icons/icon_bar_switch_left.svg");
    case ControlSwitch::STATE_RIGHT:
        return QIcon(":/control/resources/icons/icon_bar_switch_right.svg");
    }
}

ControlSwitch::SwitchID ControlSwitch::getSwitchID()
{
    return switchID;
}

void ControlSwitch::actionToggle(bool state)
{
    switch (switchType) {
    case ControlSwitch::TYPE_LEFT:
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
    case ControlSwitch::TYPE_RIGHT:
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
