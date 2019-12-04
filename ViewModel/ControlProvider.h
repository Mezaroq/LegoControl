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
#include <Model/ControlSensor.h>
#include <View/ControlDebugPanel.h>
#include <View/MainWindow.h>
#include <View/ControlScene.h>
#include <View/ControlView.h>
#include <ViewModel/ControlViewModel.h>
#include <ViewModel/AlieViewModel.h>
#include <QAction>
#include <QObject>
#include <QMap>
#include <QToolBar>

class ControlProvider : QObject
{
    Q_OBJECT
public:
    explicit ControlProvider();
    void setObjects();
    void setConnections();
    void setObjectsData();
    void prepareButtons();
    void prepareSliders();
    void prepareLabels();
    void prepareSwitches();
    void prepareLights();
    void prepareRails();
    void prepareTrains();
    void prepareSensors();

private:
    AlieViewModel *alieAI;
    ControlViewModel *viewModel;
    ControlDebugPanel *debugPanel;
    MainWindow mainWindow;
    ControlView *view;
    ControlScene *scene;
    QToolBar *toolBar;
    QStatusBar *statusBar;
    QPushButton *buttonStopAll;
    QAction *actionRun;
    QAction *actionEnableAI;
    QAction *actionEpplicationSettings;
    QAction *actionDebugPanel;
    QMap<int, ControlButton*> buttons;
    QMap<int, ControlSlider*> sliders;
    QMap<int, ControlLabel*> labels;
    QMap<int, ControlSwitch*> switches;
    QMap<int, ControlLight*> lights;
    QMap<int, ControlRail*> rails;
    QMap<int, ControlTrain*> trains;
    QMap<int, ControlSensor*> sensors;

public slots:
    void windowClosed();
};

#endif // CONTROLPROVIDER_H
