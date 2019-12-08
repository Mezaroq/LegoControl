#ifndef CONTROLDEBUGGER_H
#define CONTROLDEBUGGER_H

#include <QDialog>
#include <Model/ControlSensor.h>
#include <Model/ControlRail.h>
#include <Model/ControlSwitch.h>
#include <Model/ControlTrain.h>
#include <Model/ControlTimetable.h>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMap>
#include <QDebug>
#include <QTimer>
#include <QThread>

namespace Ui {
class ControlDebugger;
}

class ControlDebugger : public QDialog
{
    Q_OBJECT
public:
    enum TrainTable{
        TRAIN_ID,
        TRAIN_PRIORITY,
        TRAIN_WAITING,
        TRAIN_SPEED
    };
    enum RailTable{
        RAIL_ID,
        RAIL_COUNTER,
        RAIL_RESERVATION,
        RAIL_TRAIN_ID,
        RAIL_TRAIN_FROM,
        RAIL_SENSOR_ENTRY_LAST,
        RAIL_SENSOR_STOP_LAST,
        RAIL_SENSOR_ENTRY_NEXT,
        RAIL_SENSOR_STOP_NEXT
    };
    enum SwitchTable{
        SWITCH_ID,
        SWITCH_TOGGLE,
        SWITCH_RESERVATION
    };
    enum TimetableTable{
        TIMETABLE_ID,
        TIMETABLE_TRAIN_ID,
        TIMETABLE_CURRENT_RAIL_ID,
        TIMETABLE_DESTINATION_RAIL_ID,
        TIMETABLE_TRAIN_DIRECTION,
        TIMETABLE_CURRENT_LOOP,
        TIMETABLE_MAX_LOOP
    };

    explicit ControlDebugger(QWidget *parent = nullptr);
    void setMenu();
    ~ControlDebugger();
    void update();
    void setDebuggerData();
    void setSensors(QMap<int, ControlSensor*> sensors);
    void setRails(QMap<int, ControlRail*> rails);
    void setTrains(QMap<int, ControlTrain*> trains);
    void setSwitches(QMap<int, ControlSwitch*> switches);
    void setTimetables(QMap<ControlTrain::TrainID, ControlTimetable *> *timetables);
    QString getTrainPriority(ControlTrain *train);
    QString getTrainIDfromRail(ControlTrain *train);
    QString getTrainFrom(ControlRail::TrainFrom trainFrom);
    QString getTimetableLoop (ControlTimetable::Loop loop);
    QString getSensorID(ControlSensor::SensorID id);
    QString getTrainID(ControlTrain::TrainID id);
    QString getRailID(ControlRail::RailID id);
    QString getSwitchID(ControlSwitch::SwitchID id);

private:
    bool debuggerIsRunning = false;
    QTimer* debuggerTimer;
    QThread *timerThread;
    Ui::ControlDebugger *ui;
    QMap<int, ControlSensor*> sensors;
    QMap<int, ControlRail*> rails;
    QMap<int, ControlTrain*> trains;
    QMap<int, ControlSwitch*> switches;
    QMap<ControlTrain::TrainID, ControlTimetable *> *timetables;
    QTableWidget *trainTable;
    QTableWidget *railTable;
    QTableWidget *timetableTable;
    QTableWidget *switchTable;

public slots:
    void sensorClicked(int row, int column);

private slots:
    void debuggerLoop();
    void on_debuggerButton_clicked();
    void on_insertButton_clicked();
    void on_removeButton_clicked();
};

#endif // CONTROLDEBUGGER_H
