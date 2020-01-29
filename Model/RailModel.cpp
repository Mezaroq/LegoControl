#include "RailModel.h"
#include <QDebug>

RailModel::RailModel(RailID railID) : ObjectModel(ObjectModel::OBJECT_RAIL, railID)
{
    this->railID = railID;
    setPixmap(getResource(railID));
}

QString RailModel::getResource(RailModel::RailID railID)
{
    return ":/control/resources/objects/object_rail_section_" + QString::number(railID) + ".png";
}

void RailModel::setTrain(TrainModel *train)
{
    this->currentTrain = train;
    entryCounter = 2;
    railReservation = true;
    setOpacity(0.5);
}

void RailModel::setReservation(bool reservation)
{
    this->railReservation = reservation;
}

bool RailModel::isReserved()
{
    return railReservation;
}

void RailModel::setLights(QList<LightModel *> lights)
{
    this->lights.insert(REVERSE, lights.at(FORWARD));
    this->lights.insert(FORWARD, lights.at(REVERSE));
}

LightModel *RailModel::getLight(RailModel::TrainMove direction)
{
    return lights.value(direction);
}

void RailModel::setRails(RailModel::TrainMove direction, QList<RailModel *> rails)
{
    this->rails.insert(direction, rails);
}

QList<RailModel *> RailModel::getRails(RailModel::TrainMove direction)
{
    return rails.value(direction);
}

TrainModel *RailModel::getTrain(bool remove)
{
    if (remove) {
        trainMove = UNDEFINED;
        entryCounter = 0;
        railReservation = false;
        setOpacity(1);
        TrainModel *temp = currentTrain;
        currentTrain = nullptr;
        return temp;
    }
    return currentTrain;
}

RailModel::RailID RailModel::getRailID()
{
    return railID;
}

void RailModel::sensorChanged(SensorModel::SensorType sensorType)
{
    switch (sensorType) {
    case SensorModel::REVERSE_ENTRY_SENSOR:
        if ((currentTrain == nullptr) && (entryCounter == 0)) {
            if (rails.value(REVERSE).first()->getTrain() != nullptr) {
                entryCounter = 1;
                emit (trainEnters(rails.value(REVERSE).first()->getTrain()->getTrainID(), railID));
            }
        } else if ((currentTrain == nullptr) && (entryCounter == 1)) {
            if (rails.value(REVERSE).first()->getTrain() != nullptr) {
                trainMove = FORWARD;
                setTrain(rails.value(REVERSE).first()->getTrain(true));
                emit trainEntered(currentTrain->getTrainID(), railID);
            }
        } else if ((currentTrain != nullptr) && (entryCounter == 2)) {
            if (currentTrain != nullptr) {
                entryCounter = 1;
                emit trainLeaving(currentTrain->getTrainID(), railID);
            }
        } else if((currentTrain != nullptr) && (entryCounter == 1)) {
            if (currentTrain != nullptr) {
                emit trainLeft(currentTrain->getTrainID(), railID);
                rails.value(REVERSE).first()->setTrain(getTrain(true));
            }
        }
        break;
    case SensorModel::REVERSE_STOP_SENSOR:
        if ((currentTrain != nullptr) && (trainMove == REVERSE)) {
            trainMove = UNDEFINED;
            emit trainActivatedStop(currentTrain->getTrainID(), railID);
        }
        break;
    case SensorModel::FORWARD_STOP_SENSOR:
        if ((currentTrain != nullptr) && (trainMove == FORWARD)) {
            trainMove = UNDEFINED;
            emit trainActivatedStop(currentTrain->getTrainID(), railID);
        }
        break;
    case SensorModel::FORWARD_ENTRY_SENSOR:
        if ((currentTrain == nullptr) && (entryCounter == 0)) {
            if (rails.value(FORWARD).first()->getTrain() != nullptr) {
                entryCounter = 1;
                emit trainEnters(rails.value(FORWARD).first()->getTrain()->getTrainID(), railID);
            }
        } else if (currentTrain == nullptr && entryCounter == 1) {
            if (rails.value(FORWARD).first()->getTrain()) {
                trainMove = REVERSE;
                setTrain(rails.value(FORWARD).first()->getTrain(true));
                emit trainEntered(currentTrain->getTrainID(), railID);
            }
        } else if(currentTrain != nullptr && entryCounter == 2) {
            if (currentTrain != nullptr) {
                entryCounter = 1;
                emit trainLeaving(currentTrain->getTrainID(), railID);
            }
        } else if(currentTrain != nullptr && entryCounter == 1) {
            if (currentTrain != nullptr) {
                emit trainLeft(currentTrain->getTrainID(), railID);
                rails.value(FORWARD).first()->setTrain(getTrain(true));
            }
        }
        break;
    }
}
