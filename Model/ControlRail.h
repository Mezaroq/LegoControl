#ifndef CONTROLRAIL_H
#define CONTROLRAIL_H

#include <Model/ControlObject.h>
#include <Model/ControlSensor.h>
#include <Model/ControlTrain.h>

class ControlRail : public ControlObject
{
    Q_OBJECT
public:
    enum RailID{
        RAIL_SECTION_1,
        RAIL_SECTION_2,
        RAIL_SECTION_3,
        RAIL_SECTION_4,
        RAIL_SECTION_5,
        RAIL_SECTION_6,
        RAIL_SECTION_7,
        RAIL_SECTION_8,
        RAIL_SECTION_9,
        RAIL_SECTION_10,
        RAIL_SECTION_11
    };
    explicit ControlRail(RailID railID);
    static QString getResource(RailID railID);

private:
    RailID railID;
    ControlTrain *train = nullptr;
    int entryCounter = 0;

signals:
    void objectChanged();

public slots:
    void sensorChanged(ControlSensor::SensorType sensorType);
};

#endif // CONTROLRAIL_H
