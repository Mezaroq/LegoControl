#include "View/MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Lego Control");
}

QMap<int, ControlButton *> MainWindow::getButtons()
{
    QMap<int, ControlButton *> buttons;
    buttons.insert(ControlButton::BUTTON_CHANNEL_1, ui->buttonChannel1);
    buttons.insert(ControlButton::BUTTON_CHANNEL_2, ui->buttonChannel2);
    buttons.insert(ControlButton::BUTTON_CHANNEL_3,  ui->buttonChannel3);
    buttons.insert(ControlButton::BUTTON_CHANNEL_4,  ui->buttonChannel4);
    buttons.insert(ControlButton::BUTTON_CHANNEL_5,  ui->buttonChannel5);
    buttons.insert(ControlButton::BUTTON_CHANNEL_6,  ui->buttonChannel6);
    buttons.insert(ControlButton::BUTTON_CHANNEL_7,  ui->buttonChannel7);
    buttons.insert(ControlButton::BUTTON_CHANNEL_8,  ui->buttonChannel8);

    return buttons;
}

QMap<int, ControlSlider *> MainWindow::getSliders()
{
    QMap<int, ControlSlider*> sliders;
    sliders.insert(ControlSlider::SLIDER_CHANNEL_1, ui->sliderChannel1);
    sliders.insert(ControlSlider::SLIDER_CHANNEL_2, ui->sliderChannel2);
    sliders.insert(ControlSlider::SLIDER_CHANNEL_3, ui->sliderChannel3);
    sliders.insert(ControlSlider::SLIDER_CHANNEL_4, ui->sliderChannel4);
    sliders.insert(ControlSlider::SLIDER_CHANNEL_5, ui->sliderChannel5);
    sliders.insert(ControlSlider::SLIDER_CHANNEL_6, ui->sliderChannel6);
    sliders.insert(ControlSlider::SLIDER_CHANNEL_7, ui->sliderChannel7);
    sliders.insert(ControlSlider::SLIDER_CHANNEL_8, ui->sliderChannel8);

    return sliders;
}

QMap<int, ControlLabel *> MainWindow::getLabels()
{
    QMap<int, ControlLabel*> labels;
    labels.insert(ControlLabel::LABEL_CHANNEL_1, ui->labelChannel1);
    labels.insert(ControlLabel::LABEL_CHANNEL_2, ui->labelChannel2);
    labels.insert(ControlLabel::LABEL_CHANNEL_3, ui->labelChannel3);
    labels.insert(ControlLabel::LABEL_CHANNEL_4, ui->labelChannel4);
    labels.insert(ControlLabel::LABEL_CHANNEL_5, ui->labelChannel5);
    labels.insert(ControlLabel::LABEL_CHANNEL_6, ui->labelChannel6);
    labels.insert(ControlLabel::LABEL_CHANNEL_7, ui->labelChannel7);
    labels.insert(ControlLabel::LABEL_CHANNEL_8, ui->labelChannel8);

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

ControlView *MainWindow::getControlView()
{
    return ui->graphicsView;
}

MainWindow::~MainWindow()
{
    emit closeWindow();
    delete ui;
}
