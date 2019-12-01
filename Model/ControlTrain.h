#ifndef CONTROLTRAIN_H
#define CONTROLTRAIN_H

#include <QObject>
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
        SPEED_REVERSE_1,
        SPEED_REVERSE_2,
        SPEED_REVERSE_3,
        SPEED_REVERSE_4,
        SPEED_REVERSE_5,
        SPEED_REVERSE_6,
        SPEED_REVERSE_7
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

    explicit ControlTrain(TrainID trainID, ControlSlider *trainSlider, QObject *parent = nullptr);
    int getTrainSpeed();

private:
    int trainID;
    ControlSlider* trainSlider = nullptr;


signals:

public slots:
};

#endif // CONTROLTRAIN_H
