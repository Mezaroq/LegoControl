#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Model/ControlLabel.h>
#include <Model/ControlSlider.h>
#include <Model/ControlButton.h>
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
    QMap<qint8, ControlButton*> getButtons();
    QMap<qint8, ControlSlider*> getSliders();
    QMap<qint8, ControlLabel*> getLabels();
    QToolBar* getToolBar();
    QAction* getActionRun();
    QAction* getActionEnableAI();
    QAction* getActionApplicationSettings();
    ControlView* getControlView();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
