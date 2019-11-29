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
    view = mainWindow.getControlView();
    scene = new ControlScene();
    buttonStopAll = mainWindow.getButtonStopAll();
    actionRun = mainWindow.getActionRun();
    actionEnableAI = mainWindow.getActionEnableAI();
    actionEpplicationSettings = mainWindow.getActionApplicationSettings();
    toolBar = mainWindow.getToolBar();
    buttons = mainWindow.getButtons();
    sliders = mainWindow.getSliders();
    labels = mainWindow.getLabels();
}

void ControlProvider::createConnections()
{
    connect(buttonStopAll, SIGNAL(clicked()), viewModel, SLOT(stopAllChannels()));
    connect(scene, SIGNAL(controlObjectClicked(ControlObject::ObjectType, int)), viewModel, SLOT(controlObjectClicked(ControlObject::ObjectType, int)));
}

void ControlProvider::createObjectsData()
{
    scene->setBackgroundBrush(QColor("#539920"));
    view->setScene(scene);
    prepareLabels();
    prepareSliders();
    prepareButtons();
    prepareSwitches();
    toolBar->addSeparator();
    prepareLights();
    prepareRails();
    viewModel->setSliders(sliders);
    viewModel->setLights(lights);
    viewModel->setSwitches(switches);
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
        //add connections to vm (id, value) albo nie bo wysylanie bedzie samo zbieralo dane ze wszyzstkiego wiec nic nie musze wysylac, tylko zrobic gety
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
    switches.insert(ControlSwitch::SWITCH_01, new ControlSwitch(ControlSwitch::TYPE_RIGHT, ControlSwitch::SWITCH_01));
    switches.insert(ControlSwitch::SWITCH_02, new ControlSwitch(ControlSwitch::TYPE_LEFT, ControlSwitch::SWITCH_02));
    switches.insert(ControlSwitch::SWITCH_03, new ControlSwitch(ControlSwitch::TYPE_LEFT, ControlSwitch::SWITCH_03));
    switches.insert(ControlSwitch::SWITCH_04, new ControlSwitch(ControlSwitch::TYPE_RIGHT, ControlSwitch::SWITCH_04));
    switches.insert(ControlSwitch::SWITCH_05, new ControlSwitch(ControlSwitch::TYPE_RIGHT, ControlSwitch::SWITCH_05));
    switches.insert(ControlSwitch::SWITCH_06, new ControlSwitch(ControlSwitch::TYPE_LEFT, ControlSwitch::SWITCH_06));
    switches.insert(ControlSwitch::SWITCH_07, new ControlSwitch(ControlSwitch::TYPE_RIGHT, ControlSwitch::SWITCH_07));
    switches.insert(ControlSwitch::SWITCH_08, new ControlSwitch(ControlSwitch::TYPE_RIGHT, ControlSwitch::SWITCH_08));
    switches.insert(ControlSwitch::SWITCH_09, new ControlSwitch(ControlSwitch::TYPE_LEFT, ControlSwitch::SWITCH_09));

    QMapIterator<int, ControlSwitch*> switchList(switches);
    while (switchList.hasNext()) {
        switchList.next();
        switchList.value()->setFlag(QGraphicsItem::ItemIsFocusable);
        switchList.value()->setControlAction(new ControlAction(switchList.value()->getIcon(), ControlAction::ACTION_SWITCH, switchList.value()->getSwitchID(), toolBar));
        toolBar->addAction(switchList.value()->getControlAction());
        scene->addItem(switchList.value());
    }
}

void ControlProvider::prepareLights()
{
    lights.insert(ControlLight::LIGHT_01, new ControlLight(ControlLight::LIGHT_01, QPointF(10.95, 690), 180));
    lights.insert(ControlLight::LIGHT_02, new ControlLight(ControlLight::LIGHT_02, QPointF(24.09, 258), 0));
    lights.insert(ControlLight::LIGHT_03, new ControlLight(ControlLight::LIGHT_03, QPointF(40.5, 610), 180));
    lights.insert(ControlLight::LIGHT_04, new ControlLight(ControlLight::LIGHT_04, QPointF(53.64, 300), 0));
    lights.insert(ControlLight::LIGHT_05, new ControlLight(ControlLight::LIGHT_05, QPointF(73.2, 590), 180));
    lights.insert(ControlLight::LIGHT_06, new ControlLight(ControlLight::LIGHT_06, QPointF(86.34, 323), 0));
    lights.insert(ControlLight::LIGHT_07, new ControlLight(ControlLight::LIGHT_07, QPointF(10.95, 146), 180));
    lights.insert(ControlLight::LIGHT_08, new ControlLight(ControlLight::LIGHT_08, QPointF(245, 22.99), 90));
    lights.insert(ControlLight::LIGHT_09, new ControlLight(ControlLight::LIGHT_09, QPointF(315, 9.85), -90));
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
        toolBar->addAction(lightList.value()->getControlAction());
        scene->addItem(lightList.value());
    }
}

void ControlProvider::prepareRails()
{
    rails.insert(ControlRail::RAIL_SECTION_01, new ControlRail(ControlRail::RAIL_SECTION_01));
    rails.insert(ControlRail::RAIL_SECTION_02, new ControlRail(ControlRail::RAIL_SECTION_02));
    rails.insert(ControlRail::RAIL_SECTION_03, new ControlRail(ControlRail::RAIL_SECTION_03));
    rails.insert(ControlRail::RAIL_SECTION_04, new ControlRail(ControlRail::RAIL_SECTION_04));
    rails.insert(ControlRail::RAIL_SECTION_05, new ControlRail(ControlRail::RAIL_SECTION_05));
    rails.insert(ControlRail::RAIL_SECTION_06, new ControlRail(ControlRail::RAIL_SECTION_06));
    rails.insert(ControlRail::RAIL_SECTION_07, new ControlRail(ControlRail::RAIL_SECTION_07));
    rails.insert(ControlRail::RAIL_SECTION_08, new ControlRail(ControlRail::RAIL_SECTION_08));
    rails.insert(ControlRail::RAIL_SECTION_09, new ControlRail(ControlRail::RAIL_SECTION_09));
    rails.insert(ControlRail::RAIL_SECTION_10, new ControlRail(ControlRail::RAIL_SECTION_10));

    QMapIterator<int, ControlRail*> railList(rails);
    while (railList.hasNext()) {
        railList.next();
        scene->addItem(railList.value());
    }
    scene->addItem(new QGraphicsPixmapItem(ControlRail::getResource(ControlRail::RAIL_SECTION_11)));
}
