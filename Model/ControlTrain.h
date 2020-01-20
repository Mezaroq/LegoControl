#ifndef CONTROLTRAIN_H
#define CONTROLTRAIN_H

#include <QObject>
#include <QTimer>
#include <Model/ControlSlider.h>

class ControlTrain : public QObject
{
    Q_OBJECT
public:
    enum TrainSpeed{
        SPEED_NEUTRAL,
        SPEED_FORWARD_1,
        SPEED_FORWARD_2,
        SPEED_FORWARD_3,
        SPEED_FORWARD_4,
        SPEED_FORWARD_5,
        SPEED_FORWARD_6,
        SPEED_FORWARD_7,
        SPEED_BREAKE,
        SPEED_REVERSE_7 = -7,
        SPEED_REVERSE_6,
        SPEED_REVERSE_5,
        SPEED_REVERSE_4,
        SPEED_REVERSE_3,
        SPEED_REVERSE_2,
        SPEED_REVERSE_1
    };
    enum TrainID{
        TRAIN_1,
        TRAIN_2,
        TRAIN_3,
        TRAIN_4,
        TRAIN_5,
        TRAIN_6,
        TRAIN_7,
        TRAIN_8,
    };

    enum TrainPriority{
        PRIORITY_8,
        PRIORITY_7,
        PRIORITY_6,
        PRIORITY_5,
        PRIORITY_4,
        PRIORITY_3,
        PRIORITY_2,
        PRIORITY_1
    };

    enum TrainDirection{
        DIRECTION_FORWARD = 1,
        DIRECTION_REVERSE = -1
    };

    explicit ControlTrain(TrainID trainID, ControlSlider *trainSlider, QObject *parent = nullptr);
    void setTrainSpeed(TrainSpeed trainSpeed);
    void setTrainPriority(TrainPriority trainPriority); // move to timetable
    void setWaiting(int mscs); // move to timetable
    bool isWaiting(); // move to timetable
    TrainID getTrainID();
    int getTrainSpeed();
    TrainPriority getTrainPriority(); // move to timetable / remove
    TrainDirection getTrainDirectionFromSpeed();

private:
    TrainID trainID;
    TrainPriority trainPriority = PRIORITY_1; // remove
    bool trainIsWaiting = false; // remove
    ControlSlider* trainSlider = nullptr;

signals:

public slots:
    void waitingEnded(); // remove
};

#endif // CONTROLTRAIN_H
