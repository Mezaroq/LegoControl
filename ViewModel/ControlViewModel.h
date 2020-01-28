#ifndef CONTROLVIEWMODEL_H
#define CONTROLVIEWMODEL_H

#include <QObject>
#include <Model/ControlSlider.h>
#include <Model/ControlLight.h>
#include <Model/ControlSwitch.h>
#include <Model/ControlRail.h>
#include <Model/ControlTrain.h>
#include <Model/ControlSensor.h>
#include <ViewModel/ControlDataController.h>
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

class ControlViewModel : public QObject
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

    explicit ControlViewModel(QMainWindow* mainWindow, QObject *parent = nullptr);
    ~ControlViewModel();
    void setSliders(QMap<int, ControlSlider*> sliders);
    void setLights(QMap<int, ControlLight*> lights);
    void setSwitches(QMap<int, ControlSwitch*> switches);
    void setRails(QMap<int, ControlRail*> rails);
    void setTrains(QMap<int, ControlTrain*> trains);
    void setSensors(QMap<int, ControlSensor*> sensors);
    void setStatusBar(QStatusBar *statusBar);
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
    ControlDataController *dataController = nullptr;
    QMap<int, ControlSlider*> sliders;
    QMap<int, ControlLight*> lights;
    QMap<int, ControlSwitch*> switches;
    QMap<int, ControlRail*> rails;
    QMap<int, ControlTrain*> trains;
    QMap<int, ControlSensor*> sensors;
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
    void controlObjectClicked(ControlObject::ObjectType objectType, int objectID);
    void sensorsData(QByteArray data);
    void resetTrainsTriggered();
    void controllerConnected();
};

#endif // CONTROLVIEWMODEL_H
