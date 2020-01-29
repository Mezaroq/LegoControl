#include "SensorModel.h"
#include <QDebug>

SensorModel::SensorModel(SensorID sensorID, SensorType sensorType, QObject *parent) : QObject(parent)
{
    this->sensorID = sensorID;
    this->sensorType = sensorType;
}

void SensorModel::setState(bool newState)
{
    if ((newState == true) && (state != newState)) {
        state = true;
        emit signalChanged(sensorType);
    } else if ((newState == false) && (state != newState)) {
        state = false;
    }
}

void SensorModel::debugSignal()
{
    emit signalChanged(sensorType);
}
