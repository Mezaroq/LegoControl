#ifndef CONTROLSENSOR_H
#define CONTROLSENSOR_H

#include <QObject>

class SensorModel : public QObject
{
    Q_OBJECT
public:
    enum SensorID{
        SENSOR_1,
        SENSOR_2,
        SENSOR_3,
        SENSOR_4,
        SENSOR_5,
        SENSOR_6,
        SENSOR_7,
        SENSOR_8,
        SENSOR_9,
        SENSOR_10,
        SENSOR_11,
        SENSOR_12,
        SENSOR_13,
        SENSOR_14,
        SENSOR_15,
        SENSOR_16,
        SENSOR_17,
        SENSOR_18,
        SENSOR_19,
        SENSOR_20,
        SENSOR_21,
        SENSOR_22,
        SENSOR_23,
        SENSOR_24,
        SENSOR_25,
        SENSOR_26,
        SENSOR_27,
        SENSOR_28
    };
    enum SensorType{
        REVERSE_ENTRY_SENSOR,
        REVERSE_STOP_SENSOR,
        FORWARD_STOP_SENSOR,
        FORWARD_ENTRY_SENSOR,
    };

    explicit SensorModel(SensorID sensorID, SensorType sensorType, QObject *parent = nullptr);
    void setState(bool newState);
    void debugSignal();

private:
    SensorID sensorID;
    SensorType sensorType;
    bool state = false;

signals:
    void signalChanged(SensorModel::SensorType sensorType);

};

#endif // CONTROLSENSOR_H
