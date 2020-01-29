#include "ActionModel.h"

ActionModel::ActionModel(const QIcon &icon, ActionModel::ActionType actionType, int actionID, QObject *parent) : QAction(icon, getActionName(actionType, actionID), parent)
{
    this->actionType = actionType;
    this->actionID = actionID;
}

QString ActionModel::getActionName(ActionModel::ActionType actionType, int actionID)
{
    switch (actionType) {
    case ActionModel::ACTION_SWITCH:
        return "Switch " + QString::number(actionID+1);
    case ActionModel::ACTION_LIGHT:
        return "Light " + QString::number(actionID+1);
    }
}
