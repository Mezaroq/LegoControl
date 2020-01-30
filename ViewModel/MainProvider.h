#ifndef CONTROLPROVIDER_H
#define CONTROLPROVIDER_H

#include <Model/ActionModel.h>
#include <Model/LabelModel.h>
#include <Model/SliderModel.h>
#include <Model/ButtonModel.h>
#include <Model/RailModel.h>
#include <Model/LightModel.h>
#include <Model/SwitchModel.h>
#include <Model/TrainModel.h>
#include <Model/SensorModel.h>
#include <Model/StationModel.h>
#include <Model/ControlSwitchMap.h>
#include <View/MainWindow.h>
#include <View/SceneView.h>
#include <View/GraphicsView.h>
#include <View/DebuggerView.h>
#include <ViewModel/MainViewModel.h>
#include <ViewModel/TrafficManagerViewModel.h>
#include <QAction>
#include <QObject>
#include <QMap>
#include <QToolBar>

class MainProvider : QObject
{
    Q_OBJECT
public:
    explicit MainProvider();
    void setObjects();
    void setGlobalConnections();
    void setObjectsData();
    void prependButtons();
    void prependSliders();
    void prependLabels();
    void prependSwitches();
    void prependLights();
    void prependRails();
    void prependTrains();
    void prependSensors();
    void prependStations();
    void prependTrafficManager();

private:
    MainViewModel *viewModel;
    DebuggerView *debugger;
    MainWindow mainWindow;
    GraphicsView *view;
    SceneView *scene;
    QToolBar *toolBar;
    QStatusBar *statusBar;
    QPushButton *buttonStopAll;
    QAction *actionRun;
    QAction *actionEnableAI;
    QAction *actionDebugPanel;
    QAction *actionReset;
    ControlSwitchMap *switchMap;
    TrafficManagerViewModel *trafficManager;
    QMap<int, ButtonModel*> buttons;
    QMap<int, SliderModel*> sliders;
    QMap<int, LabelModel*> labels;
    QMap<int, SwitchModel*> switches;
    QMap<int, LightModel*> lights;
    QMap<int, RailModel*> rails;
    QMap<int, TrainModel*> trains;
    QMap<int, SensorModel*> sensors;
    QMap<int, StationModel*> stations;

public slots:
    void windowClosed();
};

#endif // CONTROLPROVIDER_H
