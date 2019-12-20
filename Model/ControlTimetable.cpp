#include "ControlTimetable.h"
#include <QDebug>

ControlTimetable::ControlTimetable(ControlTrain::TrainID trainID, ControlRail::RailID railID, Loop loop, ControlTrain::TrainDirection direction)
{
    this->connectionID = nextConnectionID();
    this->trainID = trainID;
    this->destinationRailID = railID;
    this->loop = loop;
    this->direction = direction;
}

qint64 ControlTimetable::nextConnectionID()
{
    static qint64 connectionID = 0;
    return connectionID++;
}

ControlTimetable *ControlTimetable::generateTimetable(ControlTrain::TrainID trainID, int currentRailID)
{
    int loops = (qrand() % LOOP_5) + 1;
    ControlRail::RailID railID = generateDestinationPoint(trainID, currentRailID);
    ControlTrain::TrainDirection trainDirection;
    ControlTrain::TrainDirection directions[2] = {ControlTrain::DIRECTION_FORWARD, ControlTrain::DIRECTION_REVERSE};
    if (trainID == ControlTrain::TRAIN_3) {
        trainDirection = ControlTrain::DIRECTION_FORWARD;
    } else {
        trainDirection = directions[qrand() % 2];
    }

    ControlTimetable *timetable = new ControlTimetable(trainID, railID, Loop(loops), trainDirection);
    return timetable;
}

ControlRail::RailID ControlTimetable::generateDestinationPoint(ControlTrain::TrainID trainID, int currentRailID)
{
    QList<ControlRail::RailID> passengerStations;
    QList<ControlRail::RailID> freightStations;

    passengerStations << ControlRail::RAIL_SECTION_2 << ControlRail::RAIL_SECTION_3 << ControlRail::RAIL_SECTION_6 << ControlRail::RAIL_SECTION_8;
    freightStations << ControlRail::RAIL_SECTION_1 << ControlRail::RAIL_SECTION_5 << ControlRail::RAIL_SECTION_9;

    switch (trainID) {
    case ControlTrain::TRAIN_1:
    case ControlTrain::TRAIN_2:
        if (currentRailID != -1)
            passengerStations.removeOne(ControlRail::RailID(currentRailID));
        std::random_shuffle(passengerStations.begin(), passengerStations.end());

        return passengerStations.takeFirst();
    case ControlTrain::TRAIN_3:
        if (currentRailID != -1)
            freightStations.removeOne(ControlRail::RailID(currentRailID));
        std::random_shuffle(freightStations.begin(), freightStations.end());

        return freightStations.takeFirst();
    case ControlTrain::TRAIN_4:
    case ControlTrain::TRAIN_5:
    case ControlTrain::TRAIN_6:
    case ControlTrain::TRAIN_7:
    case ControlTrain::TRAIN_8:
        return ControlRail::RAIL_SECTION_1;
    }
}

void ControlTimetable::increaseLoop()
{
    currentLoop++;
}

void ControlTimetable::setCurrentRailID(ControlRail::RailID currentRailID)
{
    this->currentRailID = currentRailID;
}

void ControlTimetable::setDirection(ControlTrain::TrainDirection direction)
{
    this->direction = direction;
}

void ControlTimetable::increaseLoopCounter()
{
    if (currentLoop != loop) {
        loopCounter++;
        if (loopCounter == MAX_LOOP_COUNTER) {
            loopCounter = 0;
            increaseLoop();
        }
    }
}

void ControlTimetable::setIgnoreTrain(bool state)
{
    this->ignoreTrainWithHigherPriority = state;
}

bool ControlTimetable::isIgnoreTrain()
{
    return ignoreTrainWithHigherPriority;
}

bool ControlTimetable::isEndLoop()
{
    return (currentLoop == loop);
}

qint64 ControlTimetable::getConnectionID()
{
    return connectionID;
}

ControlTrain::TrainID ControlTimetable::getTrainID()
{
    return trainID;
}

ControlRail::RailID ControlTimetable::getDestinationRailID()
{
    return destinationRailID;
}

ControlRail::RailID ControlTimetable::getCurrentRailID()
{
    return currentRailID;
}

ControlTimetable::Loop ControlTimetable::getLoop()
{
    return loop;
}

int ControlTimetable::getCurrentLoop()
{
    return currentLoop;
}

ControlTrain::TrainDirection ControlTimetable::getDirection()
{
    return direction;
}

int ControlTimetable::getLoopCounter()
{
    return loopCounter;
}
