#include "View/MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Lego Control");
}

QMap<qint8, ControlButton *> MainWindow::getButtons()
{
    QMap<qint8, ControlButton *> buttons;
    buttons.insert(ControlViewModel::BUTTON_CHANNEL_1, ui->buttonChannel1);
    buttons.insert(ControlViewModel::BUTTON_CHANNEL_2, ui->buttonChannel2);
    buttons.insert(ControlViewModel::BUTTON_CHANNEL_3,  ui->buttonChannel3);
    buttons.insert(ControlViewModel::BUTTON_CHANNEL_4,  ui->buttonChannel4);
    buttons.insert(ControlViewModel::BUTTON_CHANNEL_5,  ui->buttonChannel5);
    buttons.insert(ControlViewModel::BUTTON_CHANNEL_6,  ui->buttonChannel6);
    buttons.insert(ControlViewModel::BUTTON_CHANNEL_7,  ui->buttonChannel7);
    buttons.insert(ControlViewModel::BUTTON_CHANNEL_8,  ui->buttonChannel8);
    buttons.insert(ControlViewModel::BUTTON_STOP_ALL,  ui->buttonStopAll);

    return buttons;
}

QMap<qint8, ControlSlider *> MainWindow::getSliders()
{
    QMap<qint8, ControlSlider*> sliders;
    sliders.insert(ControlViewModel::SLIDER_CHANNEL_1, ui->sliderChannel1);
    sliders.insert(ControlViewModel::SLIDER_CHANNEL_2, ui->sliderChannel2);
    sliders.insert(ControlViewModel::SLIDER_CHANNEL_3, ui->sliderChannel3);
    sliders.insert(ControlViewModel::SLIDER_CHANNEL_4, ui->sliderChannel4);
    sliders.insert(ControlViewModel::SLIDER_CHANNEL_5, ui->sliderChannel5);
    sliders.insert(ControlViewModel::SLIDER_CHANNEL_6, ui->sliderChannel6);
    sliders.insert(ControlViewModel::SLIDER_CHANNEL_7, ui->sliderChannel7);
    sliders.insert(ControlViewModel::SLIDER_CHANNEL_8, ui->sliderChannel8);

    return sliders;
}

QMap<qint8, ControlLabel *> MainWindow::getLabels()
{
    QMap<qint8, ControlLabel*> labels;
    labels.insert(ControlViewModel::LABEL_CHANNEL_1, ui->labelChannel1);
    labels.insert(ControlViewModel::LABEL_CHANNEL_2, ui->labelChannel2);
    labels.insert(ControlViewModel::LABEL_CHANNEL_3, ui->labelChannel3);
    labels.insert(ControlViewModel::LABEL_CHANNEL_4, ui->labelChannel4);
    labels.insert(ControlViewModel::LABEL_CHANNEL_5, ui->labelChannel5);
    labels.insert(ControlViewModel::LABEL_CHANNEL_6, ui->labelChannel6);
    labels.insert(ControlViewModel::LABEL_CHANNEL_7, ui->labelChannel7);
    labels.insert(ControlViewModel::LABEL_CHANNEL_8, ui->labelChannel8);

    return labels;
}

QToolBar *MainWindow::getToolBar()
{
    return ui->toolBar;
}

QAction *MainWindow::getActionRun()
{
    return ui->actionRun;
}

QAction *MainWindow::getActionEnableAI()
{
    return ui->actionEnable_AI;
}

QAction *MainWindow::getActionApplicationSettings()
{
    return ui->actionApplication_settings;
}

ControlView *MainWindow::getControlView()
{
    return ui->graphicsView;
}

MainWindow::~MainWindow()
{
    delete ui;
}
