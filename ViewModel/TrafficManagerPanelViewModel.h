#ifndef TRAFFICMANAGERPANELVIEWMODEL_H
#define TRAFFICMANAGERPANELVIEWMODEL_H

#include <QObject>
#include <Model/TrafficManagerButtonModel.h>
#include <Model/TrafficManagerLabelModel.h>
#include <Model/TrafficTimetableModel.h>
#include <Model/StationModel.h>
#include <Model/TrainModel.h>
#include <QMainWindow>
#include <QCoreApplication>
#include <QFileDialog>
#include <QMap>
#include <QDebug>

class TrafficManagerPanelViewModel : public QObject
{
    Q_OBJECT
public:
    enum ButtonIndex{
        TRAIN_1_CENTRAL = 10,
        TRAIN_1_NORTH,
        TRAIN_1_SOUTH,
        TRAIN_1_DIRECTION,
        TRAIN_2_CENTRAL = TRAIN_1_CENTRAL + 8,
        TRAIN_2_NORTH,
        TRAIN_2_SOUTH,
        TRAIN_2_DIRECTION,
        TRAIN_3_CENTRAL = TRAIN_2_CENTRAL + 8,
        TRAIN_3_NORTH,
        TRAIN_3_SOUTH,
        TRAIN_3_DIRECTION,
    };
    enum ConfigurationFile{
        CONFIG_TRAIN_ID,
        CONFIG_PRIORITY,
        CONFIG_WAIT_TIME,
        CONFIG_DIRECTION,
        CONFIG_INVERSION,
        CONFIG_STATIONS
    };
    explicit TrafficManagerPanelViewModel(QMainWindow *mainWindow, QObject *parent = nullptr);
    void initPanel();
    void updatePanel();
    void setManagerButtons(QMap<int, TrafficManagerButtonModel *> managerButtons);
    void setManagerLabels(QMap<int, TrafficManagerLabelModel*> managerLabels);
    void setTimetables(QMap<TrainModel::TrainID, TrafficTimetableModel*> *timetables);
    void setTrains(QMap<int, TrainModel *> trains);
    void setStations(QMap<int, StationModel *> stations);
    void setNormalSpeed(int *normalSpeed);
    void setSlowdownSpeed(int *slowdownSpeed);
    void setStartSpeed(int *startSpeed);
    bool getStopStationSelected(StationModel *station, TrainModel *train);
    void setPriorities();

private:
    QMainWindow *mainWindow;
    QMap<int, TrainModel *> trains;
    QMap<int, StationModel *> stations;
    QMap<int, TrafficManagerButtonModel*> managerButtons;
    QMap<int, TrafficManagerLabelModel*> managerLabels;
    QMap<TrainModel::TrainID, TrafficTimetableModel*> *timetables;
    QList<unsigned int> priorities;
    TrafficTimetableModel *timetable;
    int *normalSpeed;
    int *slowdownSpeed;
    int *startSpeed;

public slots:
    void managerButtonClicked(TrafficManagerButtonModel::ButtonCategory buttonCategory, TrafficManagerButtonModel::ButtonType buttonType, bool toggled);
    void saveConfig();
    void loadConfig();
};

#endif // TRAFFICMANAGERPANELVIEWMODEL_H
