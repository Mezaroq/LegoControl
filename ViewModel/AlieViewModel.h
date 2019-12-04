#ifndef ALIEVIEWMODEL_H
#define ALIEVIEWMODEL_H

#include <QObject>
#include <Model/ControlRail.h>
#include <Model/ControlTrain.h>
#include <Model/ControlSwitch.h>
#include <QMap>
#include <QList>

class AlieViewModel : public QObject
{
    Q_OBJECT
public:
    explicit AlieViewModel(QObject *parent = nullptr);
    void run();
    void setAiEnabled(bool state);
    void setSwitches(QMap<int, ControlSwitch*> switches);
    void setRails(QMap<int, ControlRail*> rails);
    void setTrains(QMap<int, ControlTrain*> trains);
    void setTrainSpeedFromList();

private:
    bool alieIsEnabled = false;
    QMap<int, ControlSwitch*> switches;
    QMap<int, ControlRail*> rails;
    QMap<int, ControlTrain*> trains;
    QMap<ControlTrain*, ControlTrain::TrainSpeed> trainSpeedMap;

signals:

public slots:
    void trainEnters(ControlTrain::TrainID trainID);
    void trainEntered(ControlTrain::TrainID trainID);
    void trainLeaving(ControlTrain::TrainID trainID);
    void trainLeft(ControlTrain::TrainID trainID);
    void stopSensorActivated(ControlTrain::TrainID trainID, ControlRail::RailID railID);

};

#endif // ALIEVIEWMODEL_H
