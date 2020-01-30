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

void TrainModel::setTrainPrority(TrainModel::TrainPriority trainPriority)
{
    this->trainPriority = trainPriority;
}

TrainModel::TrainID TrainModel::getTrainID()
{
    return trainID;
}

TrainModel::TrainType TrainModel::getTrainType()
{
    return trainType;
}

TrainModel::TrainPriority TrainModel::getTrainPriority()
{
    return trainPriority;
}

int TrainModel::getTrainSpeed()
{
    if (trainSlider->value() == SPEED_NEUTRAL)
        return SPEED_BREAKE;
    return trainSlider->value();
}

TrainModel::TrainDirection TrainModel::getDirectionMultiplier()
{
    if (getTrainSpeed() >= 0)
        return DIRECTION_FORWARD;
    return DIRECTION_REVERSE;
}
