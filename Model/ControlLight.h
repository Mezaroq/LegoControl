#ifndef CONTROLLIGHT_H
#define CONTROLLIGHT_H

#include <Model/ControlObject.h>
#include <Model/ControlAction.h>

class ControlLight : public ControlObject
{
    Q_OBJECT
public:
    enum LightID{
        LIGHT_01,
        LIGHT_02,
        LIGHT_03,
        LIGHT_04,
        LIGHT_05,
        LIGHT_06,
        LIGHT_07,
        LIGHT_08,
        LIGHT_09,
        LIGHT_10,
        LIGHT_11,
        LIGHT_12,
        LIGHT_13,
        LIGHT_14,
        LIGHT_15,
        LIGHT_16,
        LIGHT_17,
        LIGHT_18,
        LIGHT_19,
        LIGHT_20,
        LIGHT_21
    };
    enum LightState{
        STATE_RED,
        STATE_GREEN
    };

    ControlLight(LightID lightID, QPointF lightPosition, qreal lightRotation);
    void setControlAction(ControlAction* controlAction);
    void toggle();
    void setToggle(LightState lightState);
    ControlAction* getControlAction();
    QString getResource();
    QIcon getIcon();
    LightID getLightID();

private:
    LightID lightID;
    LightState lightState;
    ControlAction *controlAction;
    QPointF lightPosition;
    qreal lightRotation;

public slots:
    void actionToggle(bool state);
};

#endif // CONTROLLIGHT_H
