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
    view = mainWindow.getControlView();
    scene = new ControlScene();
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

}

void ControlProvider::createObjectsData()
{
    view->setScene(scene);
    prepareLabels();
    prepareSliders();
    prepareButtons();
    prepareSwitches();
    toolBar->addSeparator();
    prepareLights();
//    qDebug() << actions;

    scene->addItem(new QGraphicsPixmapItem(QPixmap(":/control/resources/objects/object_rail_section_switches.png")));
    scene->addItem(new QGraphicsPixmapItem(QPixmap(":/control/resources/objects/object_rail_section_01.png")));
    scene->addItem(new QGraphicsPixmapItem(QPixmap(":/control/resources/objects/object_rail_section_02.png")));
    scene->addItem(new QGraphicsPixmapItem(QPixmap(":/control/resources/objects/object_rail_section_03.png")));
    scene->addItem(new QGraphicsPixmapItem(QPixmap(":/control/resources/objects/object_rail_section_04.png")));
    scene->addItem(new QGraphicsPixmapItem(QPixmap(":/control/resources/objects/object_rail_section_05.png")));
    scene->addItem(new QGraphicsPixmapItem(QPixmap(":/control/resources/objects/object_rail_section_06.png")));
    scene->addItem(new QGraphicsPixmapItem(QPixmap(":/control/resources/objects/object_rail_section_07.png")));
    scene->addItem(new QGraphicsPixmapItem(QPixmap(":/control/resources/objects/object_rail_section_08.png")));
    scene->addItem(new QGraphicsPixmapItem(QPixmap(":/control/resources/objects/object_rail_section_09.png")));
    scene->addItem(new QGraphicsPixmapItem(QPixmap(":/control/resources/objects/object_rail_section_10.png")));
    scene->setBackgroundBrush(QColor("#539920"));
}

void ControlProvider::prepareButtons()
{
    QMapIterator<qint8, ControlButton*> buttonList(buttons);
    while (buttonList.hasNext()) {
        buttonList.next();
        buttonList.value()->setID(buttonList.key());
        //add connections to vm (id)
    }
}

void ControlProvider::prepareSliders()
{
    QMapIterator<qint8, ControlSlider*> sliderList(sliders);
    while (sliderList.hasNext()) {
        sliderList.next();
        sliderList.value()->setID(sliderList.key());
        sliderList.value()->setLabel(labels.value(sliderList.key()));
        //add connections to vm (id, value)
    }
}

void ControlProvider::prepareLabels()
{
    QMapIterator<qint8, ControlLabel*> labelList(labels);
    while (labelList.hasNext()) {
        labelList.next();
        labelList.value()->setID(labelList.key());
    }
}

void ControlProvider::prepareSwitches()
{
    switches.insert(ControlViewModel::SWITCH1, new ControlAction(QIcon(":/control/resources/icons/icon_bar_switch_neutral.svg"), "Switch 1", toolBar));
    switches.insert(ControlViewModel::SWITCH2, new ControlAction(QIcon(":/control/resources/icons/icon_bar_switch_neutral.svg"), "Switch 2", toolBar));
    switches.insert(ControlViewModel::SWITCH3, new ControlAction(QIcon(":/control/resources/icons/icon_bar_switch_neutral.svg"), "Switch 3", toolBar));
    switches.insert(ControlViewModel::SWITCH4, new ControlAction(QIcon(":/control/resources/icons/icon_bar_switch_neutral.svg"), "Switch 4", toolBar));
    switches.insert(ControlViewModel::SWITCH5, new ControlAction(QIcon(":/control/resources/icons/icon_bar_switch_neutral.svg"), "Switch 5", toolBar));
    switches.insert(ControlViewModel::SWITCH6, new ControlAction(QIcon(":/control/resources/icons/icon_bar_switch_neutral.svg"), "Switch 6", toolBar));
    switches.insert(ControlViewModel::SWITCH7, new ControlAction(QIcon(":/control/resources/icons/icon_bar_switch_neutral.svg"), "Switch 7", toolBar));
    switches.insert(ControlViewModel::SWITCH8, new ControlAction(QIcon(":/control/resources/icons/icon_bar_switch_neutral.svg"), "Switch 8", toolBar));
    switches.insert(ControlViewModel::SWITCH9, new ControlAction(QIcon(":/control/resources/icons/icon_bar_switch_neutral.svg"), "Switch 9", toolBar));

    QMapIterator<qint8, ControlAction*> switchList(switches);
    while (switchList.hasNext()) {
        switchList.next();
        switchList.value()->setID(switchList.key());
        switchList.value()->setCheckable(true);
        toolBar->addAction(switchList.value());
        //add connections to vm (id)
    }
    actions.unite(switches);
}

void ControlProvider::prepareLights()
{
    lights.insert(ControlViewModel::LIGHT1, new ControlAction(QIcon(":/control/resources/icons/icon_bar_light_red.svg"), "Light 1", toolBar));
    lights.insert(ControlViewModel::LIGHT2, new ControlAction(QIcon(":/control/resources/icons/icon_bar_light_red.svg"), "Light 2", toolBar));
    lights.insert(ControlViewModel::LIGHT3, new ControlAction(QIcon(":/control/resources/icons/icon_bar_light_red.svg"), "Light 3", toolBar));
    lights.insert(ControlViewModel::LIGHT4, new ControlAction(QIcon(":/control/resources/icons/icon_bar_light_red.svg"), "Light 4", toolBar));
    lights.insert(ControlViewModel::LIGHT5, new ControlAction(QIcon(":/control/resources/icons/icon_bar_light_red.svg"), "Light 5", toolBar));
    lights.insert(ControlViewModel::LIGHT6, new ControlAction(QIcon(":/control/resources/icons/icon_bar_light_red.svg"), "Light 6", toolBar));
    lights.insert(ControlViewModel::LIGHT7, new ControlAction(QIcon(":/control/resources/icons/icon_bar_light_red.svg"), "Light 7", toolBar));
    lights.insert(ControlViewModel::LIGHT8, new ControlAction(QIcon(":/control/resources/icons/icon_bar_light_red.svg"), "Light 8", toolBar));
    lights.insert(ControlViewModel::LIGHT9, new ControlAction(QIcon(":/control/resources/icons/icon_bar_light_red.svg"), "Light 9", toolBar));
    lights.insert(ControlViewModel::LIGHT10, new ControlAction(QIcon(":/control/resources/icons/icon_bar_light_red.svg"), "Light 10", toolBar));
    lights.insert(ControlViewModel::LIGHT11, new ControlAction(QIcon(":/control/resources/icons/icon_bar_light_red.svg"), "Light 11", toolBar));
    lights.insert(ControlViewModel::LIGHT12, new ControlAction(QIcon(":/control/resources/icons/icon_bar_light_red.svg"), "Light 12", toolBar));
    lights.insert(ControlViewModel::LIGHT13, new ControlAction(QIcon(":/control/resources/icons/icon_bar_light_red.svg"), "Light 13", toolBar));
    lights.insert(ControlViewModel::LIGHT14, new ControlAction(QIcon(":/control/resources/icons/icon_bar_light_red.svg"), "Light 14", toolBar));
    lights.insert(ControlViewModel::LIGHT15, new ControlAction(QIcon(":/control/resources/icons/icon_bar_light_red.svg"), "Light 15", toolBar));
    lights.insert(ControlViewModel::LIGHT16, new ControlAction(QIcon(":/control/resources/icons/icon_bar_light_red.svg"), "Light 16", toolBar));
    lights.insert(ControlViewModel::LIGHT17, new ControlAction(QIcon(":/control/resources/icons/icon_bar_light_red.svg"), "Light 17", toolBar));
    lights.insert(ControlViewModel::LIGHT18, new ControlAction(QIcon(":/control/resources/icons/icon_bar_light_red.svg"), "Light 18", toolBar));
    lights.insert(ControlViewModel::LIGHT19, new ControlAction(QIcon(":/control/resources/icons/icon_bar_light_red.svg"), "Light 19", toolBar));
    lights.insert(ControlViewModel::LIGHT20, new ControlAction(QIcon(":/control/resources/icons/icon_bar_light_red.svg"), "Light 20", toolBar));
    lights.insert(ControlViewModel::LIGHT21, new ControlAction(QIcon(":/control/resources/icons/icon_bar_light_red.svg"), "Light 21", toolBar));

    QMapIterator<qint8, ControlAction*> lightList(lights);
    while (lightList.hasNext()) {
        lightList.next();
        qDebug() << lightList.key();
        lightList.value()->setID(lightList.key());
        lightList.value()->setCheckable(true);
        toolBar->addAction(lightList.value());
        //add connections to vm (id)
    }
    actions.unite(lights);
}
