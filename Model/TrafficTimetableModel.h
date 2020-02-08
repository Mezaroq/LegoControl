#ifndef TRAFFICTIMETABLEMODEL_H
#define TRAFFICTIMETABLEMODEL_H

#include <QObject>
#include <Model/TrainModel.h>
#include <Model/StationModel.h>
#include <QTimer>
#include <QList>

class TrafficTimetableModel : public QObject
{
    Q_OBJECT
public:
    enum WaitingTime{
        WAITING_1S = 1000,
        WAITING_5S = WAITING_1S*5,
        WAITING_10S = WAITING_1S*10,
        WAITING_15S = WAITING_1S*15,
        WAITING_20S = WAITING_1S*20,
        WAITING_25S = WAITING_1S*25,
        WAITING_30S = WAITING_1S*30,
    };
    explicit TrafficTimetableModel(TrainModel::TrainID trainID);
    void setCurrentStation(StationModel *currentStation);
    void setCurrentRail(RailModel *currentRail);
    void setWaitingTime(WaitingTime waitingTime);
    void setDirection(TrainModel::TrainDirection direction);
    void setStopStation(StationModel *station);
    void removeStopStation(StationModel *station);
    void enableWaiting();
    void setSingleStop(bool state);
    TrainModel::TrainID getTrainID();
    StationModel* getCurrentStation();
    RailModel* getCurrentRail();
    TrainModel::TrainDirection getDirection();
    QList<StationModel *> *getStopStations();
    WaitingTime getWaitingTime();
    bool isWaiting();
    bool isSingleStop();

private:
    TrainModel::TrainID trainID;
    QList<StationModel*> stopStations;
    StationModel *currentStation = nullptr;
    RailModel *currentRail = nullptr;
    WaitingTime waitingTime = WAITING_1S;
    bool waiting = false;
    bool singleStop = false;
    TrainModel::TrainDirection direction;

public slots:
    void waitingEnd();
};

#endif // TRAFFICTIMETABLEMODEL_H
