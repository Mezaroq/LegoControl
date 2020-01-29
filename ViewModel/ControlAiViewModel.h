//#ifndef AIVIEWMODEL_H
//#define AIVIEWMODEL_H

//#include <QObject>
//#include <Model/ControlRail.h>
//#include <Model/ControlTrain.h>
//#include <Model/ControlSwitch.h>
//#include <Model/ControlLight.h>
//#include <Model/ControlTimetable.h>
//#include <Model/ControlSwitchMap.h>
//#include <QMap>
//#include <QList>

//class ControlAiViewModel : public QObject
//{
//    Q_OBJECT
//public:
//    enum SpeedType{
//        ENTERS,
//        LEAVING
//    };
//    explicit ControlAiViewModel(QObject *parent = nullptr);
//    void run();
//    void setAiEnabled(bool state);
//    void setSwitches(QMap<int, ControlSwitch*> switches);
//    void setRails(QMap<int, ControlRail*> rails);
//    void setTrains(QMap<int, ControlTrain*> trains);
//    void setLights(QMap<int, ControlLight*> lights);
//    void setSwitchMap(ControlSwitchMap *switchMap);
//    void generateTimetables();
//    void manageMovingTrains();
//    void manageStopTrains();
//    void antiBlocker();
//    void manageTrainSpeed(ControlTrain::TrainID trainID, SpeedType speedType);
//    void supportManualDriving(ControlTrain::TrainID trainID, ControlRail::RailID railID);
//    void setTrainWay(ControlTrain::TrainDirection direction, ControlRail *from, ControlRail *to, bool isEndLoop);
//    bool prepareTrainWay(ControlTrain *train, ControlRail *from, ControlRail *to, ControlTrain::TrainDirection direction, bool isEndLoop, bool ignoreFlag);
//    bool checkIfNotExistTrainWithHigherPriority(ControlTrain::TrainDirection direction, ControlRail *from, int priority, bool ignoreFlag);
//    bool checkIfRailsAreNotReseved(ControlTrain::TrainDirection direction, ControlRail *from, ControlRail *to, bool isEndLoop);
//    QMap<ControlTrain::TrainID, ControlTimetable*> *getTimetables();

//private:
//    const int WAITING_TIME = 10000;
//    const int STARTING_SPEED = ControlTrain::TrainSpeed::SPEED_FORWARD_4;
//    const int NORMAL_SPEED = ControlTrain::TrainSpeed::SPEED_FORWARD_5;
//    const int SLOWDOWN_SPEED = ControlTrain::TrainSpeed::SPEED_FORWARD_3;
//    bool aiIsEnabled = false;
//    ControlSwitchMap *switchMap;
//    ControlTimetable *timetable;
//    QMap<ControlTrain::TrainID, ControlTimetable*> timetables;
//    QMap<int, ControlSwitch*> switches;
//    QMap<int, ControlRail*> rails;
//    QMap<int, ControlTrain*> trains;
//    QMap<int, ControlLight*> lights;
//    QMap<ControlTrain*, ControlTrain::TrainSpeed> movingTrains;
//    QMap<int, ControlTrain::TrainID> stopTrains;

//signals:

//public slots:
//    void trainEnters(ControlTrain::TrainID trainID, ControlRail::RailID railID);
//    void trainEntered(ControlTrain::TrainID trainID, ControlRail::RailID railID);
//    void trainLeaving(ControlTrain::TrainID trainID, ControlRail::RailID railID);
//    void trainLeft(ControlTrain::TrainID trainID, ControlRail::RailID railID);
//    void stopSensorActivated(ControlTrain::TrainID trainID, ControlRail::RailID railID);

//};

//#endif // AIVIEWMODEL_H
