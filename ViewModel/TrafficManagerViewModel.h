#ifndef TRAFFICMANAGERVIEWMODEL_H
#define TRAFFICMANAGERVIEWMODEL_H

#include <QObject>
#include <Model/RailModel.h>
#include <Model/TrainModel.h>
#include <Model/SwitchModel.h>
#include <Model/StationModel.h>
#include <Model/TrafficMapModel.h>
#include <Model/TrafficTimetableModel.h>
#include <Model/TrafficManagerLabelModel.h>
#include <Model/TrafficManagerButtonModel.h>
#include <QMap>
#include <QList>

class TrafficManagerViewModel : public QObject
{
    Q_OBJECT
public:
    enum TrainState{
        TRAIN_ENTERS,
        TRAIN_LEAVES
    };
    explicit TrafficManagerViewModel(QObject *parent = nullptr);
    void run();
    void enable();
    void disable();
    void trafficManagerWaitingTrains();
    void initData();
    void deinitData();
    bool nextRailFree();
    bool nextStationIsStop();
    bool currentStationIsStop();
    void trafficManagerMovingTrains(TrainModel *train, TrainState trainState);
    void prependTimetables();
    void prependTrafficMap();
    void setRails(QMap<int, RailModel*> rails);
    void setTrains(QMap<int, TrainModel*> trains);
    void setStations(QMap<int, StationModel*> stations);
    void setSwitches(QMap<int, SwitchModel*> switches);
    QMap<TrainModel::TrainID, TrafficTimetableModel *> *getTimetables();
    int *getNormalSpeed();
    int *getSlowdownSpeed();
    int *getStartSpeed();

protected:
    QMap<unsigned int, TrainModel*> getTrainsByPriority();

private:
    int normalSpeed = TrainModel::SPEED_FORWARD_5;
    int slowdownSpeed = TrainModel::SPEED_FORWARD_3;
    int startSpeed = TrainModel::SPEED_FORWARD_3;
    bool trafficManagerEnabled = false;
    QMap<int, RailModel*> rails;
    QMap<int, TrainModel*> trains;
    QMap<int, StationModel*> stations;
    QMap<int, SwitchModel*> switches;
    TrafficTimetableModel *timetable;
    RailModel *destinationRail;
    QMap<TrainModel::TrainID, TrafficTimetableModel*> timetables;
    QMap<unsigned int, TrainModel*> waitingTrainsBuffor;
    QList<TrainModel*> waitingTrains;
    TrafficMapModel *map;

public slots:
    void trainEnter(TrainModel *train, RailModel *rail);
    void trainLeave(TrainModel *train, RailModel *rail);
    void trainEnters(TrainModel *train, RailModel *rail);
    void trainLeaves(TrainModel *train, RailModel *rail);
    void trainStop(TrainModel *train, RailModel *rail);

};

#endif // TRAFFICMANAGERVIEWMODEL_H
