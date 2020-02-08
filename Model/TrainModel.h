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
        PRIORITY_MIN = 0U,
        PRIORITY_MAX = 12U,
        PRIORITY_NONE = 100U
    };
    enum TrainDirection{
        DIRECTION_FORWARD = 1,
        DIRECTION_REVERSE = -1
    };
    explicit TrainModel(TrainID trainID, SliderModel *trainSlider, TrainType trainType, QObject *parent = nullptr);
    void setTrainSpeed(TrainSpeed trainSpeed);
    void setTrainPrority(unsigned int trainPriority);
    void setInverseSpeed(bool inverseSpeed);
    TrainID getTrainID();
    TrainType getTrainType();
    unsigned int getTrainPriority();
    TrainDirection getDirectionMultiplier();
    int getTrainSpeed();
    int getTrainControl();
    bool isInverse();

private:
    TrainID trainID;
    TrainType trainType;
    unsigned int trainPriority = PRIORITY_NONE;
    bool inverseSpeed = false;
    SliderModel* trainSlider = nullptr;
};

#endif // CONTROLTRAIN_H
