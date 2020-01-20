#include "ControlSensor.h"
#include <QDebug>

ControlSensor::ControlSensor(SensorID sensorID, SensorType sensorType, QObject *parent) : QObject(parent)
{
    this->sensorID = sensorID;
    this->sensorType = sensorType;
}

void ControlSensor::setState(bool newState)
{
    if ((newState == true) && (state != newState)) //ignore 2x true signal
        emit signalChanged(sensorType);
    state = newState;
}

void ControlSensor::debugSignal()
{
    emit signalChanged(sensorType);
}
