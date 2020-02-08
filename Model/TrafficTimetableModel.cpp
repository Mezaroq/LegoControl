#include "TrafficTimetableModel.h"

TrafficTimetableModel::TrafficTimetableModel(TrainModel::TrainID trainID)
{
    this->trainID = trainID;
}

void TrafficTimetableModel::setCurrentStation(StationModel *currentStation)
{
    this->currentStation = currentStation;
}

void TrafficTimetableModel::setCurrentRail(RailModel *currentRail)
{
    this->currentRail = currentRail;
}

void TrafficTimetableModel::setWaitingTime(TrafficTimetableModel::WaitingTime waitingTime)
{
    this->waitingTime = waitingTime;
}

void TrafficTimetableModel::setDirection(TrainModel::TrainDirection direction)
{
    this->direction = direction;
}

void TrafficTimetableModel::setStopStation(StationModel *station)
{
    stopStations.append(station);
}

void TrafficTimetableModel::removeStopStation(StationModel *station)
{
    stopStations.removeOne(station);
}

void TrafficTimetableModel::enableWaiting()
{
    waiting = true;
    QTimer::singleShot(waitingTime, this, SLOT(waitingEnd()));
}

void TrafficTimetableModel::setSingleStop(bool state)
{
    singleStop = state;
}

TrainModel::TrainID TrafficTimetableModel::getTrainID()
{
    return trainID;
}

StationModel *TrafficTimetableModel::getCurrentStation()
{
    return currentStation;
}

RailModel *TrafficTimetableModel::getCurrentRail()
{
    return currentRail;
}

TrainModel::TrainDirection TrafficTimetableModel::getDirection()
{
    return direction;
}

QList<StationModel *> *TrafficTimetableModel::getStopStations()
{
    return &stopStations;
}

TrafficTimetableModel::WaitingTime TrafficTimetableModel::getWaitingTime()
{
    return waitingTime;
}

bool TrafficTimetableModel::isWaiting()
{
    return waiting;
}

bool TrafficTimetableModel::isSingleStop()
{
    return singleStop;
}

void TrafficTimetableModel::waitingEnd()
{
    waiting = false;
}
