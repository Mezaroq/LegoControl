#include "ControlTrain.h"
#include <QDebug>

ControlTrain::ControlTrain(TrainID trainID, ControlSlider *trainSlider, QObject *parent) : QObject(parent)
{
    this->trainID = trainID;
    this->trainSlider = trainSlider;
}

void ControlTrain::setTrainSpeed(ControlTrain::TrainSpeed trainSpeed)
{
    trainSlider->setValue(trainSpeed);
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
