#include "RailModel.h"

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

bool RailModel::sensorDataCorrect(SensorModel::SensorType type)
{
    switch (type) {
    case SensorModel::REVERSE_ENTRY_SENSOR:
        if (currentTrain != nullptr || getRails(REVERSE).first()->getTrain() != nullptr)
            return true;
        break;
    case SensorModel::REVERSE_STOP_SENSOR:
        if (currentTrain != nullptr || getRails(REVERSE).first()->getTrain() != nullptr)
            return true;
        break;
    case SensorModel::FORWARD_STOP_SENSOR:
        if (currentTrain != nullptr || getRails(FORWARD).first()->getTrain() != nullptr)
            return true;
        break;
    case SensorModel::FORWARD_ENTRY_SENSOR:
        if (currentTrain != nullptr || getRails(FORWARD).first()->getTrain() != nullptr)
            return true;
        break;
    }
    return false;
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
    if (!sensorDataCorrect(sensorType)) {
        emit dataCorrupted();
        return;
    }

    switch (sensorType) {
    case SensorModel::REVERSE_ENTRY_SENSOR:
        if ((currentTrain == nullptr) && (entryCounter == 0)) {
            if (rails.value(REVERSE).first()->getTrain() != nullptr) {
                entryCounter = 1;
                emit trainEnters(rails.value(REVERSE).first()->getTrain(), this);
            }
        } else if ((currentTrain == nullptr) && (entryCounter == 1)) {
            if (rails.value(REVERSE).first()->getTrain() != nullptr) {
                trainMove = FORWARD;
                setTrain(rails.value(REVERSE).first()->getTrain(true));
                emit trainEnter(currentTrain, this);
            }
        } else if ((currentTrain != nullptr) && (entryCounter == 2)) {
            if (currentTrain != nullptr) {
                entryCounter = 1;
                emit trainLeaves(currentTrain, this);
            }
        } else if((currentTrain != nullptr) && (entryCounter == 1)) {
            if (currentTrain != nullptr) {
                emit trainLeave(currentTrain, this);
                rails.value(REVERSE).first()->setTrain(getTrain(true));
            }
        }
        break;
    case SensorModel::REVERSE_STOP_SENSOR:
        if (trainMove == REVERSE) {
            if (currentTrain != nullptr) {
                trainMove = UNDEFINED;
                emit trainStop(currentTrain, this);
            }
        }
        break;
    case SensorModel::FORWARD_STOP_SENSOR:
        if (trainMove == FORWARD) {
            if (currentTrain != nullptr) {
                trainMove = UNDEFINED;
                emit trainStop(currentTrain, this);
            }
        }
        break;
    case SensorModel::FORWARD_ENTRY_SENSOR:
        if ((currentTrain == nullptr) && (entryCounter == 0)) {
            if (rails.value(FORWARD).first()->getTrain() != nullptr) {
                entryCounter = 1;
                emit trainEnters(rails.value(FORWARD).first()->getTrain(), this);
            }
        } else if (currentTrain == nullptr && entryCounter == 1) {
            if (rails.value(FORWARD).first()->getTrain()) {
                trainMove = REVERSE;
                setTrain(rails.value(FORWARD).first()->getTrain(true));
                emit trainEnter(currentTrain, this);
            }
        } else if(currentTrain != nullptr && entryCounter == 2) {
            entryCounter = 1;
            emit trainLeaves(currentTrain, this);
        } else if(currentTrain != nullptr && entryCounter == 1) {
            emit trainLeave(currentTrain, this);
            rails.value(FORWARD).first()->setTrain(getTrain(true));
        }
        break;
    }
}
