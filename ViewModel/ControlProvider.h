#ifndef CONTROLPROVIDER_H
#define CONTROLPROVIDER_H

#include <Model/ControlAction.h>
#include <View/MainWindow.h>
#include <View/ControlScene.h>
#include <View/ControlView.h>
#include <ViewModel/ControlViewModel.h>
#include <QAction>
#include <QObject>
#include <QMap>
#include <QToolBar>
#include <QGraphicsPixmapItem>

class ControlProvider : QObject
{
    Q_OBJECT
public:
    explicit ControlProvider();
    void createObjects();
    void createConnections();
    void createObjectsData();
    void prepareButtons();
    void prepareSliders();
    void prepareLabels();
    void prepareSwitches();
    void prepareLights();

private:
    MainWindow mainWindow;
    ControlView *view;
    ControlScene *scene;
    QToolBar *toolBar;
    QAction *actionRun;
    QAction *actionEnableAI;
    QAction *actionEpplicationSettings;
    QMap<qint8, ControlButton*> buttons;
    QMap<qint8, ControlSlider*> sliders;
    QMap<qint8, ControlLabel*> labels;
    QMap<qint8, ControlAction*> actions;
    QMap<qint8, ControlAction*> switches;
    QMap<qint8, ControlAction*> lights;
};

#endif // CONTROLPROVIDER_H
