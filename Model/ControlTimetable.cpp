#include "ControlTimetable.h"
#include <QDebug>

ControlTimetable::ControlTimetable(TrainModel::TrainID trainID, RailModel::RailID railID, Loop loop, TrainModel::TrainDirection direction)
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

ControlTimetable *ControlTimetable::generateTimetable(TrainModel::TrainID trainID, int currentRailID)
{
    int loops = (qrand() % LOOP_5) + 1;
    RailModel::RailID railID = generateDestinationPoint(trainID, currentRailID);
    TrainModel::TrainDirection trainDirection;
    TrainModel::TrainDirection directions[2] = {TrainModel::DIRECTION_FORWARD, TrainModel::DIRECTION_REVERSE};
    if (trainID == TrainModel::TRAIN_3) {
        trainDirection = TrainModel::DIRECTION_FORWARD;
    } else {
        trainDirection = directions[qrand() % 2];
    }

    ControlTimetable *timetable = new ControlTimetable(trainID, railID, Loop(loops), trainDirection);
    return timetable;
}

RailModel::RailID ControlTimetable::generateDestinationPoint(TrainModel::TrainID trainID, int currentRailID)
{
    QList<RailModel::RailID> passengerStations;
    QList<RailModel::RailID> freightStations;

    passengerStations << RailModel::RAIL_SECTION_2 << RailModel::RAIL_SECTION_3 << RailModel::RAIL_SECTION_6 << RailModel::RAIL_SECTION_8;
    freightStations << RailModel::RAIL_SECTION_1 << RailModel::RAIL_SECTION_5 << RailModel::RAIL_SECTION_9;

    switch (trainID) {
    case TrainModel::TRAIN_1:
    case TrainModel::TRAIN_2:
        if (currentRailID != -1)
            passengerStations.removeOne(RailModel::RailID(currentRailID));
        std::random_shuffle(passengerStations.begin(), passengerStations.end());

        return passengerStations.takeFirst();
    case TrainModel::TRAIN_3:
        if (currentRailID != -1)
            freightStations.removeOne(RailModel::RailID(currentRailID));
        std::random_shuffle(freightStations.begin(), freightStations.end());

        return freightStations.takeFirst();
    case TrainModel::TRAIN_4:
    case TrainModel::TRAIN_5:
    case TrainModel::TRAIN_6:
    case TrainModel::TRAIN_7:
    case TrainModel::TRAIN_8:
        return RailModel::RAIL_SECTION_1;
    }
}

void ControlTimetable::increaseLoop()
{
    currentLoop++;
}

void ControlTimetable::setCurrentRailID(RailModel::RailID currentRailID)
{
    this->currentRailID = currentRailID;
}

void ControlTimetable::setDirection(TrainModel::TrainDirection direction)
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

TrainModel::TrainID ControlTimetable::getTrainID()
{
    return trainID;
}

RailModel::RailID ControlTimetable::getDestinationRailID()
{
    return destinationRailID;
}

RailModel::RailID ControlTimetable::getCurrentRailID()
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

TrainModel::TrainDirection ControlTimetable::getDirection()
{
    return direction;
}

int ControlTimetable::getLoopCounter()
{
    return loopCounter;
}
