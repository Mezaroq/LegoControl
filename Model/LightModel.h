#ifndef CONTROLLIGHT_H
#define CONTROLLIGHT_H

#include <Model/ObjectModel.h>
#include <Model/ActionModel.h>

class LightModel : public ObjectModel
{
    Q_OBJECT
public:
    enum LightID{
        LIGHT_1,
        LIGHT_2,
        LIGHT_3,
        LIGHT_4,
        LIGHT_5,
        LIGHT_6,
        LIGHT_7,
        LIGHT_8,
        LIGHT_9,
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
    LightModel(LightID lightID, QPointF lightPosition, qreal lightRotation);
    void setControlAction(ActionModel* controlAction);
    void toggle();
    void setToggle(LightState lightState);
    bool getLightState();
    ActionModel* getControlAction();
    QString getResource();
    QIcon getIcon();
    LightID getLightID();

private:
    LightID lightID;
    LightState lightState;
    ActionModel *controlAction;
    QPointF lightPosition;
    qreal lightRotation;

signals:
    void objectChanged();

public slots:
    void actionToggle(bool state);
};

#endif // CONTROLLIGHT_H
