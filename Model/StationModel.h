#ifndef CONTROLSTATION_H
#define CONTROLSTATION_H

#include <QObject>
#include <Model/RailModel.h>
#include <Model/TrainModel.h>
#include <QList>
#include <QMap>

class StationModel : public QObject
{
    Q_OBJECT
public:
    enum StationID{
        CENTRAL_STATION,
        NORTH_STATION,
        SOUTH_STATION
    };
    enum NextStation{
        FORWARD,
        REVERSE
    };
    explicit StationModel(StationID stationID, QObject *parent = nullptr);
    void setStations(QList<StationModel*> nextStations);
    void setPlatforms(TrainModel::TrainType trainType, QList<RailModel*> rails);
    void setNextRails(QList<RailModel*> nextRails);
    StationID getStationID();
    QMap<TrainModel::TrainType, QList<RailModel*>> getPlatforms();
    StationModel* getNextStation(TrainModel::TrainDirection direction);
    RailModel* getNextRail(TrainModel::TrainDirection direction);
    RailModel* getFreePlatform();
    RailModel* getPlatformByTrainType(TrainModel::TrainType trainType);

private:
    StationID stationID;
    QMap<NextStation, StationModel*> nextStations;
    QMap<TrainModel::TrainType, QList<RailModel*>> platforms;
    QMap<NextStation, RailModel*> nextRails;
};

#endif // CONTROLSTATION_H
