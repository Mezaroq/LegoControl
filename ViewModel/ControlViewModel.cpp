#include "ControlViewModel.h"
#include <QTimer> //debug timer, delete after debug

ControlViewModel::ControlViewModel(QObject *parent) : QObject(parent)
{
    dataProvider = new ControlDataProvider();
    connect(dataProvider, SIGNAL(dataFromSerialDeviceReady(QByteArray)), this, SLOT(dataFromSerialDeviceCollected(QByteArray)));
    connect(this, SIGNAL(controlDataCollected(QByteArray)), dataProvider, SLOT(dataToSerialDeviceReady(QByteArray)));
    //after run check if file exist and load last train positions to rails

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(settingsTriggered()));
//    timer->start(200);
}

ControlViewModel::~ControlViewModel()
{
    if (!dataProvider) {
        dataProvider->terminate();
        dataProvider->wait();
        dataProvider->exit();
        delete dataProvider;
    }
}

void ControlViewModel::setSliders(QMap<int, ControlSlider *> sliders)
{
    this->sliders = sliders;
}

void ControlViewModel::setLights(QMap<int, ControlLight *> lights)
{
    this->lights = lights;
}

void ControlViewModel::setSwitches(QMap<int, ControlSwitch *> switches)
{
    this->switches = switches;
}

void ControlViewModel::setRails(QMap<int, ControlRail *> rails)
{
    this->rails = rails;
}

void ControlViewModel::setTrains(QMap<int, ControlTrain *> trains)
{
    this->trains = trains;
}

void ControlViewModel::setStatusBar(QStatusBar *statusBar)
{
    this->statusBar = statusBar;
}

void ControlViewModel::prepareCollectedData(QByteArray byteArray)
{
//    qDebug() << byteArray.toHex('|');
    QList<QByteArray> listOfBytes = byteArray.toHex('|').split('|');
    QString debugString = "|";
    int index = 1;
    for (QByteArray byte : listOfBytes) {
        debugString += QString::number(index++) += QString(":") += QString::number(byte.toShort()) += "|";
    }

    statusBar->showMessage(debugString);
}

void ControlViewModel::collectControlData()
{
    controlData.clear();
    controlData[MAIN_CONTROL] = static_cast<char>(128);

    controlData[TRAIN_CONTROL_1] = static_cast<char>(trains.value(ControlTrain::TRAIN_1)->getTrainSpeed());
    controlData[TRAIN_CONTROL_2] = static_cast<char>(trains.value(ControlTrain::TRAIN_2)->getTrainSpeed());
    controlData[TRAIN_CONTROL_3] = static_cast<char>(trains.value(ControlTrain::TRAIN_3)->getTrainSpeed());
    controlData[TRAIN_CONTROL_4] = static_cast<char>(trains.value(ControlTrain::TRAIN_4)->getTrainSpeed());
    controlData[TRAIN_CONTROL_5] = static_cast<char>(trains.value(ControlTrain::TRAIN_5)->getTrainSpeed());
    controlData[TRAIN_CONTROL_6] = static_cast<char>(trains.value(ControlTrain::TRAIN_6)->getTrainSpeed());
    controlData[TRAIN_CONTROL_7] = static_cast<char>(trains.value(ControlTrain::TRAIN_7)->getTrainSpeed());
    controlData[TRAIN_CONTROL_8] = static_cast<char>(trains.value(ControlTrain::TRAIN_8)->getTrainSpeed());

    controlData[SWITCH_CONTROL_1] = static_cast<char>( switches.value(ControlSwitch::SWITCH_1)->getSwitchToggle() +
                                                   2 * switches.value(ControlSwitch::SWITCH_2)->getSwitchToggle() +
                                                   4 * switches.value(ControlSwitch::SWITCH_3)->getSwitchToggle() +
                                                   8 * switches.value(ControlSwitch::SWITCH_4)->getSwitchToggle() +
                                                  16 * switches.value(ControlSwitch::SWITCH_5)->getSwitchToggle() +
                                                  32 * switches.value(ControlSwitch::SWITCH_6)->getSwitchToggle() +
                                                  64 * switches.value(ControlSwitch::SWITCH_7)->getSwitchToggle() +
                                                 128 * switches.value(ControlSwitch::SWITCH_8)->getSwitchToggle() );
    controlData[SWITCH_CONTROL_2] = static_cast<char>( switches.value(ControlSwitch::SWITCH_9)->getSwitchToggle() );

    controlData[LIGHT_CONTROL_1] = static_cast<char>( lights.value( ControlLight::LIGHT_1)->getLightToggle() +
                                                  2 * !lights.value(ControlLight::LIGHT_1)->getLightToggle() +
                                                  4 * lights.value( ControlLight::LIGHT_2)->getLightToggle() +
                                                  8 * !lights.value(ControlLight::LIGHT_2)->getLightToggle() +
                                                 16 * lights.value( ControlLight::LIGHT_3)->getLightToggle() +
                                                 32 * !lights.value(ControlLight::LIGHT_3)->getLightToggle() +
                                                 64 * lights.value( ControlLight::LIGHT_4)->getLightToggle() +
                                                128 * !lights.value(ControlLight::LIGHT_4)->getLightToggle() );
    controlData[LIGHT_CONTROL_2] = static_cast<char>( lights.value( ControlLight::LIGHT_5)->getLightToggle() +
                                                  2 * !lights.value(ControlLight::LIGHT_5)->getLightToggle() +
                                                  4 * lights.value( ControlLight::LIGHT_6)->getLightToggle() +
                                                  8 * !lights.value(ControlLight::LIGHT_6)->getLightToggle() );
//                                                 16 * lights.value( ControlLight::LIGHT_07)->getLightToggle() +
//                                                 32 * !lights.value(ControlLight::LIGHT_07)->getLightToggle() +
//                                                 64 * lights.value( ControlLight::LIGHT_08)->getLightToggle() +
//                                                128 * !lights.value(ControlLight::LIGHT_08)->getLightToggle() );
    controlData[LIGHT_CONTROL_3] = static_cast<char>( lights.value( ControlLight::LIGHT_7)->getLightToggle() +
                                                  2 * !lights.value(ControlLight::LIGHT_7)->getLightToggle() +
                                                  4 * lights.value( ControlLight::LIGHT_8)->getLightToggle() +
                                                  8 * !lights.value(ControlLight::LIGHT_8)->getLightToggle() +
                                                 16 * lights.value( ControlLight::LIGHT_9)->getLightToggle() +
                                                 32 * !lights.value(ControlLight::LIGHT_9)->getLightToggle() +
                                                 64 * lights.value( ControlLight::LIGHT_10)->getLightToggle() +
                                                128 * !lights.value(ControlLight::LIGHT_10)->getLightToggle() );
    controlData[LIGHT_CONTROL_4] = static_cast<char>( lights.value( ControlLight::LIGHT_11)->getLightToggle() +
                                                  2 * !lights.value(ControlLight::LIGHT_11)->getLightToggle() +
                                                  4 * lights.value( ControlLight::LIGHT_12)->getLightToggle() +
                                                  8 * !lights.value(ControlLight::LIGHT_12)->getLightToggle() +
                                                 16 * lights.value( ControlLight::LIGHT_13)->getLightToggle() +
                                                 32 * !lights.value(ControlLight::LIGHT_13)->getLightToggle() );
//                                                 64 * lights.value( ControlLight::LIGHT_16)->getLightToggle() +
//                                                128 * !lights.value(ControlLight::LIGHT_16)->getLightToggle() );
    controlData[LIGHT_CONTROL_5] = static_cast<char>( lights.value( ControlLight::LIGHT_14)->getLightToggle() +
                                                  2 * !lights.value(ControlLight::LIGHT_14)->getLightToggle() +
                                                  4 * lights.value( ControlLight::LIGHT_15)->getLightToggle() +
                                                  8 * !lights.value(ControlLight::LIGHT_15)->getLightToggle() +
                                                 16 * lights.value( ControlLight::LIGHT_16)->getLightToggle() +
                                                 32 * !lights.value(ControlLight::LIGHT_16)->getLightToggle() +
                                                 64 * lights.value( ControlLight::LIGHT_17)->getLightToggle() +
                                                128 * !lights.value(ControlLight::LIGHT_17)->getLightToggle() );
    controlData[LIGHT_CONTROL_6] = static_cast<char>( lights.value( ControlLight::LIGHT_18)->getLightToggle() +
                                                  2 * !lights.value(ControlLight::LIGHT_18)->getLightToggle() +
                                                  4 * lights.value( ControlLight::LIGHT_19)->getLightToggle() +
                                                  8 * !lights.value(ControlLight::LIGHT_19)->getLightToggle() +
                                                 16 * lights.value( ControlLight::LIGHT_20)->getLightToggle() +
                                                 32 * !lights.value(ControlLight::LIGHT_20)->getLightToggle() +
                                                 64 * lights.value( ControlLight::LIGHT_21)->getLightToggle() +
                                                128 * !lights.value(ControlLight::LIGHT_21)->getLightToggle() );
    controlData[LIGHT_CONTROL_7] = 0;

    qDebug() << controlData.toHex('|');
}

void ControlViewModel::runTriggered()
{
    if (!serialPort) {
        QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
        for (QSerialPortInfo port : ports) {
            if (port.serialNumber() == "NXP-77") {
                serialPort = new QSerialPort(port);
                if (serialPort->open(QIODevice::ReadWrite)) {
                    serialPort->setBaudRate(serialPort->Baud115200, serialPort->AllDirections);
                    serialPort->clear();
                    statusBar->showMessage(tr("Device: %1").arg(port.serialNumber()));

                    dataProvider->setSerialPort(serialPort);
                    dataProvider->start(dataProvider->HighPriority);
                } else {
                    statusBar->showMessage(tr("Can't open %1, error code %2") .arg(serialPort->portName()).arg(serialPort->error()));
                }
                return;
            }
        }
        statusBar->showMessage("No Device");
        serialPort = nullptr;
        dataProvider->terminate();
    }
}

void ControlViewModel::aiEnabled(bool state)
{
    aiIsEnabled = state;
}

void ControlViewModel::settingsTriggered()
{
    /// NOW THIS METOHD IS FOR TESTING

    QByteArray byteArray;
    bool change = false;
    for (int i = 0; i < 32; i++) {
        if (change) {
            byteArray[i] = 1;
            change = !change;
        } else {
            byteArray[i] = 0;
            change = !change;
        }
    }

    prepareCollectedData(byteArray);
//    collectControlData();
}

void ControlViewModel::stopAllChannels()
{
    QMapIterator<int, ControlSlider*> sliderList(sliders);
    while (sliderList.hasNext()) {
        sliderList.next();
        sliderList.value()->setValue(0);
    }
}

void ControlViewModel::controlObjectClicked(ControlObject::ObjectType objectType, int objectID)
{
    switch (objectType) {
    case ControlObject::OBJECT_LIGHT:
        lights.value(objectID)->toggle();
        break;
    case ControlObject::OBJECT_SWITCH:
        switches.value(objectID)->toggle();
        break;
    default:
        break;
    }
}

void ControlViewModel::dataFromSerialDeviceCollected(QByteArray readData)
{
    prepareCollectedData(readData);
    if (aiIsEnabled)
        qDebug() << "aiControl()";
    else
        qDebug() << "manualControl()";
    collectControlData();
}
