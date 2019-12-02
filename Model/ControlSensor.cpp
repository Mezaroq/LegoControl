#include "ControlSensor.h"

ControlSensor::ControlSensor(SensorID sensorID, SensorType sensorType, QObject *parent) : QObject(parent)
{
    this->sensorID = sensorID;
    this->sensorType = sensorType;
}

ControlSensor::SensorType ControlSensor::getSensorType()
{
    return sensorType;
}

void ControlSensor::setState(bool newState)
{
    if ((newState == true) && (state != newState))
        emit signalChanged(sensorType);
    state = newState;
}

void ControlSensor::debugSignalTrue()
{
    emit signalChanged(sensorType);
}
