#ifndef CONTROLVIEWMODEL_H
#define CONTROLVIEWMODEL_H

#include <QObject>
#include <Model/ControlSlider.h>
#include <Model/ControlLight.h>
#include <Model/ControlSwitch.h>
#include <Model/ControlRail.h>
#include <Model/ControlTrain.h>
#include <ViewModel/ControlDataProvider.h>
#include <QThread>
#include <QMap>
#include <QDebug>
#include <QStatusBar>
#include <QList>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QByteArray>

class ControlViewModel : public QObject
{
    Q_OBJECT
public:
    enum Control{
        MAIN_CONTROL,
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
        LIGHT_CONTROL_6,
        LIGHT_CONTROL_7
    };
    explicit ControlViewModel(QObject *parent = nullptr);
    ~ControlViewModel();
    void setSliders(QMap<int, ControlSlider*> sliders);
    void setLights(QMap<int, ControlLight*> lights);
    void setSwitches(QMap<int, ControlSwitch*> switches);
    void setRails(QMap<int, ControlRail*> rails);
    void setTrains(QMap<int, ControlTrain*> trains);
    void setStatusBar(QStatusBar *statusBar);
    void prepareCollectedData(QByteArray byteArray);
    void collectControlData();

private:
    bool aiIsEnabled = false;
    QMap<int, ControlSlider*> sliders;
    QMap<int, ControlLight*> lights;
    QMap<int, ControlSwitch*> switches;
    QMap<int, ControlRail*> rails;
    QMap<int, ControlTrain*> trains;
    QStatusBar *statusBar;
    QByteArray controlData;
    QSerialPort *serialPort = nullptr;
    ControlDataProvider *dataProvider = nullptr;

signals:
    void controlDataCollected(QByteArray controlData);

public slots:
    void runTriggered();
    void aiEnabled(bool state);
    void settingsTriggered();
    void stopAllChannels();
    void controlObjectClicked(ControlObject::ObjectType objectType, int objectID);
    void dataFromSerialDeviceCollected(QByteArray readData);
};

#endif // CONTROLVIEWMODEL_H
