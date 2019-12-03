#include "ControlProvider.h"
#include <QDebug>

ControlProvider::ControlProvider()
{
    createObjects();
    createObjectsData();
    createConnections();
    mainWindow.show();
}

void ControlProvider::createObjects()
{
    viewModel = new ControlViewModel;
    debugPanel = new ControlDebugPanel();
    view = mainWindow.getControlView();
    scene = new ControlScene();
    buttonStopAll = mainWindow.getButtonStopAll();
    actionRun = mainWindow.getActionRun();
    actionEnableAI = mainWindow.getActionEnableAI();
    actionEpplicationSettings = mainWindow.getActionApplicationSettings();
    actionDebugPanel = mainWindow.getActionDebugPanel();
    toolBar = mainWindow.getToolBar();
    statusBar = mainWindow.getStatusBar();
    buttons = mainWindow.getButtons();
    sliders = mainWindow.getSliders();
    labels = mainWindow.getLabels();
}

void ControlProvider::createConnections()
{
    connect(buttonStopAll, SIGNAL(clicked()), viewModel, SLOT(stopAllChannels()));
    connect(scene, SIGNAL(controlObjectClicked(ControlObject::ObjectType, int)), viewModel, SLOT(controlObjectClicked(ControlObject::ObjectType, int)));
    connect(actionRun, SIGNAL(toggled(bool)), viewModel, SLOT(runTriggered(bool)));
    connect(actionEnableAI, SIGNAL(toggled(bool)), viewModel, SLOT(aiEnabled(bool)));
    connect(actionEpplicationSettings, SIGNAL(triggered()), viewModel, SLOT(settingsTriggered()));
    connect(actionDebugPanel, SIGNAL(triggered()), debugPanel, SLOT(show()));

}

void ControlProvider::createObjectsData()
{
//    scene->setBackgroundBrush(QColor("#539920"));
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
    viewModel->setSliders(sliders);
    viewModel->setLights(lights);
    viewModel->setSwitches(switches);
    viewModel->setRails(rails);
    viewModel->setTrains(trains);
    viewModel->setStatusBar(statusBar);
    viewModel->setSensors(sensors);
    debugPanel->setSensors(sensors);
    debugPanel->setRails(rails);
    debugPanel->setTrains(trains);
    statusBar->showMessage("No Device");
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
        sliderList.value()->setControlValue();
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

    QMapIterator<int, ControlRail*> railList(rails);
    while (railList.hasNext()) {
        railList.next();
        connect(railList.value(), SIGNAL(objectChanged()), scene, SLOT(update()));
        scene->addItem(railList.value());
    }
    scene->addItem(new QGraphicsPixmapItem(ControlRail::getResource(ControlRail::RAIL_SECTION_11)));
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
}

void ControlProvider::prepareSensors()
{
    sensors.insert(ControlSensor::SENSOR_1, new ControlSensor(ControlSensor::SENSOR_1, ControlSensor::TAIL_ENTRY_SENSOR));
    sensors.insert(ControlSensor::SENSOR_2, new ControlSensor(ControlSensor::SENSOR_2, ControlSensor::TAIL_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_3, new ControlSensor(ControlSensor::SENSOR_3, ControlSensor::HEAD_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_4, new ControlSensor(ControlSensor::SENSOR_4, ControlSensor::HEAD_ENTRY_SENSOR));
    sensors.insert(ControlSensor::SENSOR_5, new ControlSensor(ControlSensor::SENSOR_5, ControlSensor::TAIL_ENTRY_SENSOR));
    sensors.insert(ControlSensor::SENSOR_6, new ControlSensor(ControlSensor::SENSOR_6, ControlSensor::TAIL_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_7, new ControlSensor(ControlSensor::SENSOR_7, ControlSensor::HEAD_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_8, new ControlSensor(ControlSensor::SENSOR_8, ControlSensor::HEAD_ENTRY_SENSOR));
    sensors.insert(ControlSensor::SENSOR_9, new ControlSensor(ControlSensor::SENSOR_9, ControlSensor::TAIL_ENTRY_SENSOR));
    sensors.insert(ControlSensor::SENSOR_10, new ControlSensor(ControlSensor::SENSOR_10, ControlSensor::TAIL_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_11, new ControlSensor(ControlSensor::SENSOR_11, ControlSensor::HEAD_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_12, new ControlSensor(ControlSensor::SENSOR_12, ControlSensor::HEAD_ENTRY_SENSOR));
    sensors.insert(ControlSensor::SENSOR_13, new ControlSensor(ControlSensor::SENSOR_13, ControlSensor::TAIL_ENTRY_SENSOR));
    sensors.insert(ControlSensor::SENSOR_14, new ControlSensor(ControlSensor::SENSOR_14, ControlSensor::TAIL_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_15, new ControlSensor(ControlSensor::SENSOR_15, ControlSensor::HEAD_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_16, new ControlSensor(ControlSensor::SENSOR_16, ControlSensor::HEAD_ENTRY_SENSOR));
    sensors.insert(ControlSensor::SENSOR_17, new ControlSensor(ControlSensor::SENSOR_17, ControlSensor::TAIL_ENTRY_SENSOR));
    sensors.insert(ControlSensor::SENSOR_18, new ControlSensor(ControlSensor::SENSOR_18, ControlSensor::TAIL_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_19, new ControlSensor(ControlSensor::SENSOR_19, ControlSensor::HEAD_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_20, new ControlSensor(ControlSensor::SENSOR_20, ControlSensor::HEAD_ENTRY_SENSOR));
    sensors.insert(ControlSensor::SENSOR_21, new ControlSensor(ControlSensor::SENSOR_21, ControlSensor::TAIL_ENTRY_SENSOR));
    sensors.insert(ControlSensor::SENSOR_22, new ControlSensor(ControlSensor::SENSOR_22, ControlSensor::TAIL_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_23, new ControlSensor(ControlSensor::SENSOR_23, ControlSensor::HEAD_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_24, new ControlSensor(ControlSensor::SENSOR_24, ControlSensor::HEAD_ENTRY_SENSOR));
    sensors.insert(ControlSensor::SENSOR_25, new ControlSensor(ControlSensor::SENSOR_25, ControlSensor::TAIL_ENTRY_SENSOR));
    sensors.insert(ControlSensor::SENSOR_26, new ControlSensor(ControlSensor::SENSOR_26, ControlSensor::TAIL_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_27, new ControlSensor(ControlSensor::SENSOR_27, ControlSensor::HEAD_STOP_SENSOR));
    sensors.insert(ControlSensor::SENSOR_28, new ControlSensor(ControlSensor::SENSOR_28, ControlSensor::HEAD_ENTRY_SENSOR));

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
