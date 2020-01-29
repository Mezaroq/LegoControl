#ifndef CONTROLDEBUGGER_H
#define CONTROLDEBUGGER_H

#include <QDialog>
#include <Model/SensorModel.h>
#include <Model/RailModel.h>
#include <Model/SwitchModel.h>
#include <Model/TrainModel.h>
#include <Model/ControlTimetable.h>
#include <ViewModel/ControlAiViewModel.h>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMap>
#include <QDebug>
#include <QTimer>
#include <QThread>

namespace Ui {
class ControlDebugger;
}

class DebuggerView : public QDialog
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
        TIMETABLE_MAX_LOOP,
        TIMETABLE_LOOP_COUNTER,
        TIMETABLE_IGNORE_FLAG
    };

    explicit DebuggerView(QWidget *parent = nullptr);
    ~DebuggerView();
    void setMenu();
    void update();
    void setDebuggerData();
    void setSensors(QMap<int, SensorModel*> sensors);
    void setRails(QMap<int, RailModel*> rails);
    void setTrains(QMap<int, TrainModel*> trains);
    void setSwitches(QMap<int, SwitchModel*> switches);
    void setTimetables(QMap<TrainModel::TrainID, ControlTimetable *> *timetables);
    QString getTrainPriority(TrainModel *train);
    QString getTrainIDfromRail(TrainModel *train);
    QString getTrainFrom(RailModel::TrainMove trainFrom);
    QString getTimetableLoop (ControlTimetable::Loop loop);
    QString getSensorID(SensorModel::SensorID id);
    QString getTrainID(TrainModel::TrainID id);
    QString getRailID(RailModel::RailID id);
    QString getSwitchID(SwitchModel::SwitchID id);

private:
    bool debuggerIsRunning = false;
    bool aiModuleIsEnabled = false;
    QTimer* debuggerTimer;
    QThread *timerThread;
    Ui::ControlDebugger *ui;
    QMap<int, SensorModel*> sensors;
    QMap<int, RailModel*> rails;
    QMap<int, TrainModel*> trains;
    QMap<int, SwitchModel*> switches;
    QMap<TrainModel::TrainID, ControlTimetable *> *timetables;
    QTableWidget *trainTable;
    QTableWidget *railTable;
    QTableWidget *timetableTable;
    QTableWidget *switchTable;

public slots:
    void sensorClicked(int row, int column);
    void switchClicked(int row, int column);
    void timetableClicked(int row, int column);

private slots:
//    void debuggerLoop();
    void on_debuggerButton_clicked();
    void on_insertButton_clicked();
    void on_removeButton_clicked();
    void on_pushButton_toggled(bool checked);
};

#endif // CONTROLDEBUGGER_H
