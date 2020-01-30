#ifndef CONTROLTRAIN_H
#define CONTROLTRAIN_H

#include <QObject>
#include <QTimer>
#include <Model/SliderModel.h>

class TrainModel : public QObject
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

    enum TrainType{
        FREIGHT_TRAIN,
        PASSENGER_TRAIN
    };

    enum TrainPriority{
        PRIORITY_0,
        PRIORITY_1,
        PRIORITY_2,
        PRIORITY_3,
        PRIORITY_4,
        PRIORITY_5,
        PRIORITY_6,
        PRIORITY_7
    };

    enum TrainDirection{
        DIRECTION_FORWARD = 1,
        DIRECTION_REVERSE = -1
    };

    explicit TrainModel(TrainID trainID, SliderModel *trainSlider, TrainType trainType, QObject *parent = nullptr);
    void setTrainSpeed(TrainSpeed trainSpeed);
    void setTrainPrority(TrainPriority trainPriority);
    TrainID getTrainID();
    TrainType getTrainType();
    TrainPriority getTrainPriority();
    TrainDirection getDirectionMultiplier();
    int getTrainSpeed();

private:
    TrainID trainID;
    TrainType trainType;
    TrainPriority trainPriority;
    SliderModel* trainSlider = nullptr;
};

#endif // CONTROLTRAIN_H
