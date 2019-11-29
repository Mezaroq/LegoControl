#include "ControlAction.h"

ControlAction::ControlAction(const QIcon &icon, ControlAction::ActionType actionType, int actionID, QObject *parent) : QAction(icon, getActionName(actionType, actionID), parent)
{
    this->actionType = actionType;
    this->actionID = actionID;
}

QString ControlAction::getActionName(ControlAction::ActionType actionType, int actionID)
{
    switch (actionType) {
    case ControlAction::ACTION_SWITCH:
        return "Switch " + QString::number(actionID);
    case ControlAction::ACTION_LIGHT:
        return "Light " + QString::number(actionID);
    }
}
