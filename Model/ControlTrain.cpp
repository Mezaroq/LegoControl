#include "ControlTrain.h"
#include <QDebug>

ControlTrain::ControlTrain(TrainID trainID, ControlSlider *trainSlider, QObject *parent) : QObject(parent)
{
    this->trainID = trainID;
    this->trainSlider = trainSlider;
}

void ControlTrain::setTrainSpeed(ControlTrain::TrainSpeed trainSpeed)
{
    trainSpeed == SPEED_BREAKE ? trainSlider->setValue(SPEED_NEUTRAL) : trainSlider->setValue(trainSpeed);
}

void ControlTrain::setTrainPriority(ControlTrain::TrainPriority trainPriority)
{
    this->trainPriority = trainPriority;
}

ControlTrain::TrainID ControlTrain::getTrainID()
{
    return trainID;
}

int ControlTrain::getTrainSpeed()
{
    return trainSlider->getControlValue();
}

ControlTrain::TrainDirection ControlTrain::getTrainDirection()
{
    if (getTrainSpeed() >= 0)
        return DIRECTION_FORWARD;
    return DIRECTION_REVERSE;
}
