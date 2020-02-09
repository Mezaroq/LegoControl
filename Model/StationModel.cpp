#include "StationModel.h"

StationModel::StationModel(StationModel::StationID stationID, QObject *parent) : QObject(parent)
{
    this->stationID = stationID;
}

void StationModel::setStations(QList<StationModel *> stations)
{
    this->nextStations.insert(FORWARD, stations.value(FORWARD));
    this->nextStations.insert(REVERSE, stations.value(REVERSE));

}

void StationModel::setPlatforms(TrainModel::TrainType trainType, QList<RailModel *> rails)
{
    platforms.insert(trainType, rails);
}

void StationModel::setNextRails(QList<RailModel *> nextRails)
{
    this->nextRails.insert(FORWARD, nextRails.value(FORWARD));
    this->nextRails.insert(REVERSE, nextRails.value(REVERSE));
}

StationModel::StationID StationModel::getStationID()
{
    return stationID;
}

QMap<TrainModel::TrainType, QList<RailModel *> > StationModel::getPlatforms()
{
    return platforms;
}

StationModel *StationModel::getNextStation(TrainModel::TrainDirection direction)
{
    if (direction == TrainModel::DIRECTION_FORWARD)
        return nextStations.value(FORWARD);
    return nextStations.value(REVERSE);
}

RailModel *StationModel::getNextRail(TrainModel::TrainDirection direction)
{
    if (direction == TrainModel::DIRECTION_FORWARD)
        return nextRails.value(FORWARD);
    return nextRails.value(REVERSE);
}

RailModel *StationModel::getFreePlatform()
{
    for (auto trainType : platforms) {
        for (auto rail : trainType) {
            if (!rail->isReserved())
                return rail;
        }
    }
    return nullptr;
}

RailModel *StationModel::getPlatformByTrainType(TrainModel::TrainType trainType)
{
    for (auto rail : platforms.value(trainType)) {
        if (!rail->isReserved())
            return rail;
    }
    return nullptr;
}
