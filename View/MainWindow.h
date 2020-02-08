#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Model/LabelModel.h>
#include <Model/SliderModel.h>
#include <Model/ButtonModel.h>
#include <Model/LabelModel.h>
#include <Model/TrafficManagerButtonModel.h>
#include <Model/TrafficManagerLabelModel.h>
#include <View/GraphicsView.h>
#include <ViewModel/MainViewModel.h>
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
    QMap<int, TrafficManagerButtonModel*> getManagerButtons();
    QMap<int, TrafficManagerLabelModel*> getManagerLabels();
    QMap<int, ButtonModel*> getButtons();
    QMap<int, SliderModel*> getSliders();
    QMap<int, LabelModel*> getLabels();
    QPushButton* getButtonStopAll();
    QToolBar* getToolBar();
    QStatusBar* getStatusBar();
    QAction* getActionRun();
    QAction* getActionEnableAI();
    QAction* getActionLoadConfig();
    QAction* getActionSaveConfig();
    QAction* getActionReset();
    GraphicsView* getControlView();
    ~MainWindow();

private:
    Ui::MainWindow *ui;

signals:
    void closeWindow();
};
#endif // MAINWINDOW_H
