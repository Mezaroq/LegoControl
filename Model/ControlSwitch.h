#ifndef CONTROLSWITCH_H
#define CONTROLSWITCH_H

#include <Model/ControlObject.h>
#include <Model/ControlAction.h>

class ControlSwitch : public ControlObject
{
    Q_OBJECT
public:
    enum SwitchID{
        SWITCH_01,
        SWITCH_02,
        SWITCH_03,
        SWITCH_04,
        SWITCH_05,
        SWITCH_06,
        SWITCH_07,
        SWITCH_08,
        SWITCH_09
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

    ControlSwitch(SwitchType switchType, SwitchID switchID);
    void setControlAction(ControlAction* controlAction);
    void toggle();
    void setToggle(SwitchState switchState);
    ControlAction* getControlAction();
    QString getResource();
    QIcon getIcon();
    SwitchID getSwitchID();

private:
    SwitchType switchType;
    SwitchID switchID;
    SwitchState switchState;
    ControlAction *controlAction;

public slots:
    void actionToggle(bool state);
};

#endif // CONTROLSWITCH_H
