#include "ControlRail.h"
#include <QDebug>

ControlRail::ControlRail(RailID railID) : ControlObject(ControlObject::OBJECT_RAIL, railID)
{
    this->railID = railID;
    setPixmap(getResource(railID));
}

QString ControlRail::getResource(ControlRail::RailID railID)
{
    return ":/control/resources/objects/object_rail_section_" + QString::number(railID) + ".png";
}

void ControlRail::setTrain(ControlTrain *train)
{
    this->train = train;
    setOpacity(0.5); //rebuild
}

void ControlRail::setLastRails(QList<ControlRail *> rails)
{
    this->lastRails = rails;
}

void ControlRail::setNextRails(QList<ControlRail *> rails)
{
    this->nextRails = rails;
}

void ControlRail::setLastLight(ControlLight *controlLight)
{
    this->lastLight = controlLight;
}

void ControlRail::setNextLight(ControlLight *controlLight)
{
    this->nextLight = controlLight;
}

void ControlRail::setReservation(bool reservation)
{
    this->railReservation = reservation;
}

bool ControlRail::isReserved()
{
    return railReservation;
}

int ControlRail::getEntryCounter()
{
    return entryCounter;
}

ControlRail::TrainFrom ControlRail::getTrainFrom()
{
    return trainFrom;
}

ControlTrain *ControlRail::getTrain(bool remove)
{
    if (remove) {
        setOpacity(1); //rebuild
        ControlTrain *temp = train;
        train = nullptr;
        return temp;
    }
    return train;
}

QList<ControlRail *> ControlRail::getLastRails()
{
    return lastRails;
}

QList<ControlRail *> ControlRail::getNextRails()
{
    return nextRails;
}

ControlLight *ControlRail::getLastLight()
{
    return lastLight;
}

ControlLight *ControlRail::getNextLight()
{
    return nextLight;
}

ControlRail::RailID ControlRail::getRailID()
{
    return railID;
}

void ControlRail::sensorChanged(ControlSensor::SensorType sensorType)
{
    switch (sensorType) {
    case ControlSensor::LAST_ENTRY_SENSOR:
        if (train != nullptr && trainFrom == UNDEFINED && entryCounter == 0) {
            entryCounter++;
            if (train)
                emit trainLeaving(train->getTrainID(), railID);
        } else if(train != nullptr && trainFrom == UNDEFINED && entryCounter == 1) {
            entryCounter = 0;
            emit trainLeft(train->getTrainID(), railID);
            lastRails.first()->setTrain(getTrain(true));
        } else if (train == nullptr && trainFrom == UNDEFINED && entryCounter == 0) {
            entryCounter++;
            if (lastRails.first()->getTrain())
                emit trainEnters(lastRails.front()->getTrain()->getTrainID(), railID);
        } else if (train == nullptr && trainFrom == UNDEFINED && entryCounter == 1) {
            entryCounter++;
            if (lastRails.first()->getTrain()) {
                setTrain(lastRails.first()->getTrain(true));
                trainFrom = FROM_LAST;
                emit trainEntered(train->getTrainID(), railID);
            } else {
                entryCounter = 0;
            }
        } else if (train != nullptr && (trainFrom == FROM_LAST || trainFrom == FROM_NEXT) && entryCounter == 2) {
            entryCounter--;
            if (train) {
                emit trainLeaving(train->getTrainID(), railID);
            }
        } else if (train != nullptr && (trainFrom == FROM_LAST || trainFrom == FROM_NEXT) && entryCounter == 1) {
            entryCounter--;
            if (train) {
                emit trainLeft(train->getTrainID(), railID);
                lastRails.first()->setTrain(getTrain(true));
                trainFrom = UNDEFINED;
            }
        }
        break;

    case ControlSensor::NEXT_ENTRY_SENSOR:
        if (train != nullptr && trainFrom == UNDEFINED && entryCounter == 0) {
            entryCounter++;
            if (train)
                emit trainLeaving(train->getTrainID(), railID);
        } else if(train != nullptr && trainFrom == UNDEFINED && entryCounter == 1) {
            entryCounter = 0;
            emit trainLeft(train->getTrainID(), railID);
            nextRails.first()->setTrain(getTrain(true));
        } else if (train == nullptr && trainFrom == UNDEFINED && entryCounter == 0) {
            entryCounter++;
            if (nextRails.first()->getTrain())
                emit trainEnters(nextRails.front()->getTrain()->getTrainID(), railID);
        } else if (train == nullptr && trainFrom == UNDEFINED && entryCounter == 1) {
            entryCounter++;
            if (nextRails.first()->getTrain()) {
                setTrain(nextRails.first()->getTrain(true));
                trainFrom = FROM_NEXT;
                emit trainEntered(train->getTrainID(), railID);
            } else {
                entryCounter = 0;
            }
        } else if (train != nullptr && (trainFrom == FROM_LAST || trainFrom == FROM_NEXT) && entryCounter == 2) {
            entryCounter--;
            if (train)
                emit trainLeaving(train->getTrainID(), railID);
        } else if (train != nullptr && (trainFrom == FROM_LAST || trainFrom == FROM_NEXT) && entryCounter == 1) {
            entryCounter--;
            if (train) {
                emit trainLeft(train->getTrainID(), railID);
                nextRails.first()->setTrain(getTrain(true));
                trainFrom = UNDEFINED;
            }
        }
        break;

    case ControlSensor::LAST_STOP_SENSOR:
        if (train && trainFrom == FROM_NEXT) {
            emit trainActivatedStop(train->getTrainID(), railID);
        }
        break;

    case ControlSensor::NEXT_STOP_SENSOR:
        if (train && trainFrom == FROM_LAST) {
            emit trainActivatedStop(train->getTrainID(), railID);
        }
        break;
    }
}
