#include "View/MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Lego Control");
}

QMap<int, TrafficManagerButtonModel *> MainWindow::getManagerButtons()
{
    int id = 0;
    QMap<int, TrafficManagerButtonModel *> managerButtons;
    managerButtons.insert(id++, ui->normalSpeedIncrease);
    managerButtons.insert(id++, ui->normalSpeedDecrease);
    managerButtons.insert(id++, ui->slowdownSpeedIncrease);
    managerButtons.insert(id++, ui->slowdownSpeedDecrease);
    managerButtons.insert(id++, ui->startSpeedIncrease);
    managerButtons.insert(id++, ui->startSpeedDecrease);

    managerButtons.insert(id++, ui->priorityIncreaseTrain1);
    managerButtons.insert(id++, ui->priorityDecreaseTrain1);
    managerButtons.insert(id++, ui->waitingIncreaseTrain1);
    managerButtons.insert(id++, ui->waitingDecreaseTrain1);
    managerButtons.insert(id++, ui->centralStationTrain1);
    managerButtons.insert(id++, ui->northStationTrain1);
    managerButtons.insert(id++, ui->southStationTrain1);
    managerButtons.insert(id++, ui->directionTrain1);
    managerButtons.insert(id++, ui->inverseSpeed1);

    managerButtons.insert(id++, ui->priorityIncreaseTrain2);
    managerButtons.insert(id++, ui->priorityDecreaseTrain2);
    managerButtons.insert(id++, ui->waitingIncreaseTrain2);
    managerButtons.insert(id++, ui->waitingDecreaseTrain2);
    managerButtons.insert(id++, ui->centralStationTrain2);
    managerButtons.insert(id++, ui->northStationTrain2);
    managerButtons.insert(id++, ui->southStationTrain2);
    managerButtons.insert(id++, ui->directionTrain2);
    managerButtons.insert(id++, ui->inverseSpeed2);

    managerButtons.insert(id++, ui->priorityIncreaseTrain3);
    managerButtons.insert(id++, ui->priorityDecreaseTrain3);
    managerButtons.insert(id++, ui->waitingIncreaseTrain3);
    managerButtons.insert(id++, ui->waitingDecreaseTrain3);
    managerButtons.insert(id++, ui->centralStationTrain3);
    managerButtons.insert(id++, ui->northStationTrain3);
    managerButtons.insert(id++, ui->southStationTrain3);
    managerButtons.insert(id++, ui->directionTrain3);
    managerButtons.insert(id++, ui->inverseSpeed3);

    return managerButtons;
}

QMap<int, TrafficManagerLabelModel *> MainWindow::getManagerLabels()
{
    int id = 0;
    QMap<int, TrafficManagerLabelModel *> managerLabels;
    managerLabels.insert(id++, ui->normalSpeedLabel);
    managerLabels.insert(id++, ui->slowdownSpeedLabel);
    managerLabels.insert(id++, ui->startSpeedLabel);
    managerLabels.insert(id++, ui->priorityTrain1);
    managerLabels.insert(id++, ui->waitingTrain1);
    managerLabels.insert(id++, ui->priorityTrain2);
    managerLabels.insert(id++, ui->waitingTrain2);
    managerLabels.insert(id++, ui->priorityTrain3);
    managerLabels.insert(id++, ui->waitingTrain3);

    return managerLabels;
}

QMap<int, ButtonModel *> MainWindow::getButtons()
{
    QMap<int, ButtonModel *> buttons;
    buttons.insert(ButtonModel::BUTTON_CHANNEL_1, ui->buttonChannel1);
    buttons.insert(ButtonModel::BUTTON_CHANNEL_2, ui->buttonChannel2);
    buttons.insert(ButtonModel::BUTTON_CHANNEL_3,  ui->buttonChannel3);
    buttons.insert(ButtonModel::BUTTON_CHANNEL_4,  ui->buttonChannel4);
    buttons.insert(ButtonModel::BUTTON_CHANNEL_5,  ui->buttonChannel5);
    buttons.insert(ButtonModel::BUTTON_CHANNEL_6,  ui->buttonChannel6);
    buttons.insert(ButtonModel::BUTTON_CHANNEL_7,  ui->buttonChannel7);
    buttons.insert(ButtonModel::BUTTON_CHANNEL_8,  ui->buttonChannel8);

    return buttons;
}

QMap<int, SliderModel *> MainWindow::getSliders()
{
    QMap<int, SliderModel*> sliders;
    sliders.insert(SliderModel::SLIDER_CHANNEL_1, ui->sliderChannel1);
    sliders.insert(SliderModel::SLIDER_CHANNEL_2, ui->sliderChannel2);
    sliders.insert(SliderModel::SLIDER_CHANNEL_3, ui->sliderChannel3);
    sliders.insert(SliderModel::SLIDER_CHANNEL_4, ui->sliderChannel4);
    sliders.insert(SliderModel::SLIDER_CHANNEL_5, ui->sliderChannel5);
    sliders.insert(SliderModel::SLIDER_CHANNEL_6, ui->sliderChannel6);
    sliders.insert(SliderModel::SLIDER_CHANNEL_7, ui->sliderChannel7);
    sliders.insert(SliderModel::SLIDER_CHANNEL_8, ui->sliderChannel8);

    return sliders;
}

QMap<int, LabelModel *> MainWindow::getLabels()
{
    QMap<int, LabelModel*> labels;
    labels.insert(LabelModel::LABEL_CHANNEL_1, ui->labelChannel1);
    labels.insert(LabelModel::LABEL_CHANNEL_2, ui->labelChannel2);
    labels.insert(LabelModel::LABEL_CHANNEL_3, ui->labelChannel3);
    labels.insert(LabelModel::LABEL_CHANNEL_4, ui->labelChannel4);
    labels.insert(LabelModel::LABEL_CHANNEL_5, ui->labelChannel5);
    labels.insert(LabelModel::LABEL_CHANNEL_6, ui->labelChannel6);
    labels.insert(LabelModel::LABEL_CHANNEL_7, ui->labelChannel7);
    labels.insert(LabelModel::LABEL_CHANNEL_8, ui->labelChannel8);

    return labels;
}

QPushButton *MainWindow::getButtonStopAll()
{
    return ui->buttonStopAll;
}

QToolBar *MainWindow::getToolBar()
{
    return ui->toolBar;
}

QStatusBar *MainWindow::getStatusBar()
{
    return ui->statusbar;
}

QAction *MainWindow::getActionRun()
{
    return ui->actionRun;
}

QAction *MainWindow::getActionEnableAI()
{
    return ui->actionEnable_AI;
}

QAction *MainWindow::getActionDebugPanel()
{
    return ui->actionDebug_Panel;
}

QAction *MainWindow::getActionReset()
{
    return ui->actionReset;
}

GraphicsView *MainWindow::getControlView()
{
    return ui->graphicsView;
}

MainWindow::~MainWindow()
{
    emit closeWindow();
    delete ui;
}
