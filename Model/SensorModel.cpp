#include "SensorModel.h"

SensorModel::SensorModel(SensorID sensorID, SensorType sensorType, QObject *parent) : QObject(parent)
{
    this->sensorID = sensorID;
    this->sensorType = sensorType;
}

void SensorModel::setSensorSignal(bool newState)
{
    if (state == false && newState == true) {
        emit signalChanged(sensorType);
    }
    state = newState;
}

//void SensorModel::setSensorSignal(bool newState)
//{
//    if (newState)
//        emit signalChanged(sensorType);
//}
