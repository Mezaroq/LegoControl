#include "ControlSensor.h"
#include <QDebug>

ControlSensor::ControlSensor(SensorID sensorID, SensorType sensorType, QObject *parent) : QObject(parent)
{
    this->sensorID = sensorID;
    this->sensorType = sensorType;
}

void ControlSensor::setState(bool newState)
{
    if ((newState == true) && (state != newState)) {
        state = true;
        emit signalChanged(sensorType);
    } else if ((newState == false) && (state != newState)) {
        state = false;
    }
}

void ControlSensor::debugSignal()
{
    emit signalChanged(sensorType);
}
