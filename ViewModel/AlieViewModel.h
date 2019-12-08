#ifndef ALIEVIEWMODEL_H
#define ALIEVIEWMODEL_H

#include <QObject>
#include <Model/ControlRail.h>
#include <Model/ControlTrain.h>
#include <Model/ControlSwitch.h>
#include <Model/ControlTimetable.h>
#include <QMap>
#include <QList>

class AlieViewModel : public QObject
{
    Q_OBJECT
public:
    explicit AlieViewModel(QObject *parent = nullptr);
    void run();
    void createSwitchMap();
    QList<ControlSwitch *> getSwitchMap(ControlRail::RailID from, ControlRail::RailID to);
    void setAiEnabled(bool state);
    void setSwitches(QMap<int, ControlSwitch*> switches);
    void setRails(QMap<int, ControlRail*> rails);
    void setTrains(QMap<int, ControlTrain*> trains);
    void generateTimetables();
    void manageMovingTrains();
    void manageStopTrains();
    void setSwitches(ControlRail *from, ControlRail *to);
    void setTrainWay(ControlTrain::TrainDirection direction, ControlRail *from, ControlRail *to, bool isEndLoop);
    bool prepareTrainWay(ControlTrain *train, ControlRail *from, ControlRail *to, ControlTrain::TrainDirection direction, bool isEndLoop);
    bool checkIfExistTrainWithHigherPriority(ControlTrain::TrainDirection direction, ControlRail *from, ControlTrain::TrainPriority priority);
    bool checkIfRailsAreFree(ControlTrain::TrainDirection direction, ControlRail *from, ControlRail *to, bool isEndLoop);
    bool checkIfSwitchesAreFree(ControlRail *from, ControlRail *to);
    QMap<ControlTrain::TrainID, ControlTimetable*> *getTimetables();

private:
    int debugStep = 1;
    const int WAITING_TIME = 10000;
    const int SPEED = ControlTrain::TrainSpeed::SPEED_FORWARD_4;
    bool alieIsEnabled = false;
    ControlTimetable *currentTrainTimetable;
    ControlTimetable *timetable;
    QMap<ControlTrain::TrainID, ControlTimetable*> timetables;
    QMap<int, ControlSwitch*> switches;
    QMap<int, ControlRail*> rails;
    QMap<int, ControlTrain*> trains;
    QMap<ControlTrain*, ControlTrain::TrainSpeed> movingTrains;
    QMap<ControlTrain::TrainPriority, ControlTrain::TrainID> stopTrains;
    QMap<QPair<int, int>, QList<ControlSwitch*>> switchMap;

signals:

public slots:
    void trainEnters(ControlTrain::TrainID trainID, ControlRail::RailID railID);
    void trainEntered(ControlTrain::TrainID trainID, ControlRail::RailID railID);
    void trainLeaving(ControlTrain::TrainID trainID, ControlRail::RailID railID);
    void trainLeft(ControlTrain::TrainID trainID, ControlRail::RailID railID);
    void stopSensorActivated(ControlTrain::TrainID trainID, ControlRail::RailID railID);

};

#endif // ALIEVIEWMODEL_H
