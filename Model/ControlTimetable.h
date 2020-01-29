#ifndef CONTROLTIMETABLE_H
#define CONTROLTIMETABLE_H

#include <Model/TrainModel.h>
#include <Model/RailModel.h>

class ControlTimetable
{
public:
    enum Loop{
        LOOP_1 = 1,
        LOOP_2,
        LOOP_3,
        LOOP_4,
        LOOP_5
    };
    ControlTimetable(TrainModel::TrainID trainID, RailModel::RailID destinationRailID, Loop loop, TrainModel::TrainDirection direction);
    static qint64 nextConnectionID();
    static ControlTimetable* generateTimetable(TrainModel::TrainID trainID, int currentRailID);
    static RailModel::RailID generateDestinationPoint(TrainModel::TrainID trainID, int currentRailID);
    void increaseLoop();
    void setCurrentRailID(RailModel::RailID currentRailID);
    void setDirection(TrainModel::TrainDirection direction);
    void increaseLoopCounter();
    void setIgnoreTrain(bool state);
    bool isIgnoreTrain();
    bool isEndLoop();
    qint64 getConnectionID();
    TrainModel::TrainID getTrainID();
    RailModel::RailID getDestinationRailID();
    RailModel::RailID getCurrentRailID();
    Loop getLoop();
    int getCurrentLoop();
    TrainModel::TrainDirection getDirection();
    int getLoopCounter();

private:
    const int MAX_LOOP_COUNTER = 3;
    bool ignoreTrainWithHigherPriority = false;
    int loopCounter = 0;
    int currentLoop = 1;
    qint64 connectionID;
    TrainModel::TrainID trainID;
    RailModel::RailID currentRailID;
    RailModel::RailID destinationRailID;
    TrainModel::TrainDirection direction;
    Loop loop;
};

#endif // CONTROLTIMETABLE_H
