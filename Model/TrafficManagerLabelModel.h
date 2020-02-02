#ifndef TRAFFICMANAGERLABELMODEL_H
#define TRAFFICMANAGERLABELMODEL_H

#include <QWidget>
#include <QLabel>

class TrafficManagerLabelModel : public QLabel
{
    Q_OBJECT
public:
    enum LabelType{
        NORMAL_SPEED,
        SLOWDOWN_SPEED,
        START_SPEED,
        PRIORITY_TRAIN_1,
        WAITING_TRAIN_1,
        PRIORITY_TRAIN_2,
        WAITING_TRAIN_2,
        PRIORITY_TRAIN_3,
        WAITING_TRAIN_3
    };
    explicit TrafficManagerLabelModel(QWidget *parent = nullptr);

signals:

};

#endif // TRAFFICMANAGERLABELMODEL_H
