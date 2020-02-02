#include "MainViewModel.h"

MainViewModel::MainViewModel(QMainWindow *mainWindow, QObject *parent) : QObject(parent)
{
    setDataController();

    loadTrains = new QMessageBox(mainWindow);
    resetTrains = new QMessageBox(mainWindow);
}

MainViewModel::~MainViewModel()
{
    delete dataController;
}

void MainViewModel::setSliders(QMap<int, SliderModel *> sliders)
{
    this->sliders = sliders;
}

void MainViewModel::setLights(QMap<int, LightModel *> lights)
{
    this->lights = lights;
}

void MainViewModel::setSwitches(QMap<int, SwitchModel *> switches)
{
    this->switches = switches;
}

void MainViewModel::setRails(QMap<int, RailModel *> rails)
{
    this->rails = rails;
}

void MainViewModel::setTrains(QMap<int, TrainModel *> trains)
{
    this->trains = trains;
}

void MainViewModel::setSensors(QMap<int, SensorModel *> sensors)
{
    this->sensors = sensors;
}

void MainViewModel::setStatusBar(QStatusBar *statusBar)
{
    this->statusBar = statusBar;
}

void MainViewModel::setTrafficManager(TrafficManagerViewModel *trafficManager)
{
    this->trafficManager = trafficManager;
}

void MainViewModel::setSensorsData(QByteArray byteArray)
{
    sensors.value(SensorModel::SENSOR_1)->setState(byteArray.at(13));
    sensors.value(SensorModel::SENSOR_4)->setState(byteArray.at(10));
    sensors.value(SensorModel::SENSOR_5)->setState(byteArray.at(4));
    sensors.value(SensorModel::SENSOR_8)->setState(byteArray.at(2));
    sensors.value(SensorModel::SENSOR_9)->setState(byteArray.at(9));
    sensors.value(SensorModel::SENSOR_12)->setState(byteArray.at(3));
    sensors.value(SensorModel::SENSOR_13)->setState(byteArray.at(24));
    sensors.value(SensorModel::SENSOR_16)->setState(byteArray.at(27));
    sensors.value(SensorModel::SENSOR_17)->setState(byteArray.at(28));
    sensors.value(SensorModel::SENSOR_20)->setState(byteArray.at(31));
    sensors.value(SensorModel::SENSOR_21)->setState(byteArray.at(16));
    sensors.value(SensorModel::SENSOR_24)->setState(byteArray.at(18));
    sensors.value(SensorModel::SENSOR_25)->setState(byteArray.at(21));
    sensors.value(SensorModel::SENSOR_28)->setState(byteArray.at(23));


    sensors.value(SensorModel::SENSOR_2)->setState(byteArray.at(12));
    sensors.value(SensorModel::SENSOR_3)->setState(byteArray.at(11));
    sensors.value(SensorModel::SENSOR_6)->setState(byteArray.at(8));
    sensors.value(SensorModel::SENSOR_7)->setState(byteArray.at(7));
    sensors.value(SensorModel::SENSOR_10)->setState(byteArray.at(5));
    sensors.value(SensorModel::SENSOR_11)->setState(byteArray.at(6));
    sensors.value(SensorModel::SENSOR_14)->setState(byteArray.at(25));
    sensors.value(SensorModel::SENSOR_15)->setState(byteArray.at(26));
    sensors.value(SensorModel::SENSOR_18)->setState(byteArray.at(29));
    sensors.value(SensorModel::SENSOR_19)->setState(byteArray.at(30));
    sensors.value(SensorModel::SENSOR_22)->setState(byteArray.at(17));
    sensors.value(SensorModel::SENSOR_23)->setState(byteArray.at(19));
    sensors.value(SensorModel::SENSOR_26)->setState(byteArray.at(20));
    sensors.value(SensorModel::SENSOR_27)->setState(byteArray.at(22));
}

void MainViewModel::collectControlData()
{
    controlData.clear();

    controlData[TRAIN_CONTROL_1] = static_cast<char>(trains.value(TrainModel::TRAIN_1)->getTrainControl());
    controlData[TRAIN_CONTROL_2] = static_cast<char>(trains.value(TrainModel::TRAIN_2)->getTrainControl());
    controlData[TRAIN_CONTROL_3] = static_cast<char>(trains.value(TrainModel::TRAIN_3)->getTrainControl());
    controlData[TRAIN_CONTROL_4] = static_cast<char>(trains.value(TrainModel::TRAIN_4)->getTrainControl());
    controlData[TRAIN_CONTROL_5] = static_cast<char>(trains.value(TrainModel::TRAIN_5)->getTrainControl());
    controlData[TRAIN_CONTROL_6] = static_cast<char>(trains.value(TrainModel::TRAIN_6)->getTrainControl());
    controlData[TRAIN_CONTROL_7] = static_cast<char>(trains.value(TrainModel::TRAIN_7)->getTrainControl());
    controlData[TRAIN_CONTROL_8] = static_cast<char>(trains.value(TrainModel::TRAIN_8)->getTrainControl());

    controlData[SWITCH_CONTROL_1] = static_cast<char>( switches.value(SwitchModel::SWITCH_1)->getSwitchState() +
                                                   2 * !switches.value(SwitchModel::SWITCH_3)->getSwitchState() +
                                                   4 * switches.value(SwitchModel::SWITCH_4)->getSwitchState() +
                                                   8 * !switches.value(SwitchModel::SWITCH_2)->getSwitchState() +
                                                  16 * switches.value(SwitchModel::SWITCH_5)->getSwitchState() +
                                                  32 * !switches.value(SwitchModel::SWITCH_9)->getSwitchState() +
                                                  64 * !switches.value(SwitchModel::SWITCH_6)->getSwitchState() +
                                                 128 * switches.value(SwitchModel::SWITCH_7)->getSwitchState() );
    controlData[SWITCH_CONTROL_2] = static_cast<char>( switches.value(SwitchModel::SWITCH_8)->getSwitchState() );

    controlData[LIGHT_CONTROL_1] = static_cast<char>( lights.value( LightModel::LIGHT_17)->getLightState() +
                                                  2 * !lights.value( LightModel::LIGHT_17)->getLightState() +
                                                  4 * lights.value( LightModel::LIGHT_15)->getLightState() +
                                                  8 * !lights.value( LightModel::LIGHT_15)->getLightState() +
                                                 16 * lights.value( LightModel::LIGHT_14)->getLightState() +
                                                 32 * !lights.value( LightModel::LIGHT_14)->getLightState() +
                                                 64 * 0 +
                                                128 * 0 );
    controlData[LIGHT_CONTROL_2] = static_cast<char>( lights.value( LightModel::LIGHT_10)->getLightState() +
                                                  2 * !lights.value( LightModel::LIGHT_10)->getLightState() +
                                                  4 * lights.value( LightModel::LIGHT_12)->getLightState() +
                                                  8 * !lights.value( LightModel::LIGHT_12)->getLightState() +
                                                 16 * lights.value( LightModel::LIGHT_13)->getLightState() +
                                                 32 * !lights.value( LightModel::LIGHT_13)->getLightState() +
                                                 64 * 0 +
                                                128 * 0 );

    controlData[LIGHT_CONTROL_3] = static_cast<char>( lights.value( LightModel::LIGHT_20)->getLightState() +
                                                  2 * !lights.value( LightModel::LIGHT_20)->getLightState() +
                                                  4 * lights.value( LightModel::LIGHT_18)->getLightState() +
                                                  8 * !lights.value( LightModel::LIGHT_18)->getLightState() +
                                                 16 * lights.value( LightModel::LIGHT_16)->getLightState() +
                                                 32 * !lights.value( LightModel::LIGHT_16)->getLightState() +
                                                 64 * lights.value( LightModel::LIGHT_19)->getLightState() +
                                                128 * !lights.value( LightModel::LIGHT_19)->getLightState() );
    controlData[LIGHT_CONTROL_4] = static_cast<char>( lights.value( LightModel::LIGHT_8)->getLightState() +
                                                  2 * !lights.value( LightModel::LIGHT_8)->getLightState() +
                                                  4 * lights.value( LightModel::LIGHT_9)->getLightState() +
                                                  8 * !lights.value( LightModel::LIGHT_9)->getLightState() +
                                                 16 * lights.value( LightModel::LIGHT_11)->getLightState() +
                                                 32 * !lights.value( LightModel::LIGHT_11)->getLightState() +
                                                 64 * 0 +
                                                128 * 0 );

    controlData[LIGHT_CONTROL_5] = static_cast<char>( lights.value( LightModel::LIGHT_21)->getLightState() +
                                                  2 * !lights.value( LightModel::LIGHT_21)->getLightState() +
                                                  4 * lights.value( LightModel::LIGHT_1)->getLightState() +
                                                  8 * !lights.value( LightModel::LIGHT_1)->getLightState() +
                                                 16 * lights.value( LightModel::LIGHT_3)->getLightState() +
                                                 32 * !lights.value( LightModel::LIGHT_3)->getLightState() +
                                                 64 * lights.value( LightModel::LIGHT_5)->getLightState() +
                                                128 * !lights.value( LightModel::LIGHT_5)->getLightState() );
    controlData[LIGHT_CONTROL_6] = static_cast<char>( lights.value( LightModel::LIGHT_6)->getLightState() +
                                                  2 * !lights.value( LightModel::LIGHT_6)->getLightState() +
                                                  4 * lights.value( LightModel::LIGHT_4)->getLightState() +
                                                  8 * !lights.value( LightModel::LIGHT_4)->getLightState() +
                                                 16 * lights.value( LightModel::LIGHT_2)->getLightState() +
                                                 32 * !lights.value( LightModel::LIGHT_2)->getLightState() +
                                                 64 * lights.value( LightModel::LIGHT_7)->getLightState() +
                                                128 * !lights.value( LightModel::LIGHT_7)->getLightState() );

    controlData[TRANSMISSION_CONTROL] = getTransmissionControl();
    lastControlData = controlData;
}

void MainViewModel::setSerialPortInformation()
{
    bool controllerStatus = false;

    for (QSerialPortInfo port : QSerialPortInfo::availablePorts()) {
        if (port.vendorIdentifier() == 8137) {
            controllerStatus = true;
            break;
        }
    }

    statusBar->showMessage(QString("Controller: " + QString(controllerStatus ? "(Disconnected)" : ("none"))));
}

void MainViewModel::loadTrainPosition() //REMAKE
{
    loadTrains->setText("Set current trains position,\n(select highlight rail using mouse)\nTrain 1 -> Train 2 -> Train 3");
    loadTrains->setStandardButtons(QMessageBox::Ok);
    loadTrains->setIcon(QMessageBox::Icon::Information);

    if (QMessageBox::Ok == loadTrains->exec()) {
        for (RailModel *rail : rails) {
            if (rail->getObjectID() == RailModel::RAIL_SECTION_4 || rail->getObjectID() == RailModel::RAIL_SECTION_7 || rail->getObjectID() == RailModel::RAIL_SECTION_10)
                continue;
            rail->graphicsEffect()->setEnabled(true);
        }
        selectionMode = true;
    }
}

char MainViewModel::getTransmissionControl()
{
    if (lastControlData.isEmpty()) {
        return -1;
    }

    char transmissionControl = 0;

    if (lastControlData[LIGHT_CONTROL_1] != controlData[LIGHT_CONTROL_1] || lastControlData[LIGHT_CONTROL_2] != controlData[LIGHT_CONTROL_2])
        transmissionControl |= LIGHT_TRANSMISSION_CONTROL_1;

    if (lastControlData[LIGHT_CONTROL_3] != controlData[LIGHT_CONTROL_3] || lastControlData[LIGHT_CONTROL_4] != controlData[LIGHT_CONTROL_4])
        transmissionControl |= LIGHT_TRANSMISSION_CONTROL_2;

    if (lastControlData[LIGHT_CONTROL_5] != controlData[LIGHT_CONTROL_5] || lastControlData[LIGHT_CONTROL_6] != controlData[LIGHT_CONTROL_6])
        transmissionControl |= LIGHT_TRANSMISSION_CONTROL_3;

    if (lastControlData[SWITCH_CONTROL_1] != controlData[SWITCH_CONTROL_1] || lastControlData[SWITCH_CONTROL_2] != controlData[SWITCH_CONTROL_2])
        transmissionControl |= SWITCH_TRANSMISSION_CONTROL_1;

    return transmissionControl;
}

void MainViewModel::setDataController()
{
    dataController = new DataViewModel();
    connect(dataController, SIGNAL(controllerConnected()), this, SLOT(controllerConnected()));
    connect(dataController, SIGNAL(sensorsData(QByteArray)), this, SLOT(sensorsData(QByteArray)));
}

void MainViewModel::runTriggered()
{
    lastControlData.clear();
    for (QSerialPortInfo port : QSerialPortInfo::availablePorts()) {
        if (port.vendorIdentifier() == 8137) {
            dataController->connectController(port);
            break;
        }
    }
}

void MainViewModel::aiEnabled(bool state)
{
    if (state)
        trafficManager->enable();
    else
        trafficManager->disable();
    trafficManager->run();
}

void MainViewModel::stopAllChannels()
{
    trafficManager->disable();
    for (auto slider : sliders)
        slider->setValue(0);
}

void MainViewModel::controlObjectClicked(ObjectModel::ObjectType objectType, int objectID) //REMAKE
{
    if (selectionMode) {
        if (objectType == ObjectModel::OBJECT_RAIL) {
            if (objectID != RailModel::RAIL_SECTION_4 && objectID != RailModel::RAIL_SECTION_7 && objectID != RailModel::RAIL_SECTION_10) {
                if (rails.value(objectID)->getTrain() == nullptr) {
                    rails.value(objectID)->graphicsEffect()->setEnabled(false);
                    rails.value(objectID)->setReservation(true);
                    rails.value(objectID)->setTrain(trains.value(insertedTrains++));

                    if (insertedTrains == MAX_TRAINS) {
                        selectionMode = false;
                        insertedTrains = 0;
                        for (RailModel *rail : rails) {
                            if (rail->getObjectID() == RailModel::RAIL_SECTION_4 || rail->getObjectID() == RailModel::RAIL_SECTION_7 || rail->getObjectID() == RailModel::RAIL_SECTION_10)
                                continue;
                            rail->graphicsEffect()->setEnabled(false);
                        }
                    }
                }
            }
        }
        return;
    }

    switch (objectType) {
    case ObjectModel::OBJECT_LIGHT:
        lights.value(objectID)->toggle();
        break;
    case ObjectModel::OBJECT_SWITCH:
        switches.value(objectID)->toggle();
        break;
    default:
        break;
    }
}

void MainViewModel::sensorsData(QByteArray data)
{
//    qDebug() << data.toHex('|');
    setSensorsData(data);
    trafficManager->run();
    collectControlData();
    dataController->sendData(controlData);
}

void MainViewModel::resetTrainsTriggered() //REMAKE
{
    if (!selectionMode) {
        loadTrains->setText("Select rails to insert trains from 1 to 3.");
        loadTrains->setStandardButtons(QMessageBox::Button::Ok | QMessageBox::Button::Cancel);
        loadTrains->setIcon(QMessageBox::Icon::Information);

        if (loadTrains->exec() == QMessageBox::Ok) {
            for (auto rail : rails) {
                rail->getTrain(true);
            }
            for (RailModel *rail : rails) {
                if (rail->getObjectID() == RailModel::RAIL_SECTION_4 || rail->getObjectID() == RailModel::RAIL_SECTION_7 || rail->getObjectID() == RailModel::RAIL_SECTION_10)
                    continue;
                rail->graphicsEffect()->setEnabled(true);
            }
            insertedTrains = 0;
            selectionMode = true;
        }
    }
}

void MainViewModel::controllerConnected()
{
    statusBar->showMessage("Controller: (connected)");
    collectControlData();
    dataController->sendData(controlData);
}
