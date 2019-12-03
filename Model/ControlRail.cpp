#include "ControlRail.h"
#include <QDebug>

ControlRail::ControlRail(RailID railID) : ControlObject(ControlObject::OBJECT_RAIL, railID)
{
    setPixmap(getResource(railID));
}

QString ControlRail::getResource(ControlRail::RailID railID)
{
    return ":/control/resources/objects/object_rail_section_" + QString::number(railID) + ".png";
}

void ControlRail::setTrain(ControlTrain *train)
{
    this->train = train;
}

ControlTrain *ControlRail::getTrain(bool remove)
{
    if (remove) {
        ControlTrain *temp = train;
        train = nullptr;
        return temp;
    }
    return train;
}

void ControlRail::sensorChanged(ControlSensor::SensorType sensorType)
{
    switch (sensorType) {
    case ControlSensor::TAIL_ENTRY_SENSOR:
        if (train == nullptr && entryCounter == 0) {
            entryCounter++;
        } else if(train == nullptr && entryCounter == 1) {
            entryCounter++;
            //set train and remove from previous
            train = new ControlTrain(ControlTrain::TRAIN_1, new ControlSlider()); //DEBUG
            trainFrom = FROM_TAIL;
            setOpacity(0.5);
        } else if(train != nullptr && entryCounter == 2) {
            entryCounter--;
        } else if(train != nullptr && entryCounter == 1) {
            entryCounter--;
            //set train to next rail and remove this
            train = nullptr;
            trainFrom = UNDEFINED;
            setOpacity(1);
        }
        break;
    case ControlSensor::HEAD_ENTRY_SENSOR:
        if (train == nullptr && entryCounter == 0) {
            entryCounter++;
        } else if(train == nullptr && entryCounter == 1) {
            entryCounter++;
            //set train and remove from previous
            train = new ControlTrain(ControlTrain::TRAIN_1, new ControlSlider());
            trainFrom = FROM_HEAD;
            setOpacity(0.5);
        } else if(train != nullptr && entryCounter == 2) {
            entryCounter--;
        } else if(train != nullptr && entryCounter == 1) {
            entryCounter--;
            //set train to next rail and remove this
            train = nullptr;
            trainFrom = UNDEFINED;
            setOpacity(1);
        }
        break;
    case ControlSensor::TAIL_STOP_SENSOR:
        if (train && trainFrom == FROM_HEAD) {
            //if train rail id == railID -> train stop and emit trainStopped() signal from this or train??
//            qDebug() << "train from head stop";
        }
        break;
    case ControlSensor::HEAD_STOP_SENSOR:
        if (train && trainFrom == FROM_TAIL) {
            //if train rail id == railID -> train stop and emit trainStopped() signal from this or train??
//            qDebug() << "train from tail stop";
        }
        break;
    }
}
