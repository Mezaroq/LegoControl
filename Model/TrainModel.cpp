#include "TrainModel.h"

TrainModel::TrainModel(TrainID trainID, SliderModel *trainSlider, TrainType trainType, QObject *parent) : QObject(parent)
{
    this->trainID = trainID;
    this->trainSlider = trainSlider;
    this->trainType = trainType;
}

void TrainModel::setTrainSpeed(TrainModel::TrainSpeed trainSpeed)
{
    trainSpeed == SPEED_BREAKE ? trainSlider->setValue(SPEED_NEUTRAL) : trainSlider->setValue(trainSpeed);
}

void TrainModel::setTrainPrority(unsigned int trainPriority)
{
    this->trainPriority = trainPriority;
}

void TrainModel::setInverseSpeed(bool inverseSpeed)
{
    this->inverseSpeed = inverseSpeed;
}

TrainModel::TrainID TrainModel::getTrainID()
{
    return trainID;
}

TrainModel::TrainType TrainModel::getTrainType()
{
    return trainType;
}

unsigned int TrainModel::getTrainPriority()
{
    return trainPriority;
}

int TrainModel::getTrainSpeed()
{
    if (trainSlider->value() == SPEED_NEUTRAL)
        return SPEED_BREAKE;
    return trainSlider->value();
}

int TrainModel::getTrainControl()
{
    int trainSpeed = getTrainSpeed();
    return inverseSpeed ? ((trainSpeed == SPEED_BREAKE) ? trainSpeed : (trainSpeed * -1)) : trainSpeed;
}

bool TrainModel::isInverse()
{
    return inverseSpeed;
}

TrainModel::TrainDirection TrainModel::getDirectionMultiplier()
{
    if (getTrainSpeed() >= 0)
        return DIRECTION_FORWARD;
    return DIRECTION_REVERSE;
}
