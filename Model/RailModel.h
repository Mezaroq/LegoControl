#ifndef CONTROLRAIL_H
#define CONTROLRAIL_H

#include <Model/ObjectModel.h>
#include <Model/SensorModel.h>
#include <Model/TrainModel.h>
#include <Model/SwitchModel.h>
#include <Model/LightModel.h>
#include <QMap>
#include <QList>

class RailModel : public ObjectModel
{
    Q_OBJECT
public:
    enum RailID{
        RAIL_SECTION_1,
        RAIL_SECTION_2,
        RAIL_SECTION_3,
        RAIL_SECTION_4,
        RAIL_SECTION_5,
        RAIL_SECTION_6,
        RAIL_SECTION_7,
        RAIL_SECTION_8,
        RAIL_SECTION_9,
        RAIL_SECTION_10,
        RAIL_SECTION_11
    };
    enum TrainMove{
        FORWARD,
        REVERSE,
        UNDEFINED
    };
    explicit RailModel(RailID railID);
    static QString getResource(RailID railID);
    void setTrain(TrainModel *currentTrain);
    void setReservation(bool reservation);
    void setLights(QList<LightModel*> lights);
    void setRails(TrainMove direction, QList<RailModel*> rails);
    void clearStatus();
    bool sensorDataCorrect(SensorModel::SensorType type);
    LightModel* getLight(TrainMove direction);
    QList<RailModel*> getRails(TrainMove direction);
    TrainModel* getTrain(bool remove = false);
    RailID getRailID();
    bool isReserved();

private:
    RailID railID;
    int entryCounter = 0;
    bool railReservation = false;
    QMap<TrainMove, QList<RailModel*>> rails;
    QMap<TrainMove, LightModel*> lights;
    TrainModel *currentTrain = nullptr;
    TrainMove trainMove = UNDEFINED;

signals:
    void objectChanged();
    void trainEnter(TrainModel*, RailModel*);
    void trainLeave(TrainModel*, RailModel*);
    void trainEnters(TrainModel*, RailModel*);
    void trainLeaves(TrainModel*, RailModel*);
    void trainStop(TrainModel*, RailModel*);
    void dataCorrupted();

public slots:
    void sensorChanged(SensorModel::SensorType sensorType);
};

#endif // CONTROLRAIL_H
