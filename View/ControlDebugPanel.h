#ifndef CONTROLDEBUGPANEL_H
#define CONTROLDEBUGPANEL_H

#include <QDialog>
#include <QPushButton>
#include <QComboBox>
#include <Model/ControlSensor.h>
#include <Model/ControlTrain.h>
#include <Model/ControlRail.h>
#include <QMap>

namespace Ui {
class ControlDebugPanel;
}

class ControlDebugPanel : public QDialog
{
    Q_OBJECT
public:
    explicit ControlDebugPanel(QWidget *parent = nullptr);
    void setRails(QMap<int, ControlRail*> rails);
    void setTrains(QMap<int, ControlTrain*> trains);
    void setSensors(QMap<int, ControlSensor*> sensors);
    void createRailsConnections();
    void createTrainsConnections();
    void createSensorsConnections();
    ~ControlDebugPanel();

private slots:
    void on_trainSetButton_clicked();
    void on_trainRemoveButton_clicked();

    void on_trainRemoveAllButton_clicked();

    void on_railIDComboBox_currentIndexChanged(int index);

private:
    Ui::ControlDebugPanel *ui;
    QMap<int, ControlRail*> rails;
    QMap<int, ControlTrain*> trains;
    QMap<int, ControlSensor*> sensors;
};

#endif // CONTROLDEBUGPANEL_H
