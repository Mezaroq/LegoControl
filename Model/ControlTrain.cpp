#include "ControlTrain.h"
#include <QDebug>

ControlTrain::ControlTrain(TrainID trainID, ControlSlider *trainSlider, QObject *parent) : QObject(parent)
{
    this->trainID = trainID;
    this->trainSlider = trainSlider;
}

int ControlTrain::getTrainSpeed()
{
    return trainSlider->getControlValue();
}
