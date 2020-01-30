#ifndef CONTROLVIEWMODEL_H
#define CONTROLVIEWMODEL_H

#include <QObject>
#include <Model/SliderModel.h>
#include <Model/LightModel.h>
#include <Model/SwitchModel.h>
#include <Model/RailModel.h>
#include <Model/TrainModel.h>
#include <Model/SensorModel.h>
#include <ViewModel/DataViewModel.h>
#include <ViewModel/TrafficManagerViewModel.h>
#include <QMap>
#include <QDebug>
#include <QStatusBar>
#include <QList>
#include <QSerialPortInfo>
#include <QByteArray>
#include <QMessageBox>
#include <QMainWindow>
#include <QGraphicsBlurEffect>
#include <QTimer>

class MainViewModel : public QObject
{
    Q_OBJECT
public:
    enum Control{
        TRANSMISSION_CONTROL,
        TRAIN_CONTROL_1,
        TRAIN_CONTROL_2,
        TRAIN_CONTROL_3,
        TRAIN_CONTROL_4,
        TRAIN_CONTROL_5,
        TRAIN_CONTROL_6,
        TRAIN_CONTROL_7,
        TRAIN_CONTROL_8,
        SWITCH_CONTROL_1,
        SWITCH_CONTROL_2,
        LIGHT_CONTROL_1,
        LIGHT_CONTROL_2,
        LIGHT_CONTROL_3,
        LIGHT_CONTROL_4,
        LIGHT_CONTROL_5,
        LIGHT_CONTROL_6
    };
    enum TransmissionControl{
        LIGHT_TRANSMISSION_CONTROL_1 = 0x01,
        LIGHT_TRANSMISSION_CONTROL_2 = 0x02,
        LIGHT_TRANSMISSION_CONTROL_3 = 0x04,
        SWITCH_TRANSMISSION_CONTROL_1 = 0x08
    };

    explicit MainViewModel(QMainWindow* mainWindow, QObject *parent = nullptr);
    ~MainViewModel();
    void setSliders(QMap<int, SliderModel*> sliders);
    void setLights(QMap<int, LightModel*> lights);
    void setSwitches(QMap<int, SwitchModel*> switches);
    void setRails(QMap<int, RailModel*> rails);
    void setTrains(QMap<int, TrainModel*> trains);
    void setSensors(QMap<int, SensorModel*> sensors);
    void setStatusBar(QStatusBar *statusBar);
    void setTrafficManager(TrafficManagerViewModel* trafficManager);
    void setMainWindow(QMainWindow mainWindow);
    void setSensorsData(QByteArray byteArray);
    void collectControlData();
    void setSerialPortInformation();
    void loadTrainPosition();
    char getTransmissionControl();

private:
    const int MAX_TRAINS = 3;
    int insertedTrains = 0;
    bool selectionMode = false;
    TrafficManagerViewModel *trafficManager = nullptr;
    DataViewModel *dataController = nullptr;
    QMap<int, SliderModel*> sliders;
    QMap<int, LightModel*> lights;
    QMap<int, SwitchModel*> switches;
    QMap<int, RailModel*> rails;
    QMap<int, TrainModel*> trains;
    QMap<int, SensorModel*> sensors;
    QStatusBar *statusBar;
    QByteArray controlData;
    QByteArray lastControlData;
    QMessageBox* loadTrains;
    QMessageBox* resetTrains;
    QMainWindow* mainWindow;

protected:
    void setDataController();

signals:
    void controlDataCollected(QByteArray controlData);

public slots:
    void runTriggered();
    void aiEnabled(bool state);
    void stopAllChannels();
    void controlObjectClicked(ObjectModel::ObjectType objectType, int objectID);
    void sensorsData(QByteArray data);
    void resetTrainsTriggered();
    void controllerConnected();
};

#endif // CONTROLVIEWMODEL_H
