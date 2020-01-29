#include "LightModel.h"
#include <QDebug>

LightModel::LightModel(LightID lightID, QPointF lightPosition, qreal lightRotation) : ObjectModel(ObjectModel::OBJECT_LIGHT, lightID)
{
    this->lightID = lightID;
    this->lightPosition = lightPosition;
    this->lightRotation = lightRotation;
    lightState = STATE_RED;
    setPixmap(getResource());
    setPos(lightPosition);
    setRotation(lightRotation);
    setZValue(ObjectModel::OBJECT_LIGHT);
}

QString LightModel::getResource()
{
    switch (lightState) {
    case LightModel::STATE_RED:
        return ":/control/resources/objects/object_light_red.png";
    case LightModel::STATE_GREEN:
        return ":/control/resources/objects/object_light_green.png";
    }
}

QIcon LightModel::getIcon()
{
    switch (lightState) {
    case LightModel::STATE_RED:
        return QIcon(":/control/resources/icons/icon_bar_light_red.svg");
    case LightModel::STATE_GREEN:
        return QIcon(":/control/resources/icons/icon_bar_light_green.svg");
    }
}

void LightModel::setControlAction(ActionModel *controlAction)
{
    controlAction->setCheckable(true);
    this->controlAction = controlAction;
    connect(controlAction, SIGNAL(toggled(bool)), this, SLOT(actionToggle(bool)));
}

void LightModel::setToggle(LightModel::LightState lightState)
{
    controlAction->setChecked(lightState);
}

bool LightModel::getLightState()
{
    return lightState;
}

void LightModel::toggle()
{
    controlAction->toggle();
}

ActionModel *LightModel::getControlAction()
{
    return controlAction;
}

LightModel::LightID LightModel::getLightID()
{
    return lightID;
}

void LightModel::actionToggle(bool state)
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
