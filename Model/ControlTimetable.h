#ifndef CONTROLTIMETABLE_H
#define CONTROLTIMETABLE_H

#include <Model/ControlTrain.h>
#include <Model/ControlRail.h>

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
    ControlTimetable(ControlTrain::TrainID trainID, ControlRail::RailID destinationRailID, Loop loop, ControlTrain::TrainDirection direction);
    static qint64 nextConnectionID();
    static ControlTimetable* generateTimetable(ControlTrain::TrainID trainID, int currentRailID);
    static ControlRail::RailID generateDestinationPoint(ControlTrain::TrainID trainID, int currentRailID);
    void increaseLoop();
    void setCurrentRailID(ControlRail::RailID currentRailID);
    void setDirection(ControlTrain::TrainDirection direction);
    bool isEndLoop();
    qint64 getConnectionID();
    ControlTrain::TrainID getTrainID();
    ControlRail::RailID getDestinationRailID();
    ControlRail::RailID getCurrentRailID();
    Loop getLoop();
    int getCurrentLoop();
    ControlTrain::TrainDirection getDirection();

private:
    int currentLoop = 1;
    qint64 connectionID;
    ControlTrain::TrainID trainID;
    ControlRail::RailID currentRailID;
    ControlRail::RailID destinationRailID;
    Loop loop;
    ControlTrain::TrainDirection direction;

};

#endif // CONTROLTIMETABLE_H
