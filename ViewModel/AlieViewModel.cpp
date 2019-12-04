#include "AlieViewModel.h"
#include <QDebug>

AlieViewModel::AlieViewModel(QObject *parent) : QObject(parent)
{

}

void AlieViewModel::setSwitches(QMap<int, ControlSwitch *> switches)
{
    this->switches = switches;
}

void AlieViewModel::setRails(QMap<int, ControlRail *> rails)
{
    this->rails = rails;
}

void AlieViewModel::setTrains(QMap<int, ControlTrain *> trains)
{
    this->trains = trains;
}

void AlieViewModel::trainEnters(ControlTrain::TrainID trainID)
{
    ControlTrain *train = trains.value(trainID);
    train->setTrainSpeed(ControlTrain::TrainSpeed(ControlTrain::SPEED_FORWARD_3 * train->getTrainDirection()));
}

void AlieViewModel::trainEntered(ControlTrain::TrainID trainID)
{

}

void AlieViewModel::trainLeaving(ControlTrain::TrainID trainID)
{
    ControlTrain *train = trains.value(trainID);
    train->setTrainSpeed(ControlTrain::TrainSpeed(ControlTrain::SPEED_FORWARD_5 * train->getTrainDirection()));
}

void AlieViewModel::trainLeft(ControlTrain::TrainID trainID)
{

}

void AlieViewModel::stopSensorActivated(ControlTrain::TrainID trainID, ControlRail::RailID railID)
{
    trains.value(trainID)->setTrainSpeed(ControlTrain::SPEED_BREAKE);
}
