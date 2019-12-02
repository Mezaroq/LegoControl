#ifndef CONTROLRAIL_H
#define CONTROLRAIL_H

#include <Model/ControlObject.h>
#include <Model/ControlSensor.h>
#include <Model/ControlTrain.h>
#include <Model/ControlSwitch.h>
#include <Model/ControlLight.h>
#include <QList>

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
    enum TrainFrom{
        FROM_TAIL,
        FROM_HEAD,
        UNDEFINED
    };

    explicit ControlRail(RailID railID);
    static QString getResource(RailID railID);
    void setTrain(ControlTrain *train);
    ControlTrain* getTrain(bool remove = false);


private:
    RailID railID;
    int entryCounter = 0;
    QList<ControlRail*> leftRails;
    QList<ControlRail*> rightRails;
    ControlTrain *train = nullptr;
    TrainFrom trainFrom = UNDEFINED;

signals:
    void objectChanged();

public slots:
    void sensorChanged(ControlSensor::SensorType sensorType);
};

#endif // CONTROLRAIL_H
