#include "View/MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Lego Control");
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
