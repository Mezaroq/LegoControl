#ifndef CONTROLSWITCH_H
#define CONTROLSWITCH_H

#include <Model/ControlObject.h>
#include <Model/ControlAction.h>

class ControlSwitch : public ControlObject
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

    ControlSwitch(SwitchType switchType, SwitchID switchID);
    void setControlAction(ControlAction* controlAction);
    void toggle();
    void setToggle(SwitchState switchState);
    void setReservation(bool reservation);
    bool isReserved();
    bool getSwitchToggle();
    ControlAction* getControlAction();
    QString getResource();
    QIcon getIcon();
    SwitchID getSwitchID();

private:
    SwitchType switchType;
    SwitchToggle switchToggle;
    SwitchID switchID;
    SwitchState switchState;
    bool switchReservation = false;
    ControlAction *controlAction;

signals:
    void objectChanged();

public slots:
    void actionToggle(bool state);
};

#endif // CONTROLSWITCH_H
