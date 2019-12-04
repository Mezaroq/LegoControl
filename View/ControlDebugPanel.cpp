#include "ControlDebugPanel.h"
#include "ui_controldebugpanel.h"

ControlDebugPanel::ControlDebugPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControlDebugPanel)
{
    ui->setupUi(this);
    setWindowTitle("Lego Control Debug Panel");
    ui->currentIDLineEdit->setText("UNDEFINED");
}

void ControlDebugPanel::setRails(QMap<int, ControlRail *> rails)
{
    this->rails = rails;
}

void ControlDebugPanel::setTrains(QMap<int, ControlTrain *> trains)
{
    this->trains = trains;
}

void ControlDebugPanel::setSensors(QMap<int, ControlSensor *> sensors)
{
    this->sensors = sensors;
    createSensorsConnections();
}

void ControlDebugPanel::createRailsConnections()
{

}

void ControlDebugPanel::createTrainsConnections()
{

}

void ControlDebugPanel::createSensorsConnections()
{
    connect(ui->s11, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_1), SLOT(debugSignalTrue()));
    connect(ui->s21, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_2), SLOT(debugSignalTrue()));
    connect(ui->s31, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_3), SLOT(debugSignalTrue()));
    connect(ui->s41, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_4), SLOT(debugSignalTrue()));
    connect(ui->s51, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_5), SLOT(debugSignalTrue()));
    connect(ui->s61, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_6), SLOT(debugSignalTrue()));
    connect(ui->s71, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_7), SLOT(debugSignalTrue()));
    connect(ui->s81, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_8), SLOT(debugSignalTrue()));
    connect(ui->s91, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_9), SLOT(debugSignalTrue()));
    connect(ui->s101, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_10), SLOT(debugSignalTrue()));
    connect(ui->s111, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_11), SLOT(debugSignalTrue()));
    connect(ui->s121, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_12), SLOT(debugSignalTrue()));
    connect(ui->s131, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_13), SLOT(debugSignalTrue()));
    connect(ui->s141, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_14), SLOT(debugSignalTrue()));
    connect(ui->s151, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_15), SLOT(debugSignalTrue()));
    connect(ui->s161, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_16), SLOT(debugSignalTrue()));
    connect(ui->s171, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_17), SLOT(debugSignalTrue()));
    connect(ui->s181, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_18), SLOT(debugSignalTrue()));
    connect(ui->s191, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_19), SLOT(debugSignalTrue()));
    connect(ui->s201, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_20), SLOT(debugSignalTrue()));
    connect(ui->s211, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_21), SLOT(debugSignalTrue()));
    connect(ui->s221, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_22), SLOT(debugSignalTrue()));
    connect(ui->s231, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_23), SLOT(debugSignalTrue()));
    connect(ui->s241, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_24), SLOT(debugSignalTrue()));
    connect(ui->s251, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_25), SLOT(debugSignalTrue()));
    connect(ui->s261, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_26), SLOT(debugSignalTrue()));
    connect(ui->s271, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_27), SLOT(debugSignalTrue()));
    connect(ui->s281, SIGNAL(clicked()), sensors.value(ControlSensor::SENSOR_28), SLOT(debugSignalTrue()));
}

ControlDebugPanel::~ControlDebugPanel()
{
    delete ui;
}

void ControlDebugPanel::on_trainSetButton_clicked()
{
    rails.value(ui->railIDComboBox->currentIndex())->setTrain(trains.value(ui->trainIDComboBox->currentIndex()));
    ui->currentIDLineEdit->setText(QString("TRAIN_") + QString::number(rails.value(ui->railIDComboBox->currentIndex())->getTrain()->getTrainID() + 1));
}

void ControlDebugPanel::on_trainRemoveButton_clicked()
{
    rails.value(ui->railIDComboBox->currentIndex())->getTrain(true);
    ui->currentIDLineEdit->setText("UNDEFINED");
}

void ControlDebugPanel::on_trainRemoveAllButton_clicked()
{
    for (ControlRail *rail : rails) {
        rail->getTrain(true);
    }
    ui->currentIDLineEdit->setText("UNDEFINED");
}

void ControlDebugPanel::on_railIDComboBox_currentIndexChanged(int index)
{
    ControlTrain *train = rails.value(index)->getTrain();
    if (train) {
        ui->currentIDLineEdit->setText(QString("TRAIN_") + QString::number(train->getTrainID() + 1));
    } else {
        ui->currentIDLineEdit->setText("UNDEFINED");
    }
}
