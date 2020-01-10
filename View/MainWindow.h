#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Model/ControlLabel.h>
#include <Model/ControlSlider.h>
#include <Model/ControlButton.h>
#include <Model/ControlLabel.h>
#include <View/ControlView.h>
#include <ViewModel/ControlViewModel.h>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QMap<int, ControlButton*> getButtons();
    QMap<int, ControlSlider*> getSliders();
    QMap<int, ControlLabel*> getLabels();
    QPushButton* getButtonStopAll();
    QToolBar* getToolBar();
    QStatusBar* getStatusBar();
    QAction* getActionRun();
    QAction* getActionEnableAI();
    QAction* getActionDebugPanel();
    QAction* getActionReset();
    ControlView* getControlView();
    ~MainWindow();

private:
    Ui::MainWindow *ui;

signals:
    void closeWindow();
};
#endif // MAINWINDOW_H
