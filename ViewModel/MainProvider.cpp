#include "MainProvider.h"
#include <QDebug>

MainProvider::MainProvider()
{
    setObjects();
    setObjectsData();
    setConnections();
    mainWindow.show();
}

void MainProvider::setObjects()
{
    viewModel = new MainViewModel(&mainWindow);
//    debugger = new ControlDebugger();
    switchMap = new ControlSwitchMap();
    view = mainWindow.getControlView();
    scene = new SceneView();
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

void MainProvider::setConnections()
{
    connect(&mainWindow, SIGNAL(closeWindow()), this, SLOT(windowClosed()));
    connect(buttonStopAll, SIGNAL(clicked()), viewModel, SLOT(stopAllChannels()));
    connect(scene, SIGNAL(controlObjectClicked(ObjectModel::ObjectType, int)), viewModel, SLOT(controlObjectClicked(ObjectModel::ObjectType, int)));
    connect(actionRun, SIGNAL(triggered()), viewModel, SLOT(runTriggered()));
    connect(actionEnableAI, SIGNAL(toggled(bool)), viewModel, SLOT(aiEnabled(bool)));
//    connect(actionDebugPanel, SIGNAL(triggered()), debugger, SLOT(show()));
    connect(actionReset, SIGNAL(triggered()), viewModel, SLOT(resetTrainsTriggered()));
}

void MainProvider::setObjectsData()
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
//    debugger->setSensors(sensors);
//    debugger->setRails(rails);
//    debugger->setTrains(trains);
//    debugger->setSwitches(switches);
//    debugger->setDebuggerData();
}

void MainProvider::prepareButtons()
{
    QMapIterator<int, ButtonModel*> buttonList(buttons);
    while (buttonList.hasNext()) {
        buttonList.next();
        buttonList.value()->setID(buttonList.key());
        buttonList.value()->setSlider(sliders.value(buttonList.key()));
    }
}

void MainProvider::prepareSliders()
{
    QMapIterator<int, SliderModel*> sliderList(sliders);
    while (sliderList.hasNext()) {
        sliderList.next();
        sliderList.value()->setID(sliderList.key());
        sliderList.value()->setLabel(labels.value(sliderList.key()));
    }
}

void MainProvider::prepareLabels()
{
    QMapIterator<int, LabelModel*> labelList(labels);
    while (labelList.hasNext()) {
        labelList.next();
        labelList.value()->setID(labelList.key());
    }
}

void MainProvider::prepareSwitches()
{
    switches.insert(SwitchModel::SWITCH_1, new SwitchModel(SwitchModel::TYPE_RIGHT, SwitchModel::SWITCH_1));
    switches.insert(SwitchModel::SWITCH_2, new SwitchModel(SwitchModel::TYPE_LEFT, SwitchModel::SWITCH_2));
    switches.insert(SwitchModel::SWITCH_3, new SwitchModel(SwitchModel::TYPE_LEFT, SwitchModel::SWITCH_3));
    switches.insert(SwitchModel::SWITCH_4, new SwitchModel(SwitchModel::TYPE_RIGHT, SwitchModel::SWITCH_4));
    switches.insert(SwitchModel::SWITCH_5, new SwitchModel(SwitchModel::TYPE_RIGHT, SwitchModel::SWITCH_5));
    switches.insert(SwitchModel::SWITCH_6, new SwitchModel(SwitchModel::TYPE_LEFT, SwitchModel::SWITCH_6));
    switches.insert(SwitchModel::SWITCH_7, new SwitchModel(SwitchModel::TYPE_RIGHT, SwitchModel::SWITCH_7));
    switches.insert(SwitchModel::SWITCH_8, new SwitchModel(SwitchModel::TYPE_RIGHT, SwitchModel::SWITCH_8));
    switches.insert(SwitchModel::SWITCH_9, new SwitchModel(SwitchModel::TYPE_LEFT, SwitchModel::SWITCH_9));

    QMapIterator<int, SwitchModel*> switchList(switches);
    while (switchList.hasNext()) {
        switchList.next();
        switchList.value()->setFlag(QGraphicsItem::ItemIsFocusable);
        switchList.value()->setControlAction(new ActionModel(switchList.value()->getIcon(), ActionModel::ACTION_SWITCH, switchList.value()->getSwitchID(), toolBar));
        connect(switchList.value(), SIGNAL(objectChanged()), scene, SLOT(update()));
        toolBar->addAction(switchList.value()->getControlAction());
        scene->addItem(switchList.value());
    }
}

void MainProvider::prepareLights()
{
    lights.insert(LightModel::LIGHT_1, new LightModel(LightModel::LIGHT_1, QPointF(10.95, 690), 180));
    lights.insert(LightModel::LIGHT_2, new LightModel(LightModel::LIGHT_2, QPointF(24.09, 258), 0));
    lights.insert(LightModel::LIGHT_3, new LightModel(LightModel::LIGHT_3, QPointF(40.5, 610), 180));
    lights.insert(LightModel::LIGHT_4, new LightModel(LightModel::LIGHT_4, QPointF(53.64, 300), 0));
    lights.insert(LightModel::LIGHT_5, new LightModel(LightModel::LIGHT_5, QPointF(73.2, 590), 180));
    lights.insert(LightModel::LIGHT_6, new LightModel(LightModel::LIGHT_6, QPointF(86.34, 323), 0));
    lights.insert(LightModel::LIGHT_7, new LightModel(LightModel::LIGHT_7, QPointF(10.95, 146), 180));
    lights.insert(LightModel::LIGHT_8, new LightModel(LightModel::LIGHT_8, QPointF(245, 22.99), 90));
    lights.insert(LightModel::LIGHT_9, new LightModel(LightModel::LIGHT_9, QPointF(315, 9.85), -90));
    lights.insert(LightModel::LIGHT_10, new LightModel(LightModel::LIGHT_10, QPointF(797, 22.99), 90));
    lights.insert(LightModel::LIGHT_11, new LightModel(LightModel::LIGHT_11, QPointF(350, 44.89), -90));
    lights.insert(LightModel::LIGHT_12, new LightModel(LightModel::LIGHT_12, QPointF(762, 58.03), 90));
    lights.insert(LightModel::LIGHT_13, new LightModel(LightModel::LIGHT_13, QPointF(867, 9.85), -90));
    lights.insert(LightModel::LIGHT_14, new LightModel(LightModel::LIGHT_14, QPointF(876, 246.35), -90));
    lights.insert(LightModel::LIGHT_15, new LightModel(LightModel::LIGHT_15, QPointF(805.8, 259.49), 90));
    lights.insert(LightModel::LIGHT_16, new LightModel(LightModel::LIGHT_16, QPointF(490.5, 246.35), -90));
    lights.insert(LightModel::LIGHT_17, new LightModel(LightModel::LIGHT_17, QPointF(770.8, 224.43), 90));
    lights.insert(LightModel::LIGHT_18, new LightModel(LightModel::LIGHT_18, QPointF(525.506, 211.31), -90));
    lights.insert(LightModel::LIGHT_19, new LightModel(LightModel::LIGHT_19, QPointF(560.355, 176.28), -90));
    lights.insert(LightModel::LIGHT_20, new LightModel(LightModel::LIGHT_20, QPointF(385.4, 224.43), 90));
    lights.insert(LightModel::LIGHT_21, new LightModel(LightModel::LIGHT_21, QPointF(24.09, 760.95), 0));

    QMapIterator<int, LightModel*> lightList(lights);
    while (lightList.hasNext()) {
        lightList.next();
        lightList.value()->setFlag(QGraphicsItem::ItemIsFocusable);
        lightList.value()->setControlAction(new ActionModel(lightList.value()->getIcon(), ActionModel::ACTION_LIGHT, lightList.value()->getLightID(), toolBar));
        connect(lightList.value(), SIGNAL(objectChanged()), scene, SLOT(update()));
        toolBar->addAction(lightList.value()->getControlAction());
        scene->addItem(lightList.value());
    }
}

void MainProvider::prepareRails()
{
    rails.insert(RailModel::RAIL_SECTION_1, new RailModel(RailModel::RAIL_SECTION_1));
    rails.insert(RailModel::RAIL_SECTION_2, new RailModel(RailModel::RAIL_SECTION_2));
    rails.insert(RailModel::RAIL_SECTION_3, new RailModel(RailModel::RAIL_SECTION_3));
    rails.insert(RailModel::RAIL_SECTION_4, new RailModel(RailModel::RAIL_SECTION_4));
    rails.insert(RailModel::RAIL_SECTION_5, new RailModel(RailModel::RAIL_SECTION_5));
    rails.insert(RailModel::RAIL_SECTION_6, new RailModel(RailModel::RAIL_SECTION_6));
    rails.insert(RailModel::RAIL_SECTION_7, new RailModel(RailModel::RAIL_SECTION_7));
    rails.insert(RailModel::RAIL_SECTION_8, new RailModel(RailModel::RAIL_SECTION_8));
    rails.insert(RailModel::RAIL_SECTION_9, new RailModel(RailModel::RAIL_SECTION_9));
    rails.insert(RailModel::RAIL_SECTION_10, new RailModel(RailModel::RAIL_SECTION_10));

    int lightID = LightModel::LIGHT_1;
    for (auto rail : rails) {
        if (lightID == 18)
            lightID++;
        rail->setLights(QList<LightModel*>() << lights.value(LightModel::LightID(lightID)) << lights.value(LightModel::LightID(lightID+1)));
        lightID+=2;
    }

    rails.value(RailModel::RAIL_SECTION_1)->setRails(RailModel::REVERSE, QList<RailModel*>() << rails.value(RailModel::RAIL_SECTION_10));
    rails.value(RailModel::RAIL_SECTION_1)->setRails(RailModel::FORWARD, QList<RailModel*>() << rails.value(RailModel::RAIL_SECTION_4));
    rails.value(RailModel::RAIL_SECTION_2)->setRails(RailModel::REVERSE, QList<RailModel*>() << rails.value(RailModel::RAIL_SECTION_10));
    rails.value(RailModel::RAIL_SECTION_2)->setRails(RailModel::FORWARD, QList<RailModel*>() << rails.value(RailModel::RAIL_SECTION_4));
    rails.value(RailModel::RAIL_SECTION_3)->setRails(RailModel::REVERSE, QList<RailModel*>() << rails.value(RailModel::RAIL_SECTION_10));
    rails.value(RailModel::RAIL_SECTION_3)->setRails(RailModel::FORWARD, QList<RailModel*>() << rails.value(RailModel::RAIL_SECTION_4));
    rails.value(RailModel::RAIL_SECTION_4)->setRails(RailModel::REVERSE, QList<RailModel*>() << rails.value(RailModel::RAIL_SECTION_1) << rails.value(RailModel::RAIL_SECTION_2) << rails.value(RailModel::RAIL_SECTION_3));
    rails.value(RailModel::RAIL_SECTION_4)->setRails(RailModel::FORWARD, QList<RailModel*>() << rails.value(RailModel::RAIL_SECTION_5) << rails.value(RailModel::RAIL_SECTION_6));
    rails.value(RailModel::RAIL_SECTION_5)->setRails(RailModel::REVERSE, QList<RailModel*>() << rails.value(RailModel::RAIL_SECTION_4));
    rails.value(RailModel::RAIL_SECTION_5)->setRails(RailModel::FORWARD, QList<RailModel*>() << rails.value(RailModel::RAIL_SECTION_7));
    rails.value(RailModel::RAIL_SECTION_6)->setRails(RailModel::REVERSE, QList<RailModel*>() << rails.value(RailModel::RAIL_SECTION_4));
    rails.value(RailModel::RAIL_SECTION_6)->setRails(RailModel::FORWARD, QList<RailModel*>() << rails.value(RailModel::RAIL_SECTION_7));
    rails.value(RailModel::RAIL_SECTION_7)->setRails(RailModel::REVERSE, QList<RailModel*>() << rails.value(RailModel::RAIL_SECTION_5) << rails.value(RailModel::RAIL_SECTION_6));
    rails.value(RailModel::RAIL_SECTION_7)->setRails(RailModel::FORWARD, QList<RailModel*>() << rails.value(RailModel::RAIL_SECTION_8) << rails.value(RailModel::RAIL_SECTION_9));
    rails.value(RailModel::RAIL_SECTION_8)->setRails(RailModel::REVERSE, QList<RailModel*>() << rails.value(RailModel::RAIL_SECTION_7));
    rails.value(RailModel::RAIL_SECTION_8)->setRails(RailModel::FORWARD, QList<RailModel*>() << rails.value(RailModel::RAIL_SECTION_10));
    rails.value(RailModel::RAIL_SECTION_9)->setRails(RailModel::REVERSE, QList<RailModel*>() << rails.value(RailModel::RAIL_SECTION_7));
    rails.value(RailModel::RAIL_SECTION_9)->setRails(RailModel::FORWARD, QList<RailModel*>() << rails.value(RailModel::RAIL_SECTION_10));
    rails.value(RailModel::RAIL_SECTION_10)->setRails(RailModel::REVERSE, QList<RailModel*>() << rails.value(RailModel::RAIL_SECTION_8) << rails.value(RailModel::RAIL_SECTION_9));
    rails.value(RailModel::RAIL_SECTION_10)->setRails(RailModel::FORWARD, QList<RailModel*>() << rails.value(RailModel::RAIL_SECTION_1) << rails.value(RailModel::RAIL_SECTION_2) << rails.value(RailModel::RAIL_SECTION_3));

    for (auto rail : rails) {
        qDebug() << QString::number(rail->getRails(RailModel::REVERSE).size()) + "___";
        for (auto test : rail->getRails(RailModel::FORWARD)) {
            qDebug() << test->getRailID();
        }
    }

    for (auto rail : rails) {
        connect(rail, SIGNAL(objectChanged()), scene, SLOT(update()));
//        connect(rail, SIGNAL(trainEnters(ControlTrain::TrainID, ControlRail::RailID)), ai, SLOT(trainEnters(ControlTrain::TrainID, ControlRail::RailID)));
//        connect(rail, SIGNAL(trainEntered(ControlTrain::TrainID, ControlRail::RailID)), ai, SLOT(trainEntered(ControlTrain::TrainID, ControlRail::RailID)));
//        connect(rail, SIGNAL(trainLeaving(ControlTrain::TrainID, ControlRail::RailID)), ai, SLOT(trainLeaving(ControlTrain::TrainID, ControlRail::RailID)));
//        connect(rail, SIGNAL(trainLeft(ControlTrain::TrainID, ControlRail::RailID)), ai, SLOT(trainLeft(ControlTrain::TrainID, ControlRail::RailID)));
//        connect(rail, SIGNAL(trainActivatedStop(ControlTrain::TrainID, ControlRail::RailID)), ai, SLOT(stopSensorActivated(ControlTrain::TrainID, ControlRail::RailID)));
        scene->addItem(rail);
    }
    scene->addItem(new QGraphicsPixmapItem(RailModel::getResource(RailModel::RAIL_SECTION_11)));

    for (RailModel *rail : rails) {
        if (rail->getObjectID() == RailModel::RAIL_SECTION_4 || rail->getObjectID() == RailModel::RAIL_SECTION_7 || rail->getObjectID() == RailModel::RAIL_SECTION_10)
            continue;
        QGraphicsBlurEffect *effect = new QGraphicsBlurEffect();
        effect->setBlurRadius(1.65);
        rail->setGraphicsEffect(effect);
        rail->graphicsEffect()->setEnabled(false);
        rail->setFlag(QGraphicsItem::ItemIsFocusable);
    }
}

void MainProvider::prepareTrains()
{
    trains.insert(TrainModel::TRAIN_1, new TrainModel(TrainModel::TRAIN_1, sliders.value(SliderModel::SLIDER_CHANNEL_1)));
    trains.insert(TrainModel::TRAIN_2, new TrainModel(TrainModel::TRAIN_2, sliders.value(SliderModel::SLIDER_CHANNEL_2)));
    trains.insert(TrainModel::TRAIN_3, new TrainModel(TrainModel::TRAIN_3, sliders.value(SliderModel::SLIDER_CHANNEL_3)));
    trains.insert(TrainModel::TRAIN_4, new TrainModel(TrainModel::TRAIN_4, sliders.value(SliderModel::SLIDER_CHANNEL_4)));
    trains.insert(TrainModel::TRAIN_5, new TrainModel(TrainModel::TRAIN_5, sliders.value(SliderModel::SLIDER_CHANNEL_5)));
    trains.insert(TrainModel::TRAIN_6, new TrainModel(TrainModel::TRAIN_6, sliders.value(SliderModel::SLIDER_CHANNEL_6)));
    trains.insert(TrainModel::TRAIN_7, new TrainModel(TrainModel::TRAIN_7, sliders.value(SliderModel::SLIDER_CHANNEL_7)));
    trains.insert(TrainModel::TRAIN_8, new TrainModel(TrainModel::TRAIN_8, sliders.value(SliderModel::SLIDER_CHANNEL_8)));
}

void MainProvider::prepareSensors()
{
    sensors.insert(SensorModel::SENSOR_1, new SensorModel(SensorModel::SENSOR_1, SensorModel::REVERSE_ENTRY_SENSOR));
    sensors.insert(SensorModel::SENSOR_2, new SensorModel(SensorModel::SENSOR_2, SensorModel::REVERSE_STOP_SENSOR));
    sensors.insert(SensorModel::SENSOR_3, new SensorModel(SensorModel::SENSOR_3, SensorModel::FORWARD_STOP_SENSOR));
    sensors.insert(SensorModel::SENSOR_4, new SensorModel(SensorModel::SENSOR_4, SensorModel::FORWARD_ENTRY_SENSOR));
    sensors.insert(SensorModel::SENSOR_5, new SensorModel(SensorModel::SENSOR_5, SensorModel::REVERSE_ENTRY_SENSOR));
    sensors.insert(SensorModel::SENSOR_6, new SensorModel(SensorModel::SENSOR_6, SensorModel::REVERSE_STOP_SENSOR));
    sensors.insert(SensorModel::SENSOR_7, new SensorModel(SensorModel::SENSOR_7, SensorModel::FORWARD_STOP_SENSOR));
    sensors.insert(SensorModel::SENSOR_8, new SensorModel(SensorModel::SENSOR_8, SensorModel::FORWARD_ENTRY_SENSOR));
    sensors.insert(SensorModel::SENSOR_9, new SensorModel(SensorModel::SENSOR_9, SensorModel::REVERSE_ENTRY_SENSOR));
    sensors.insert(SensorModel::SENSOR_10, new SensorModel(SensorModel::SENSOR_10, SensorModel::REVERSE_STOP_SENSOR));
    sensors.insert(SensorModel::SENSOR_11, new SensorModel(SensorModel::SENSOR_11, SensorModel::FORWARD_STOP_SENSOR));
    sensors.insert(SensorModel::SENSOR_12, new SensorModel(SensorModel::SENSOR_12, SensorModel::FORWARD_ENTRY_SENSOR));
    sensors.insert(SensorModel::SENSOR_13, new SensorModel(SensorModel::SENSOR_13, SensorModel::REVERSE_ENTRY_SENSOR));
    sensors.insert(SensorModel::SENSOR_14, new SensorModel(SensorModel::SENSOR_14, SensorModel::REVERSE_STOP_SENSOR));
    sensors.insert(SensorModel::SENSOR_15, new SensorModel(SensorModel::SENSOR_15, SensorModel::FORWARD_STOP_SENSOR));
    sensors.insert(SensorModel::SENSOR_16, new SensorModel(SensorModel::SENSOR_16, SensorModel::FORWARD_ENTRY_SENSOR));
    sensors.insert(SensorModel::SENSOR_17, new SensorModel(SensorModel::SENSOR_17, SensorModel::REVERSE_ENTRY_SENSOR));
    sensors.insert(SensorModel::SENSOR_18, new SensorModel(SensorModel::SENSOR_18, SensorModel::REVERSE_STOP_SENSOR));
    sensors.insert(SensorModel::SENSOR_19, new SensorModel(SensorModel::SENSOR_19, SensorModel::FORWARD_STOP_SENSOR));
    sensors.insert(SensorModel::SENSOR_20, new SensorModel(SensorModel::SENSOR_20, SensorModel::FORWARD_ENTRY_SENSOR));
    sensors.insert(SensorModel::SENSOR_21, new SensorModel(SensorModel::SENSOR_21, SensorModel::REVERSE_ENTRY_SENSOR));
    sensors.insert(SensorModel::SENSOR_22, new SensorModel(SensorModel::SENSOR_22, SensorModel::REVERSE_STOP_SENSOR));
    sensors.insert(SensorModel::SENSOR_23, new SensorModel(SensorModel::SENSOR_23, SensorModel::FORWARD_STOP_SENSOR));
    sensors.insert(SensorModel::SENSOR_24, new SensorModel(SensorModel::SENSOR_24, SensorModel::FORWARD_ENTRY_SENSOR));
    sensors.insert(SensorModel::SENSOR_25, new SensorModel(SensorModel::SENSOR_25, SensorModel::REVERSE_ENTRY_SENSOR));
    sensors.insert(SensorModel::SENSOR_26, new SensorModel(SensorModel::SENSOR_26, SensorModel::REVERSE_STOP_SENSOR));
    sensors.insert(SensorModel::SENSOR_27, new SensorModel(SensorModel::SENSOR_27, SensorModel::FORWARD_STOP_SENSOR));
    sensors.insert(SensorModel::SENSOR_28, new SensorModel(SensorModel::SENSOR_28, SensorModel::FORWARD_ENTRY_SENSOR));

    int sensorID = 0;
    for (RailModel *rail : rails) {
        if (rail->getObjectID() == RailModel::RAIL_SECTION_4 || rail->getObjectID() == RailModel::RAIL_SECTION_7 || rail->getObjectID() == RailModel::RAIL_SECTION_10)
            continue;
        connect(sensors.value(sensorID++), SIGNAL(signalChanged(SensorModel::SensorType)), rail, SLOT(sensorChanged(SensorModel::SensorType)));
        connect(sensors.value(sensorID++), SIGNAL(signalChanged(SensorModel::SensorType)), rail, SLOT(sensorChanged(SensorModel::SensorType)));
        connect(sensors.value(sensorID++), SIGNAL(signalChanged(SensorModel::SensorType)), rail, SLOT(sensorChanged(SensorModel::SensorType)));
        connect(sensors.value(sensorID++), SIGNAL(signalChanged(SensorModel::SensorType)), rail, SLOT(sensorChanged(SensorModel::SensorType)));
    }
}

void MainProvider::windowClosed()
{
    delete viewModel;
}
