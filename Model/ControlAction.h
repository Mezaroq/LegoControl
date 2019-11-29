#ifndef CONTROLACTION_H
#define CONTROLACTION_H

#include <QAction>

class ControlAction : public QAction
{
public:
    enum ActionType{
        ACTION_SWITCH,
        ACTION_LIGHT
    };
    ControlAction(const QIcon &icon, ActionType actionType, int actionID, QObject *parent = nullptr);
    static QString getActionName(ActionType actionType, int actionID);

private:
    ActionType actionType;
    int actionID;
};

#endif // CONTROLACTION_H
