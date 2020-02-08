#ifndef TRAFFICMAPMODEL_H
#define TRAFFICMAPMODEL_H

#include <QObject>
#include <Model/RailModel.h>
#include <Model/SwitchModel.h>
#include <Model/StationModel.h>

class TrafficMapModel : public QObject
{
    Q_OBJECT
public:
    explicit TrafficMapModel(QObject *parent = nullptr);
    void setRails(QMap<int, RailModel*> rails);
    void setStations(QMap<int, StationModel*> stations);
    void setSwitches(QMap<int, SwitchModel*> switches);
    void setSwitch(RailModel::RailID from, RailModel::RailID to, TrainModel::TrainDirection direction);
    StationModel* getStationByRail(RailModel::RailID railID);

private:
    QMap<int, RailModel*> rails;
    QMap<int, StationModel*> stations;
    QMap<int, SwitchModel*> switches;
    QMap<StationModel::StationID, QList<RailModel*>> stationRails;
};

#endif // TRAFFICMAPMODEL_H
