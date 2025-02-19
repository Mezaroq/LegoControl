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
    enum SensorPosition{
        POSITION_SENSOR_1,
        POSITION_SENSOR_2,
        POSITION_SENSOR_3,
        POSITION_SENSOR_4,
        POSITION_SENSOR_5,
        POSITION_SENSOR_6,
        POSITION_SENSOR_7,
        POSITION_SENSOR_8,
        POSITION_SENSOR_9,
        POSITION_SENSOR_10,
        POSITION_SENSOR_11,
        POSITION_SENSOR_12,
        POSITION_SENSOR_13 = 16,
        POSITION_SENSOR_14,
        POSITION_SENSOR_15,
        POSITION_SENSOR_16,
        POSITION_SENSOR_17,
        POSITION_SENSOR_18,
        POSITION_SENSOR_19,
        POSITION_SENSOR_20,
        POSITION_SENSOR_21,
        POSITION_SENSOR_22,
        POSITION_SENSOR_23,
        POSITION_SENSOR_24,
        POSITION_SENSOR_25,
        POSITION_SENSOR_26,
        POSITION_SENSOR_27,
        POSITION_SENSOR_28
    };
    enum SensorType{
        REVERSE_ENTRY_SENSOR,
        REVERSE_STOP_SENSOR,
        FORWARD_STOP_SENSOR,
        FORWARD_ENTRY_SENSOR,
    };
    explicit SensorModel(SensorID sensorID, SensorType sensorType, QObject *parent = nullptr);
    void setSensorSignal(bool state);

private:
    SensorID sensorID;
    SensorType sensorType;
    bool state = false;

signals:
    void signalChanged(SensorModel::SensorType sensorType);
};

#endif // CONTROLSENSOR_H
