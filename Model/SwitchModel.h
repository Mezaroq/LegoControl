#ifndef CONTROLSWITCH_H
#define CONTROLSWITCH_H

#include <Model/ObjectModel.h>
#include <Model/ActionModel.h>

class SwitchModel : public ObjectModel
{
    Q_OBJECT
public:
    enum SwitchID{
        SWITCH_1,
        SWITCH_2,
        SWITCH_3,
        SWITCH_4,
        SWITCH_5,
        SWITCH_6,
        SWITCH_7,
        SWITCH_8,
        SWITCH_9
    };
    enum SwitchType{
        TYPE_LEFT,
        TYPE_RIGHT
    };
    enum SwitchState{
        STATE_NORMAL,
        STATE_LEFT,
        STATE_RIGHT
    };
    enum SwitchToggle{
        TOGGLE_OFF,
        TOGGLE_ON
    };
    SwitchModel(SwitchType switchType, SwitchID switchID);
    void setControlAction(ActionModel* controlAction);
    void toggle();
    void setToggle(bool switchState);
    bool getSwitchState();
    ActionModel* getControlAction();
    QString getResource();
    QIcon getIcon();
    SwitchID getSwitchID();

private:
    SwitchType switchType;
    SwitchToggle switchToggle;
    SwitchID switchID;
    SwitchState switchState;
    ActionModel *controlAction;

signals:
    void objectChanged();

public slots:
    void actionToggle(bool state);
};

#endif // CONTROLSWITCH_H
