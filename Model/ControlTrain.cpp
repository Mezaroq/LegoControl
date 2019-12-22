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

void ControlTrain::setWaiting(int mscs)
{
    QTimer::singleShot(mscs, this, SLOT(waitingEnded()));
    trainIsWaiting = true;
    setTrainSpeed(SPEED_BREAKE);
}

bool ControlTrain::isWaiting()
{
    return trainIsWaiting;
}

ControlTrain::TrainID ControlTrain::getTrainID()
{
    return trainID;
}

int ControlTrain::getTrainSpeed()
{
    return trainSlider->getControlValue();
}

ControlTrain::TrainPriority ControlTrain::getTrainPriority()
{
    return trainPriority;
}

ControlTrain::TrainDirection ControlTrain::getTrainDirectionFromSpeed()
{
    if (getTrainSpeed() >= 0)
        return DIRECTION_FORWARD;
    return DIRECTION_REVERSE;
}

void ControlTrain::waitingEnded()
{
    trainIsWaiting = false;
}
