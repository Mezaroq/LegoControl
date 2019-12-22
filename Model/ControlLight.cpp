#include "ControlLight.h"
#include <QDebug>

ControlLight::ControlLight(LightID lightID, QPointF lightPosition, qreal lightRotation) : ControlObject(ControlObject::OBJECT_LIGHT, lightID)
{
    this->lightID = lightID;
    this->lightPosition = lightPosition;
    this->lightRotation = lightRotation;
    lightState = STATE_RED;
    setPixmap(getResource());
    setPos(lightPosition);
    setRotation(lightRotation);
    setZValue(ControlObject::OBJECT_LIGHT);
}

QString ControlLight::getResource()
{
    switch (lightState) {
    case ControlLight::STATE_RED:
        return ":/control/resources/objects/object_light_red.png";
    case ControlLight::STATE_GREEN:
        return ":/control/resources/objects/object_light_green.png";
    }
}

QIcon ControlLight::getIcon()
{
    switch (lightState) {
    case ControlLight::STATE_RED:
        return QIcon(":/control/resources/icons/icon_bar_light_red.svg");
    case ControlLight::STATE_GREEN:
        return QIcon(":/control/resources/icons/icon_bar_light_green.svg");
    }
}

void ControlLight::setControlAction(ControlAction *controlAction)
{
    controlAction->setCheckable(true);
    this->controlAction = controlAction;
    connect(controlAction, SIGNAL(toggled(bool)), this, SLOT(actionToggle(bool)));
}

void ControlLight::setToggle(ControlLight::LightState lightState)
{
    controlAction->setChecked(lightState);
}

bool ControlLight::getLightToggle()
{
    return lightState;
}

void ControlLight::toggle()
{
    controlAction->toggle();
}

ControlAction *ControlLight::getControlAction()
{
    return controlAction;
}

ControlLight::LightID ControlLight::getLightID()
{
    return lightID;
}

void ControlLight::actionToggle(bool state)
{
    if (state) {
        lightState = STATE_GREEN;
        setPixmap(getResource());
        controlAction->setIcon(getIcon());
    } else {
        lightState = STATE_RED;
        setPixmap(getResource());
        controlAction->setIcon(getIcon());
    }
    emit objectChanged();
}
