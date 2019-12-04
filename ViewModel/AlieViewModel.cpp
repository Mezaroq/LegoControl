#include "AlieViewModel.h"
#include <QDebug>

AlieViewModel::AlieViewModel(QObject *parent) : QObject(parent)
{

}

void AlieViewModel::run()
{
    qDebug() << "run";
    setTrainSpeedFromList();

}

void AlieViewModel::setAiEnabled(bool state)
{
    this->alieIsEnabled = state;
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

void AlieViewModel::setTrainSpeedFromList()
{
    QMapIterator<ControlTrain*, ControlTrain::TrainSpeed> speedMap(trainSpeedMap);
    while (speedMap.hasNext()) {
        speedMap.next();
        speedMap.key()->setTrainSpeed(speedMap.value());
    }
    trainSpeedMap.clear();
}

void AlieViewModel::trainEnters(ControlTrain::TrainID trainID)
{
    if (alieIsEnabled) {
        ControlTrain *train = trains.value(trainID);
        trainSpeedMap.insert(train, ControlTrain::TrainSpeed(ControlTrain::SPEED_FORWARD_5 * train->getTrainDirection()));
    }
}

void AlieViewModel::trainEntered(ControlTrain::TrainID trainID)
{

}

void AlieViewModel::trainLeaving(ControlTrain::TrainID trainID)
{
    if (alieIsEnabled) {
        ControlTrain *train = trains.value(trainID);
        trainSpeedMap.insert(train, ControlTrain::TrainSpeed(ControlTrain::SPEED_FORWARD_3 * train->getTrainDirection()));
    }
}

void AlieViewModel::trainLeft(ControlTrain::TrainID trainID)
{

}

void AlieViewModel::stopSensorActivated(ControlTrain::TrainID trainID, ControlRail::RailID railID)
{
    if (alieIsEnabled) {
        ControlTrain *train = trains.value(trainID);
        trainSpeedMap.insert(train, ControlTrain::SPEED_BREAKE);
    }
}
