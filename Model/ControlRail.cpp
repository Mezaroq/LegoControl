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
    entryCounter = 2;
    railReservation = true;
    setOpacity(0.5);
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

void ControlRail::setTrainFrom(ControlRail::TrainFrom trainFrom)
{
    this->trainFrom = trainFrom;
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
        entryCounter = 0;
        trainFrom = UNDEFINED;
        railReservation = false;
        setOpacity(1);
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
        if (train == nullptr && entryCounter == 0) {
            entryCounter = 1;
            emit trainEnters(getLastRails().first()->getTrain()->getTrainID(), railID);
        } else if (train == nullptr && entryCounter == 1) {
            trainFrom = FROM_LAST;
            setTrain(getLastRails().first()->getTrain(true));
            emit trainEntered(train->getTrainID(), railID);
        } else if(train != nullptr && entryCounter == 2) {
            entryCounter = 1;
            emit trainLeaving(train->getTrainID(), railID);
        } else if(train != nullptr && entryCounter == 1) {
            emit trainLeft(train->getTrainID(), railID);
            getLastRails().first()->setTrain(getTrain(true));
        }
        break;
    case ControlSensor::LAST_STOP_SENSOR:
        if (train != nullptr && trainFrom == FROM_NEXT) {
            trainFrom = UNDEFINED;
            emit trainActivatedStop(train->getTrainID(), railID);
        }
        break;
    case ControlSensor::NEXT_STOP_SENSOR:
        if (train != nullptr && trainFrom == FROM_LAST) {
            trainFrom = UNDEFINED;
            emit trainActivatedStop(train->getTrainID(), railID);
        }
        break;
    case ControlSensor::NEXT_ENTRY_SENSOR:
        if (train == nullptr && entryCounter == 0) {
            entryCounter = 1;
            emit trainEnters(getNextRails().first()->getTrain()->getTrainID(), railID);
        } else if (train == nullptr && entryCounter == 1) {
            trainFrom = FROM_NEXT;
            setTrain(getNextRails().first()->getTrain(true));
            emit trainEntered(train->getTrainID(), railID);
        } else if(train != nullptr && entryCounter == 2) {
            entryCounter = 1;
            emit trainLeaving(train->getTrainID(), railID);
        } else if(train != nullptr && entryCounter == 1) {
            emit trainLeft(train->getTrainID(), railID);
            getNextRails().first()->setTrain(getTrain(true));
        }
        break;
    }
}
