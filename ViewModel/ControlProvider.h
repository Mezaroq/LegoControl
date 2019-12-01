#ifndef CONTROLPROVIDER_H
#define CONTROLPROVIDER_H

#include <Model/ControlAction.h>
#include <Model/ControlLabel.h>
#include <Model/ControlSlider.h>
#include <Model/ControlButton.h>
#include <Model/ControlRail.h>
#include <Model/ControlLight.h>
#include <Model/ControlSwitch.h>
#include <Model/ControlTrain.h>
#include <View/MainWindow.h>
#include <View/ControlScene.h>
#include <View/ControlView.h>
#include <ViewModel/ControlViewModel.h>
#include <QAction>
#include <QObject>
#include <QMap>
#include <QToolBar>

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
    void prepareRails();
    void prepareTrains();

private:
    ControlViewModel *viewModel;
    MainWindow mainWindow;
    ControlView *view;
    ControlScene *scene;
    QToolBar *toolBar;
    QStatusBar *statusBar;
    QPushButton *buttonStopAll;
    QAction *actionRun;
    QAction *actionEnableAI;
    QAction *actionEpplicationSettings;
    QMap<int, ControlButton*> buttons;
    QMap<int, ControlSlider*> sliders;
    QMap<int, ControlLabel*> labels;
    QMap<int, ControlSwitch*> switches;
    QMap<int, ControlLight*> lights;
    QMap<int, ControlRail*> rails;
    QMap<int, ControlTrain*> trains;
};

#endif // CONTROLPROVIDER_H
