#include "ControlViewModel.h"
#include <QDir>
#include <QTimer> //debug timer, delete after debug

ControlViewModel::ControlViewModel(QMainWindow *mainWindow, QObject *parent) : QObject(parent)
{
    dataProvider = new ControlDataProvider();
    connect(dataProvider, SIGNAL(dataFromSenderReady(QByteArray)), this, SLOT(dataFromSenderReady(QByteArray)));
    connect(dataProvider, SIGNAL(receiverReady()), this, SLOT(collectDataToReceiver()));

    lastTrainPosition = new QMessageBox(mainWindow);
    lastTrainPosition->setText("Load last train position?");
    lastTrainPosition->setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    lastTrainPosition->setIcon(QMessageBox::Question);
    lastTrainPosition->setDefaultButton(QMessageBox::Yes);
}

ControlViewModel::~ControlViewModel()
{
    if (receiver)
        receiver->disconnect(dataProvider, SIGNAL(readyRead()));
    if (sender)
        receiver->disconnect(dataProvider, SIGNAL(readyRead()));
    QMapIterator<int, ControlTrain*> trainList(trains);
    while (trainList.hasNext()) {
        trainList.next();
        trainList.value()->setTrainSpeed(ControlTrain::SPEED_BREAKE);
    }
    collectDataToReceiver();
    saveLastTrainPosition();
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

void ControlViewModel::setSensors(QMap<int, ControlSensor *> sensors)
{
    this->sensors = sensors;
}

void ControlViewModel::setStatusBar(QStatusBar *statusBar)
{
    this->statusBar = statusBar;
}

void ControlViewModel::setCollectedData(QByteArray byteArray)
{
    sensors.value(ControlSensor::SENSOR_1)->setState(byteArray.at(10));
    sensors.value(ControlSensor::SENSOR_2)->setState(byteArray.at(11));
    sensors.value(ControlSensor::SENSOR_3)->setState(byteArray.at(12));
    sensors.value(ControlSensor::SENSOR_4)->setState(byteArray.at(13));
    sensors.value(ControlSensor::SENSOR_5)->setState(byteArray.at(3));
    sensors.value(ControlSensor::SENSOR_6)->setState(byteArray.at(15));
    sensors.value(ControlSensor::SENSOR_7)->setState(byteArray.at(0));
    sensors.value(ControlSensor::SENSOR_8)->setState(byteArray.at(5));
    sensors.value(ControlSensor::SENSOR_9)->setState(byteArray.at(14));
    sensors.value(ControlSensor::SENSOR_10)->setState(byteArray.at(2));
    sensors.value(ControlSensor::SENSOR_11)->setState(byteArray.at(1));
    sensors.value(ControlSensor::SENSOR_12)->setState(byteArray.at(4));

    sensors.value(ControlSensor::SENSOR_13)->setState(byteArray.at(16));
    sensors.value(ControlSensor::SENSOR_14)->setState(byteArray.at(17));
    sensors.value(ControlSensor::SENSOR_15)->setState(byteArray.at(18));
    sensors.value(ControlSensor::SENSOR_16)->setState(byteArray.at(19));
    sensors.value(ControlSensor::SENSOR_17)->setState(byteArray.at(20));
    sensors.value(ControlSensor::SENSOR_18)->setState(byteArray.at(21));
    sensors.value(ControlSensor::SENSOR_19)->setState(byteArray.at(22));
    sensors.value(ControlSensor::SENSOR_20)->setState(byteArray.at(23));

    sensors.value(ControlSensor::SENSOR_21)->setState(byteArray.at(31));
    sensors.value(ControlSensor::SENSOR_22)->setState(byteArray.at(30));
    sensors.value(ControlSensor::SENSOR_23)->setState(byteArray.at(28));
    sensors.value(ControlSensor::SENSOR_24)->setState(byteArray.at(29));
    sensors.value(ControlSensor::SENSOR_25)->setState(byteArray.at(26));
    sensors.value(ControlSensor::SENSOR_26)->setState(byteArray.at(27));
    sensors.value(ControlSensor::SENSOR_27)->setState(byteArray.at(25));
    sensors.value(ControlSensor::SENSOR_28)->setState(byteArray.at(24));
}

void ControlViewModel::setAI(ControlAiViewModel *ai)
{
    this->ai = ai;
}

void ControlViewModel::loadLastTrainPosition()
{
    if (QFileInfo::exists(fileName)) {
        if (lastTrainPosition->exec() == QMessageBox::Yes) {
            QFile file(fileName);
            if (file.open(QIODevice::ReadOnly)) {
                QDataStream in(&file);
                int railID;
                int trainID;

                while (!in.atEnd()) {
                    in >> railID;
                    in >> trainID;

                    rails.value(railID)->setTrain(trains.value(trainID));
                    rails.value(railID)->setReservation(true);
                }
                file.close();
            }
        }
    }
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
                                                   2 * !switches.value(ControlSwitch::SWITCH_3)->getSwitchToggle() +
                                                   4 * switches.value(ControlSwitch::SWITCH_4)->getSwitchToggle() +
                                                   8 * !switches.value(ControlSwitch::SWITCH_2)->getSwitchToggle() +
                                                  16 * switches.value(ControlSwitch::SWITCH_5)->getSwitchToggle() +
                                                  32 * !switches.value(ControlSwitch::SWITCH_9)->getSwitchToggle() +
                                                  64 * !switches.value(ControlSwitch::SWITCH_6)->getSwitchToggle() +
                                                 128 * switches.value(ControlSwitch::SWITCH_7)->getSwitchToggle() );
    controlData[SWITCH_CONTROL_2] = static_cast<char>( switches.value(ControlSwitch::SWITCH_8)->getSwitchToggle() );

    controlData[LIGHT_CONTROL_1] = static_cast<char>( lights.value( ControlLight::LIGHT_17)->getLightToggle() +
                                                  2 * !lights.value( ControlLight::LIGHT_17)->getLightToggle() +
                                                  4 * lights.value( ControlLight::LIGHT_15)->getLightToggle() +
                                                  8 * !lights.value( ControlLight::LIGHT_15)->getLightToggle() +
                                                 16 * lights.value( ControlLight::LIGHT_14)->getLightToggle() +
                                                 32 * !lights.value( ControlLight::LIGHT_14)->getLightToggle() +
                                                 64 * 0 +
                                                128 * 0 );
    controlData[LIGHT_CONTROL_2] = static_cast<char>( lights.value( ControlLight::LIGHT_10)->getLightToggle() +
                                                  2 * !lights.value( ControlLight::LIGHT_10)->getLightToggle() +
                                                  4 * lights.value( ControlLight::LIGHT_12)->getLightToggle() +
                                                  8 * !lights.value( ControlLight::LIGHT_12)->getLightToggle() +
                                                 16 * lights.value( ControlLight::LIGHT_13)->getLightToggle() +
                                                 32 * !lights.value( ControlLight::LIGHT_13)->getLightToggle() +
                                                 64 * 0 +
                                                128 * 0 );

    controlData[LIGHT_CONTROL_3] = static_cast<char>( lights.value( ControlLight::LIGHT_20)->getLightToggle() +
                                                  2 * !lights.value( ControlLight::LIGHT_20)->getLightToggle() +
                                                  4 * lights.value( ControlLight::LIGHT_18)->getLightToggle() +
                                                  8 * !lights.value( ControlLight::LIGHT_18)->getLightToggle() +
                                                 16 * lights.value( ControlLight::LIGHT_16)->getLightToggle() +
                                                 32 * !lights.value( ControlLight::LIGHT_16)->getLightToggle() +
                                                 64 * lights.value( ControlLight::LIGHT_19)->getLightToggle() +
                                                128 * !lights.value( ControlLight::LIGHT_19)->getLightToggle() );
    controlData[LIGHT_CONTROL_4] = static_cast<char>( lights.value( ControlLight::LIGHT_8)->getLightToggle() +
                                                  2 * !lights.value( ControlLight::LIGHT_8)->getLightToggle() +
                                                  4 * lights.value( ControlLight::LIGHT_9)->getLightToggle() +
                                                  8 * !lights.value( ControlLight::LIGHT_9)->getLightToggle() +
                                                 16 * lights.value( ControlLight::LIGHT_11)->getLightToggle() +
                                                 32 * !lights.value( ControlLight::LIGHT_11)->getLightToggle() +
                                                 64 * 0 +
                                                128 * 0 );

    controlData[LIGHT_CONTROL_5] = static_cast<char>( lights.value( ControlLight::LIGHT_21)->getLightToggle() +
                                                  2 * !lights.value( ControlLight::LIGHT_21)->getLightToggle() +
                                                  4 * lights.value( ControlLight::LIGHT_1)->getLightToggle() +
                                                  8 * !lights.value( ControlLight::LIGHT_1)->getLightToggle() +
                                                 16 * lights.value( ControlLight::LIGHT_3)->getLightToggle() +
                                                 32 * !lights.value( ControlLight::LIGHT_3)->getLightToggle() +
                                                 64 * lights.value( ControlLight::LIGHT_5)->getLightToggle() +
                                                128 * !lights.value( ControlLight::LIGHT_5)->getLightToggle() );
    controlData[LIGHT_CONTROL_6] = static_cast<char>( lights.value( ControlLight::LIGHT_6)->getLightToggle() +
                                                  2 * !lights.value( ControlLight::LIGHT_6)->getLightToggle() +
                                                  4 * lights.value( ControlLight::LIGHT_4)->getLightToggle() +
                                                  8 * !lights.value( ControlLight::LIGHT_4)->getLightToggle() +
                                                 16 * lights.value( ControlLight::LIGHT_2)->getLightToggle() +
                                                 32 * !lights.value( ControlLight::LIGHT_2)->getLightToggle() +
                                                 64 * lights.value( ControlLight::LIGHT_7)->getLightToggle() +
                                                128 * !lights.value( ControlLight::LIGHT_7)->getLightToggle() );
    controlData[LIGHT_CONTROL_7] = 0;
}

void ControlViewModel::setSerialPortInformation()
{
    bool senderStatus = false;
    bool receiverStatus = false;

    QList<QString> deviceList;
    for (QSerialPortInfo port : QSerialPortInfo::availablePorts()) {
        if (port.serialNumber() == "NXP-77") {
            if (port.vendorIdentifier() == senderID) {
                senderStatus = true;
            } else if (port.vendorIdentifier() == receiverID) {
                receiverStatus = true;
            }
        }
    }

    statusBar->showMessage(QString("Sender: ") + QString(senderStatus ? "(disconnected)" : "(empty)") + " " + QString("Receiver: ") + QString(receiverStatus ? "(disconnected)" : "(empty)"));
}

void ControlViewModel::saveLastTrainPosition()
{
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);

    QMapIterator<int, ControlRail*> railList(rails);
    while (railList.hasNext()) {
        railList.next();
        if (railList.value()->getTrain() != nullptr) {
            out << int(railList.key());
            out << int(railList.value()->getTrain()->getTrainID());
        }
    }
}

void ControlViewModel::runTriggered()
{
    if (sender && receiver) {
        return;
    } else {
        if (sender) {
            sender->close();
            delete sender;
        }
        if (receiver) {
            receiver->close();
            delete receiver;
        }
    }

    bool senderStatus = false;
    bool receiverStatus = false;

    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    for (QSerialPortInfo port : ports) {
        if (port.serialNumber() == "NXP-77") {
            if (port.vendorIdentifier() == senderID) {
                if (sender != nullptr) {
                    sender = new QSerialPort(port);
                    if (sender->open(QIODevice::ReadWrite)) {
                        sender->setBaudRate(sender->Baud115200, sender->AllDirections);
                        sender->clear();
                        dataProvider->setSender(sender);
                        senderStatus = true;
                    }
                }
            } else if (port.vendorIdentifier() == receiverID) {
                if (receiver != nullptr) {
                    receiver = new QSerialPort(port);
                    if (receiver->open(QIODevice::ReadWrite)) {
                        receiver->setBaudRate(receiver->Baud115200, receiver->AllDirections);
                        receiver->clear();
                        dataProvider->setReceiver(receiver);
                        receiverStatus = true;
                        collectDataToReceiver();
                    }
                }
            }
        }

        if (sender && receiver)
            statusBar->showMessage(QString("Sender: ") + QString(senderStatus ? "(connected)" : "(disconnected)") + " " + QString("Receiver: ") + QString(receiverStatus ? "(connected)" : "(disconnected)"));
        else
            statusBar->showMessage(QString("Sender: ") + QString(senderStatus ? "(disconnected)" : "(empty)") + " " + QString("Receiver: ") + QString(receiverStatus ? "(disconnected)" : "(empty)"));
    }
}

void ControlViewModel::aiEnabled(bool state)
{
    aiIsEnabled = state;
    ai->setAiEnabled(state);
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

void ControlViewModel::dataFromSenderReady(QByteArray readData)
{
    setCollectedData(readData);
    if (aiIsEnabled)
        ai->run();
}

void ControlViewModel::collectDataToReceiver()
{
    collectControlData();
    dataProvider->sendDataToReceiver(controlData);
}
