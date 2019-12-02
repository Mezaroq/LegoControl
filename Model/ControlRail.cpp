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

void ControlRail::sensorChanged(ControlSensor::SensorType sensorType)
{
    qDebug() << sensorType;
    switch (sensorType) {
    case ControlSensor::LEFT_ENTRY_SENSOR:
        if (train == nullptr && entryCounter == 0) {
            entryCounter++;
        } else if(train == nullptr && entryCounter == 1) {
            entryCounter++;
            //set train and remove from previous
            setOpacity(0.5);
        } else if(train != nullptr && entryCounter == 2) {
            entryCounter--;
        } else if(train != nullptr && entryCounter == 1) {
            entryCounter--;
            //set train to next rail and remove this
            setOpacity(1);
        }
        break;
    case ControlSensor::RIGHT_ENTRY_SENSOR:
        if (train == nullptr && entryCounter == 0) {
            entryCounter++;
        } else if(train == nullptr && entryCounter == 1) {
            entryCounter++;
            //set train and remove from previous
            setOpacity(0.5);
        } else if(train != nullptr && entryCounter == 2) {
            entryCounter--;
        } else if(train != nullptr && entryCounter == 1) {
            entryCounter--;
            //set train to next rail and remove this
            setOpacity(1);
        }
        break;
    case ControlSensor::LEFT_STOP_SENSOR:
        break;
    case ControlSensor::RIGHT_STOP_SENSOR:
        break;

    }
}
