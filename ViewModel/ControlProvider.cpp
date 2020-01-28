#include "ControlProvider.h"
#include <QDebug>

ControlProvider::ControlProvider()
{
    setObjects();
    setObjectsData();
    setConnections();
    mainWindow.show();
}

void ControlProvider::setObjects()
{
    ai = new ControlAiViewModel();
    viewModel = new ControlViewModel(&mainWindow);
    debugger = new ControlDebugger();
    switchMap = new ControlSwitchMap();
    view = mainWindow.getControlView();
    scene = new ControlScene();
    buttonStopAll = mainWindow.getButtonStopAll();
    actionRun = mainWindow.getActionRun();
    actionEnableAI = mainWindow.getActionEnableAI();
    actionDebugPanel = mainWindow.getActionDebugPanel();
    actionReset = mainWindow.getActionReset();
    toolBar = mainWindow.getToolBar();
    statusBar = mainWindow.getStatusBar();
    buttons = mainWindow.getButtons();
    sliders = mainWindow.getSliders();
    labels = mainWindow.getLabels();
}

void ControlProvider::setConnections()
{
    connect(&mainWindow, SIGNAL(closeWindow()), this, SLOT(windowClosed()));
    connect(buttonStopAll, SIGNAL(clicked()), viewModel, SLOT(stopAllChannels()));
    connect(scene, SIGNAL(controlObjectClicked(ControlObject::ObjectType, int)), viewModel, SLOT(controlObjectClicked(ControlObject::ObjectType, int)));
    connect(actionRun, SIGNAL(triggered()), viewModel, SLOT(runTriggered()));
    connect(actionEnableAI, SIGNAL(toggled(bool)), viewModel, SLOT(aiEnabled(bool)));
    connect(actionDebugPanel, SIGNAL(triggered()), debugger, SLOT(show()));
    connect(actionReset, SIGNAL(triggered()), viewModel, SLOT(resetTrainsTriggered()));
}

void ControlProvider::setObjectsData()
{
    scene->setBackgroundBrush(QColor(32, 153, 86));
    view->setScene(scene);
    prepareLabels();
    prepareSliders();
    prepareButtons();
    prepareSwitches();
    toolBar->addSeparator();
    prepareLights();
    prepareRails();
    prepareTrains();
    prepareSensors();
    switchMap->setSwitches(switches); //remove
    switchMap->setRails(rails); //remove
    viewModel->setSliders(sliders);
    viewModel->setLights(lights);
    viewModel->setSwitches(switches);
    viewModel->setRails(rails);
    viewModel->setTrains(trains);
    viewModel->setStatusBar(statusBar);
    viewModel->setSensors(sensors);
    viewModel->setSerialPortInformation();
    ai->setRails(rails);
    ai->setTrains(trains);
    ai->setSwitches(switches);
    ai->setSwitchMap(switchMap);
    ai->setLights(lights);
    debugger->setSensors(sensors);
    debugger->setRails(rails);
    debugger->setTrains(trains);
    debugger->setSwitches(switches);
    debugger->setTimetables(ai->getTimetables());
    debugger->setDebuggerData();
    debugger->setAI(ai);
}

void ControlProvider::prepareButtons()
{
    QMapIterator<int, ControlButton*> buttonList(buttons);
    while (buttonList.hasNext()) {
        buttonList.next();
        buttonList.value()->setID(buttonList.key());
        buttonList.value()->setSlider(sliders.value(buttonList.key()));
    }
}

void ControlProvider::prepareSliders()
{
    QMapIterator<int, ControlSlider*> sliderList(sliders);
    while (sliderList.hasNext()) {
        sliderList.next();
        sliderList.value()->setID(sliderList.key());
        sliderList.value()->setLabel(labels.value(sliderList.key()));
    }
}

void ControlProvider::prepareLabels()
{
    QMapIterator<int, ControlLabel*> labelList(labels);
    while (labelList.hasNext()) {
        labelList.next();
        labelList.value()->setID(labelList.key());
    }
}

void ControlProvider::prepareSwitches()
{
    switches.insert(ControlSwitch::SWITCH_1, new ControlSwitch(ControlSwitch::TYPE_RIGHT, ControlSwitch::SWITCH_1));
    switches.insert(ControlSwitch::SWITCH_2, new ControlSwitch(ControlSwitch::TYPE_LEFT, ControlSwitch::SWITCH_2));
    switches.insert(ControlSwitch::SWITCH_3, new ControlSwitch(ControlSwitch::TYPE_LEFT, ControlSwitch::SWITCH_3));
    switches.insert(ControlSwitch::SWITCH_4, new ControlSwitch(ControlSwitch::TYPE_RIGHT, ControlSwitch::SWITCH_4));
    switches.insert(ControlSwitch::SWITCH_5, new ControlSwitch(ControlSwitch::TYPE_RIGHT, ControlSwitch::SWITCH_5));
    switches.insert(ControlSwitch::SWITCH_6, new ControlSwitch(ControlSwitch::TYPE_LEFT, ControlSwitch::SWITCH_6));
    switches.insert(ControlSwitch::SWITCH_7, new ControlSwitch(ControlSwitch::TYPE_RIGHT, ControlSwitch::SWITCH_7));
    switches.insert(ControlSwitch::SWITCH_8, new ControlSwitch(ControlSwitch::TYPE_RIGHT, ControlSwitch::SWITCH_8));
    switches.insert(ControlSwitch::SWITCH_9, new ControlSwitch(ControlSwitch::TYPE_LEFT, ControlSwitch::SWITCH_9));

    QMapIterator<int, ControlSwitch*> switchList(switches);
    while (switchList.hasNext()) {
        switchList.next();
        switchList.value()->setFlag(QGraphicsItem::ItemIsFocusable);
        switchList.value()->setControlAction(new ControlAction(switchList.value()->getIcon(), ControlAction::ACTION_SWITCH, switchList.value()->getSwitchID(), toolBar));
        connect(switchList.value(), SIGNAL(objectChanged()), scene, SLOT(update()));
        toolBar->addAction(switchList.value()->getControlAction());
        scene->addItem(switchList.value());
    }
}

void ControlProvider::prepareLights()
{
    lights.insert(ControlLight::LIGHT_1, new ControlLight(ControlLight::LIGHT_1, QPointF(10.95, 690), 180));
    lights.insert(ControlLight::LIGHT_2, new ControlLight(ControlLight::LIGHT_2, QPointF(24.09, 258), 0));
    lights.insert(ControlLight::LIGHT_3, new ControlLight(ControlLight::LIGHT_3, QPointF(40.5, 610), 180));
    lights.insert(ControlLight::LIGHT_4, new ControlLight(ControlLight::LIGHT_4, QPointF(53.64, 300), 0));
    lights.insert(ControlLight::LIGHT_5, new ControlLight(ControlLight::LIGHT_5, QPointF(73.2, 590), 180));
    lights.insert(ControlLight::LIGHT_6, new ControlLight(ControlLight::LIGHT_6, QPointF(86.34, 323), 0));
    lights.insert(ControlLight::LIGHT_7, new ControlLight(ControlLight::LIGHT_7, QPointF(10.95, 146), 180));
    lights.insert(ControlLight::LIGHT_8, new ControlLight(ControlLight::LIGHT_8, QPointF(245, 22.99), 90));
    lights.insert(ControlLight::LIGHT_9, new ControlLight(ControlLight::LIGHT_9, QPointF(315, 9.85), -90));
    lights.insert(ControlLight::LIGHT_10, new ControlLight(ControlLight::LIGHT_10, QPointF(797, 22.99), 90));
    lights.insert(ControlLight::LIGHT_11, new ControlLight(ControlLight::LIGHT_11, QPointF(350, 44.89), -90));
    lights.insert(ControlLight::LIGHT_12, new ControlLight(ControlLight::LIGHT_12, QPointF(762, 58.03), 90));
    lights.insert(ControlLight::LIGHT_13, new ControlLight(ControlLight::LIGHT_13, QPointF(867, 9.85), -90));
    lights.insert(ControlLight::LIGHT_14, new ControlLight(ControlLight::LIGHT_14, QPointF(876, 246.35), -90));
    lights.insert(ControlLight::LIGHT_15, new ControlLight(ControlLight::LIGHT_15, QPointF(805.8, 259.49), 90));
    lights.insert(ControlLight::LIGHT_16, new ControlLight(ControlLight::LIGHT_16, QPointF(490.5, 246.35), -90));
    lights.insert(ControlLight::LIGHT_17, new ControlLight(ControlLight::LIGHT_17, QPointF(770.8, 224.43), 90));
    lights.insert(ControlLight::LIGHT_18, new ControlLight(ControlLight::LIGHT_18, QPointF(525.506, 211.31), -90));
    lights.insert(ControlLight::LIGHT_19, new ControlLight(ControlLight::LIGHT_19, QPointF(560.355, 176.28), -90));
    lights.insert(ControlLight::LIGHT_20, new ControlLight(ControlLight::LIGHT_20, QPointF(385.4, 224.43), 90));
    lights.insert(ControlLight::LIGHT_21, new ControlLight(ControlLight::LIGHT_21, QPointF(24.09, 760.95), 0));

    QMapIterator<int, ControlLight*> lightList(lights);
    while (lightList.hasNext()) {
        lightList.next();
        lightList.value()->setFlag(QGraphicsItem::ItemIsFocusable);
        lightList.value()->setControlAction(new ControlAction(lightList.value()->getIcon(), ControlAction::ACTION_LIGHT, lightList.value()->getLightID(), toolBar));
        connect(lightList.value(), SIGNAL(objectChanged()), scene, SLOT(update()));
        toolBar->addAction(lightList.value()->getControlAction());
        scene->addItem(lightList.value());
    }
}

void ControlProvider::prepareRails()
{
    rails.insert(ControlRail::RAIL_SECTION_1, new ControlRail(ControlRail::RAIL_SECTION_1));
    rails.insert(ControlRail::RAIL_SECTION_2, new ControlRail(ControlRail::RAIL_SECTION_2));
    rails.insert(ControlRail::RAIL_SECTION_3, new ControlRail(ControlRail::RAIL_SECTION_3));
    rails.insert(ControlRail::RAIL_SECTION_4, new ControlRail(ControlRail::RAIL_SECTION_4));
    rails.insert(ControlRail::RAIL_SECTION_5, new ControlRail(ControlRail::RAIL_SECTION_5));
    rails.insert(ControlRail::RAIL_SECTION_6, new ControlRail(ControlRail::RAIL_SECTION_6));
    rails.insert(ControlRail::RAIL_SECTION_7, new ControlRail(ControlRail::RAIL_SECTION_7));
    rails.insert(ControlRail::RAIL_SECTION_8, new ControlRail(ControlRail::RAIL_SECTION_8));
    rails.insert(ControlRail::RAIL_SECTION_9, new ControlRail(ControlRail::RAIL_SECTION_9));
    rails.insert(ControlRail::RAIL_SECTION_10, new ControlRail(ControlRail::RAIL_SECTION_10));

    rails.value(ControlRail::RAIL_SECTION_1)->setLastRails(QList<ControlRail*>() << rails.value(ControlRail::RAIL_SECTION_10));
    rails.value(ControlRail::RAIL_SECTION_1)->setNextRails(QList<ControlRail*>() << rails.value(ControlRail::RAIL_SECTION_4));
    rails.value(ControlRail::RAIL_SECTION_2)->setLastRails(QList<ControlRail*>() << rails.value(ControlRail::RAIL_SECTION_10));
    rails.value(ControlRail::RAIL_SECTION_2)->setNextRails(QList<ControlRail*>() << rails.value(ControlRail::RAIL_SECTION_4));
    rails.value(ControlRail::RAIL_SECTION_3)->setLastRails(QList<ControlRail*>() << rails.value(ControlRail::RAIL_SECTION_10));
    rails.value(ControlRail::RAIL_SECTION_3)->setNextRails(QList<ControlRail*>() << rails.value(ControlRail::RAIL_SECTION_4));
    rails.value(ControlRail::RAIL_SECTION_4)->setLastRails(QList<ControlRail*>() << rails.value(ControlRail::RAIL_SECTION_1) << rails.value(ControlRail::RAIL_SECTION_2) << rails.value(ControlRail::RAIL_SECTION_3));
    rails.value(ControlRail::RAIL_SECTION_4)->setNextRails(QList<ControlRail*>() << rails.value(ControlRail::RAIL_SECTION_5) << rails.value(ControlRail::RAIL_SECTION_6));
    rails.value(ControlRail::RAIL_SECTION_5)->setLastRails(QList<ControlRail*>() << rails.value(ControlRail::RAIL_SECTION_4));
    rails.value(ControlRail::RAIL_SECTION_5)->setNextRails(QList<ControlRail*>() << rails.value(ControlRail::RAIL_SECTION_7));
    rails.value(ControlRail::RAIL_SECTION_6)->setLastRails(QList<ControlRail*>() << rails.value(ControlRail::RAIL_SECTION_4));
    rails.value(ControlRail::RAIL_SECTION_6)->setNextRails(QList<ControlRail*>() << rails.value(ControlRail::RAIL_SECTION_7));
    rails.value(ControlRail::RAIL_SECTION_7)->setLastRails(QList<ControlRail*>() << rails.value(ControlRail::RAIL_SECTION_5) << rails.value(ControlRail::RAIL_SECTION_6));
    rails.value(ControlRail::RAIL_SECTION_7)->setNextRails(QList<ControlRail*>() << rails.value(ControlRail::RAIL_SECTION_8) << rails.value(ControlRail::RAIL_SECTION_9));
    rails.value(ControlRail::RAIL_SECTION_8)->setLastRails(QList<ControlRail*>() << rails.value(ControlRail::RAIL_SECTION_7));
    rails.value(ControlRail::RAIL_SECTION_8)->setNextRails(QList<ControlRail*>() << rails.value(ControlRail::RAIL_SECTION_10));
    rails.value(ControlRail::RAIL_SECTION_9)->setLastRails(QList<ControlRail*>() << rails.value(ControlRail::RAIL_SECTION_7));
    rails.value(ControlRail::RAIL_SECTION_9)->setNextRails(QList<ControlRail*>() << rails.value(ControlRail::RAIL_SECTION_10));
    rails.value(ControlRail::RAIL_SECTION_10)->setLastRails(QList<ControlRail*>() << rails.value(ControlRail::RAIL_SECTION_8) << rails.value(ControlRail::RAIL_SECTION_9));
    rails.value(ControlRail::RAIL_SECTION_10)->setNextRails(QList<ControlRail*>() << rails.value(ControlRail::RAIL_SECTION_1) << rails.value(ControlRail::RAIL_SECTION_2) << rails.value(ControlRail::RAIL_SECTION_3));

    rails.value(ControlRail::RAIL_SECTION_1)->setLastLight(lights.value(ControlLight::LIGHT_1));
    rails.value(ControlRail::RAIL_SECTION_1)->setNextLight(lights.value(ControlLight::LIGHT_2));
    rails.value(ControlRail::RAIL_SECTION_2)->setLastLight(lights.value(ControlLight::LIGHT_3));
    rails.value(ControlRail::RAIL_SECTION_2)->setNextLight(lights.value(ControlLight::LIGHT_4));
    rails.value(ControlRail::RAIL_SECTION_3)->setLastLight(lights.value(ControlLight::LIGHT_5));
    rails.value(ControlRail::RAIL_SECTION_3)->setNextLight(lights.value(ControlLight::LIGHT_6));
    rails.value(ControlRail::RAIL_SECTION_4)->setLastLight(lights.value(ControlLight::LIGHT_7));
    rails.value(ControlRail::RAIL_SECTION_4)->setNextLight(lights.value(ControlLight::LIGHT_8));
    rails.value(ControlRail::RAIL_SECTION_5)->setLastLight(lights.value(ControlLight::LIGHT_9));
    rails.value(ControlRail::RAIL_SECTION_5)->setNextLight(lights.value(ControlLight::LIGHT_10));
    rails.value(ControlRail::RAIL_SECTION_6)->setLastLight(lights.value(ControlLight::LIGHT_11));
    rails.value(ControlRail::RAIL_SECTION_6)->setNextLight(lights.value(ControlLight::LIGHT_12));
    rails.value(ControlRail::RAIL_SECTION_7)->setLastLight(lights.value(ControlLight::LIGHT_13));
    rails.value(ControlRail::RAIL_SECTION_7)->setNextLight(lights.value(ControlLight::LIGHT_14));
    rails.value(ControlRail::RAIL_SECTION_8)->setLastLight(lights.value(ControlLight::LIGHT_15));
    rails.value(ControlRail::RAIL_SECTION_8)->setNextLight(lights.value(ControlLight::LIGHT_16));
    rails.value(ControlRail::RAIL_SECTION_9)->setLastLight(lights.value(ControlLight::LIGHT_17));
    rails.value(ControlRail::RAIL_SECTION_9)->setNextLight(lights.value(ControlLight::LIGHT_18));
    rails.value(ControlRail::RAIL_SECTION_10)->setLastLight(lights.value(ControlLight::LIGHT_20));
    rails.value(ControlRail::RAIL_SECTION_10)->setNextLight(lights.value(ControlLight::LIGHT_21));

    for (auto rail : rails) {
        connect(rail, SIGNAL(objectChanged()), scene, SLOT(update()));
        connect(rail, SIGNAL(trainEnters(ControlTrain::TrainID, ControlRail::RailID)), ai, SLOT(trainEnters(ControlTrain::TrainID, ControlRail::RailID)));
        connect(rail, SIGNAL(trainEntered(ControlTrain::TrainID, ControlRail::RailID)), ai, SLOT(trainEntered(ControlTrain::TrainID, ControlRail::RailID)));
        connect(rail, SIGNAL(trainLeaving(ControlTrain::TrainID, ControlRail::RailID)), ai, SLOT(trainLeaving(ControlTrain::TrainID, ControlRail::RailID)));
        connect(rail, SIGNAL(trainLeft(ControlTrain::TrainID, ControlRail::RailID)), ai, SLOT(trainLeft(ControlTrain::TrainID, ControlRail::RailID)));
        connect(rail, SIGNAL(trainActivatedStop(ControlTrain::TrainID, ControlRail::RailID)), ai, SLOT(stopSensorActivated(ControlTrain::TrainID, ControlRail::RailID)));
        scene->addItem(rail);
    }
    scene->addItem(new QGraphicsPixmapItem(ControlRail::getResource(ControlRail::RAIL_SECTION_11)));

    for (ControlRail *rail : rails) {
        if (rail->getObjectID() == ControlRail::RAIL_SECTION_4 || rail->getObjectID() == ControlRail::RAIL_SECTION_7 || rail->getObjectID() == ControlRail::RAIL_SECTION_10)
            continue;
        QGraphicsBlurEffect *effect = new QGraphicsBlurEffect();
        effect->setBlurRadius(1.65);
        rail->setGraphicsEffect(effect);
        rail->graphicsEffect()->setEnabled(false);
        rail->setFlag(QGraphicsItem::ItemIsFocusable);
    }
}

void ControlProvider::prepareTrains()
{
    trains.insert(ControlTrain::TRAIN_1, new ControlTrain(ControlTrain::TRAIN_1, sliders.value(ControlSlider::SLIDER_CHANNEL_1)));
    trains.insert(ControlTrain::TRAIN_2, new ControlTrain(ControlTrain::TRAIN_2, sliders.value(ControlSlider::SLIDER_CHANNEL_2)));
    trains.insert(ControlTrain::TRAIN_3, new ControlTrain(ControlTrain::TRAIN_3, sliders.value(ControlSlider::SLIDER_CHANNEL_3)));
    trains.insert(ControlTrain::TRAIN_4, new ControlTrain(ControlTrain::TRAIN_4, sliders.value(ControlSlider::SLIDER_CHANNEL_4)));
    trains.insert(ControlTrain::TRAIN_5, new ControlTrain(ControlTrain::TRAIN_5, sliders.value(ControlSlider::SLIDER_CHANNEL_5)));
    trains.insert(ControlTrain::TRAIN_6, new ControlTrain(ControlTrain::TRAIN_6, sliders.value(ControlSlider::SLIDER_CHANNEL_6)));
    trains.insert(ControlTrain::TRAIN_7, new ControlTrain(ControlTrain::TRAIN_7, sliders.value(ControlSlider::SLIDER_CHANNEL_7)));
    trains.insert(ControlTrain::TRAIN_8, new ControlTrain(ControlTrain::TRAIN_8, sliders.value(ControlSlider::SLIDER_CHANNEL_8)));

    int priority = 0;
    for (ControlTrain *train : trains) {
        train->setTrainPriority(ControlTrain::TrainPriority(priority++));
    }
}

void ControlProvider::prepareSensors()
{
    sensors.insert(ControlSensor::SENSOR_1, new ControlSensor(ControlSensor::SENSOR_1, ControlSensor::LAST_ENTRY_SENSOR));
    sensors.insert(ControlSensor::SENSOR_2, new ControlSensor(ControlSensor::SENSOR_2, ControlSensor::LAST_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_3, new ControlSensor(ControlSensor::SENSOR_3, ControlSensor::NEXT_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_4, new ControlSensor(ControlSensor::SENSOR_4, ControlSensor::NEXT_ENTRY_SENSOR));
    sensors.insert(ControlSensor::SENSOR_5, new ControlSensor(ControlSensor::SENSOR_5, ControlSensor::LAST_ENTRY_SENSOR));
    sensors.insert(ControlSensor::SENSOR_6, new ControlSensor(ControlSensor::SENSOR_6, ControlSensor::LAST_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_7, new ControlSensor(ControlSensor::SENSOR_7, ControlSensor::NEXT_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_8, new ControlSensor(ControlSensor::SENSOR_8, ControlSensor::NEXT_ENTRY_SENSOR));
    sensors.insert(ControlSensor::SENSOR_9, new ControlSensor(ControlSensor::SENSOR_9, ControlSensor::LAST_ENTRY_SENSOR));
    sensors.insert(ControlSensor::SENSOR_10, new ControlSensor(ControlSensor::SENSOR_10, ControlSensor::LAST_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_11, new ControlSensor(ControlSensor::SENSOR_11, ControlSensor::NEXT_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_12, new ControlSensor(ControlSensor::SENSOR_12, ControlSensor::NEXT_ENTRY_SENSOR));
    sensors.insert(ControlSensor::SENSOR_13, new ControlSensor(ControlSensor::SENSOR_13, ControlSensor::LAST_ENTRY_SENSOR));
    sensors.insert(ControlSensor::SENSOR_14, new ControlSensor(ControlSensor::SENSOR_14, ControlSensor::LAST_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_15, new ControlSensor(ControlSensor::SENSOR_15, ControlSensor::NEXT_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_16, new ControlSensor(ControlSensor::SENSOR_16, ControlSensor::NEXT_ENTRY_SENSOR));
    sensors.insert(ControlSensor::SENSOR_17, new ControlSensor(ControlSensor::SENSOR_17, ControlSensor::LAST_ENTRY_SENSOR));
    sensors.insert(ControlSensor::SENSOR_18, new ControlSensor(ControlSensor::SENSOR_18, ControlSensor::LAST_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_19, new ControlSensor(ControlSensor::SENSOR_19, ControlSensor::NEXT_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_20, new ControlSensor(ControlSensor::SENSOR_20, ControlSensor::NEXT_ENTRY_SENSOR));
    sensors.insert(ControlSensor::SENSOR_21, new ControlSensor(ControlSensor::SENSOR_21, ControlSensor::LAST_ENTRY_SENSOR));
    sensors.insert(ControlSensor::SENSOR_22, new ControlSensor(ControlSensor::SENSOR_22, ControlSensor::LAST_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_23, new ControlSensor(ControlSensor::SENSOR_23, ControlSensor::NEXT_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_24, new ControlSensor(ControlSensor::SENSOR_24, ControlSensor::NEXT_ENTRY_SENSOR));
    sensors.insert(ControlSensor::SENSOR_25, new ControlSensor(ControlSensor::SENSOR_25, ControlSensor::LAST_ENTRY_SENSOR));
    sensors.insert(ControlSensor::SENSOR_26, new ControlSensor(ControlSensor::SENSOR_26, ControlSensor::LAST_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_27, new ControlSensor(ControlSensor::SENSOR_27, ControlSensor::NEXT_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_28, new ControlSensor(ControlSensor::SENSOR_28, ControlSensor::NEXT_ENTRY_SENSOR));

    int sensorID = 0;
    for (ControlRail *rail : rails) {
        if (rail->getObjectID() == ControlRail::RAIL_SECTION_4 || rail->getObjectID() == ControlRail::RAIL_SECTION_7 || rail->getObjectID() == ControlRail::RAIL_SECTION_10)
            continue;
        connect(sensors.value(sensorID++), SIGNAL(signalChanged(ControlSensor::SensorType)), rail, SLOT(sensorChanged(ControlSensor::SensorType)));
        connect(sensors.value(sensorID++), SIGNAL(signalChanged(ControlSensor::SensorType)), rail, SLOT(sensorChanged(ControlSensor::SensorType)));
        connect(sensors.value(sensorID++), SIGNAL(signalChanged(ControlSensor::SensorType)), rail, SLOT(sensorChanged(ControlSensor::SensorType)));
        connect(sensors.value(sensorID++), SIGNAL(signalChanged(ControlSensor::SensorType)), rail, SLOT(sensorChanged(ControlSensor::SensorType)));
    }
}

void ControlProvider::windowClosed()
{
    delete viewModel;
}
