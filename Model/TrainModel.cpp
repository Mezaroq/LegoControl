#include "TrainModel.h"

TrainModel::TrainModel(TrainID trainID, SliderModel *trainSlider, QObject *parent) : QObject(parent)
{
    this->trainID = trainID;
    this->trainSlider = trainSlider;
}

void TrainModel::setTrainSpeed(TrainModel::TrainSpeed trainSpeed)
{
    trainSpeed == SPEED_BREAKE ? trainSlider->setValue(SPEED_NEUTRAL) : trainSlider->setValue(trainSpeed);
}

TrainModel::TrainID TrainModel::getTrainID()
{
    return trainID;
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
