#include "ControlDebugger.h"
#include "ui_controldebugger.h"

ControlDebugger::ControlDebugger(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControlDebugger)
{
    ui->setupUi(this);
    setWindowTitle("Debugger");
    setWindowFlag(Qt::WindowContextHelpButtonHint,false);
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    trainTable = ui->trainTable;
    railTable = ui->railTable;
    timetableTable = ui->timetableTable;
    switchTable = ui->switchTable;

    timerThread = new QThread(this);
    debuggerTimer = new QTimer();
    debuggerTimer->setInterval(50);
    debuggerTimer->moveToThread(timerThread);

    connect(railTable, SIGNAL(cellClicked(int, int)), this, SLOT(sensorClicked(int, int)));
    connect(switchTable, SIGNAL(cellClicked(int, int)), this, SLOT(switchClicked(int, int)));
    connect(timetableTable, SIGNAL(cellClicked(int, int)), this, SLOT(timetableClicked(int, int)));
    connect(debuggerTimer, SIGNAL(timeout()), this, SLOT(debuggerLoop()));
    connect(timerThread, SIGNAL(started()), debuggerTimer, SLOT(start()));
    setMenu();
}

void ControlDebugger::setMenu()
{
    for (int i = 0; i < ControlTrain::TRAIN_8 + 1; i++) {
        ui->trainComboBox->insertItem(i, QString("TRAIN_") + QString::number(i+1));
    }

    for (int i = 0; i < ControlRail::RAIL_SECTION_10 + 1; i++) {
        ui->railComboBox->insertItem(i, QString("RAIL_") + QString::number(i+1));
    }
}

ControlDebugger::~ControlDebugger()
{
    delete ui;
}

void ControlDebugger::update()
{
    int row = 0;
    for (ControlTrain *train : trains) {
        trainTable->item(row, TRAIN_ID)->setText( getTrainID(train->getTrainID()) );
        trainTable->item(row, TRAIN_PRIORITY)->setText( getTrainPriority(train) );
        trainTable->item(row, TRAIN_WAITING)->setText( train->isWaiting() ? QString("TRUE") : QString("FALSE") );
        trainTable->item(row, TRAIN_SPEED)->setText( QString::number(train->getTrainSpeed()) );
        row++;
    }

    row = 0;
    int sensorID = 1;
    for (ControlRail *rail : rails) {
        railTable->item(row, RAIL_ID)->setText( getRailID(rail->getRailID()) );
        railTable->item(row, RAIL_COUNTER)->setText( QString::number(rail->getEntryCounter()) );
        railTable->item(row, RAIL_RESERVATION)->setText( rail->isReserved() ? QString("TRUE") : QString("FALSE") );
        railTable->item(row, RAIL_TRAIN_ID)->setText( getTrainIDfromRail(rail->getTrain()) );
        railTable->item(row, RAIL_TRAIN_FROM)->setText( getTrainFrom(rail->getTrainFrom()) );
        if ( (row != 3) && (row != 6) && (row != 9)) {
            railTable->item(row, RAIL_SENSOR_ENTRY_LAST)->setText( getSensorID(ControlSensor::SensorID(sensorID++)) );
            railTable->item(row, RAIL_SENSOR_STOP_LAST)->setText( getSensorID(ControlSensor::SensorID(sensorID++)) );
            railTable->item(row, RAIL_SENSOR_ENTRY_NEXT)->setText( getSensorID(ControlSensor::SensorID(sensorID++)) );
            railTable->item(row, RAIL_SENSOR_STOP_NEXT)->setText( getSensorID(ControlSensor::SensorID(sensorID++)) );
        }
        row++;
    }

    row = 0;
    for (ControlSwitch *cswitch : switches) {
        switchTable->item(row, SWITCH_ID)->setText( getSwitchID(cswitch->getSwitchID()) );
        switchTable->item(row, SWITCH_TOGGLE)->setText( cswitch->getSwitchToggle() ? "TOGGLED" : "NORMAL" );
        switchTable->item(row, SWITCH_RESERVATION)->setText( cswitch->isReserved() ? "TRUE" : "FALSE" );
        row++;
    }

    row = 0;
    for (ControlTimetable *timetable : *timetables) {
        timetableTable->item(row, TIMETABLE_ID)->setText( QString::number(timetable->getConnectionID()) );
        timetableTable->item(row, TIMETABLE_TRAIN_ID)->setText( getTrainID(timetable->getTrainID()) );
        timetableTable->item(row, TIMETABLE_CURRENT_RAIL_ID)->setText( getRailID(timetable->getCurrentRailID()) );
        timetableTable->item(row, TIMETABLE_DESTINATION_RAIL_ID)->setText( getRailID(timetable->getDestinationRailID()) );
        timetableTable->item(row, TIMETABLE_TRAIN_DIRECTION)->setText( timetable->getDirection() == 1 ? "FORWARD" : "REVERSE" );
        timetableTable->item(row, TIMETABLE_CURRENT_LOOP)->setText( getTimetableLoop(ControlTimetable::Loop(timetable->getCurrentLoop())) );
        timetableTable->item(row, TIMETABLE_MAX_LOOP)->setText( getTimetableLoop(timetable->getLoop()) );
        timetableTable->item(row, TIMETABLE_LOOP_COUNTER)->setText( QString::number(timetable->getLoopCounter()) );
        timetableTable->item(row, TIMETABLE_IGNORE_FLAG)->setText( timetable->isIgnoreTrain() ? QString("TRUE") : QString("FALSE") );

        for (ControlRail *rail : rails) {
            if (rail->getTrain()) {
                if (rail->getTrain()->getTrainID() == timetable->getTrainID()) {
                    timetable->setCurrentRailID(rail->getRailID());
                    break;
                }
            }
        }
        row++;
    }
}

void ControlDebugger::setDebuggerData()
{
    int row = 0;
    for (ControlTrain *train : trains) {
        trainTable->setItem(row, TRAIN_ID, new QTableWidgetItem( getTrainID(train->getTrainID()) ));
        trainTable->setItem(row, TRAIN_PRIORITY, new QTableWidgetItem( getTrainPriority(train) ));
        trainTable->setItem(row, TRAIN_WAITING, new QTableWidgetItem( train->isWaiting() ? QString("TRUE") : QString("FALSE") ));
        trainTable->setItem(row, TRAIN_SPEED, new QTableWidgetItem( QString::number(train->getTrainSpeed()) ));

        trainTable->item(row, TRAIN_ID)->setTextAlignment(Qt::AlignCenter);
        trainTable->item(row, TRAIN_PRIORITY)->setTextAlignment(Qt::AlignCenter);
        trainTable->item(row, TRAIN_WAITING)->setTextAlignment(Qt::AlignCenter);
        trainTable->item(row, TRAIN_SPEED)->setTextAlignment(Qt::AlignCenter);
        row++;
    }

    row = 0;
    int sensorID = 1;
    for (ControlRail *rail : rails) {
        railTable->setItem(row, RAIL_ID, new QTableWidgetItem( getRailID(rail->getRailID()) ));
        railTable->setItem(row, RAIL_COUNTER, new QTableWidgetItem( QString::number(rail->getEntryCounter()) ));
        railTable->setItem(row, RAIL_RESERVATION, new QTableWidgetItem( rail->isReserved() ? QString("TRUE") : QString("FALSE") ));
        railTable->setItem(row, RAIL_TRAIN_ID, new QTableWidgetItem( getTrainIDfromRail(rail->getTrain()) ));
        railTable->setItem(row, RAIL_TRAIN_FROM, new QTableWidgetItem( getTrainFrom(rail->getTrainFrom()) ));
        if ( (row != 3) && (row != 6) && (row != 9)) {
            railTable->setItem(row, RAIL_SENSOR_ENTRY_LAST, new QTableWidgetItem( getSensorID(ControlSensor::SensorID(sensorID++)) ));
            railTable->setItem(row, RAIL_SENSOR_STOP_LAST, new QTableWidgetItem( getSensorID(ControlSensor::SensorID(sensorID++)) ));
            railTable->setItem(row, RAIL_SENSOR_ENTRY_NEXT, new QTableWidgetItem( getSensorID(ControlSensor::SensorID(sensorID++)) ));
            railTable->setItem(row, RAIL_SENSOR_STOP_NEXT, new QTableWidgetItem( getSensorID(ControlSensor::SensorID(sensorID++)) ));
        }

        railTable->item(row, RAIL_ID)->setTextAlignment(Qt::AlignCenter);
        railTable->item(row, RAIL_COUNTER)->setTextAlignment(Qt::AlignCenter);
        railTable->item(row, RAIL_RESERVATION)->setTextAlignment(Qt::AlignCenter);
        railTable->item(row, RAIL_TRAIN_ID)->setTextAlignment(Qt::AlignCenter);
        railTable->item(row, RAIL_TRAIN_FROM)->setTextAlignment(Qt::AlignCenter);
        if ( (row != 3) && (row != 6) && (row != 9)) {
            railTable->item(row, RAIL_SENSOR_ENTRY_LAST)->setTextAlignment(Qt::AlignCenter);
            railTable->item(row, RAIL_SENSOR_STOP_LAST)->setTextAlignment(Qt::AlignCenter);
            railTable->item(row, RAIL_SENSOR_STOP_NEXT)->setTextAlignment(Qt::AlignCenter);
            railTable->item(row, RAIL_SENSOR_ENTRY_NEXT)->setTextAlignment(Qt::AlignCenter);
        }
        row++;
    }

    row = 0;
    for (ControlSwitch *cswitch : switches) {
        switchTable->setItem(row, SWITCH_ID, new QTableWidgetItem( getSwitchID(cswitch->getSwitchID()) ));
        switchTable->setItem(row, SWITCH_TOGGLE, new QTableWidgetItem( cswitch->getSwitchToggle() ? "TOGGLED" : "NORMAL" ));
        switchTable->setItem(row, SWITCH_RESERVATION, new QTableWidgetItem( cswitch->isReserved() ? "TRUE" : "FALSE" ));

        switchTable->item(row, SWITCH_ID)->setTextAlignment(Qt::AlignCenter);
        switchTable->item(row, SWITCH_TOGGLE)->setTextAlignment(Qt::AlignCenter);
        switchTable->item(row, SWITCH_RESERVATION)->setTextAlignment(Qt::AlignCenter);
        row++;
    }

    for (int row = 0; row < 3; row++) {
        timetableTable->setItem(row, TIMETABLE_ID, new QTableWidgetItem());
        timetableTable->setItem(row, TIMETABLE_TRAIN_ID, new QTableWidgetItem());
        timetableTable->setItem(row, TIMETABLE_CURRENT_RAIL_ID, new QTableWidgetItem());
        timetableTable->setItem(row, TIMETABLE_DESTINATION_RAIL_ID, new QTableWidgetItem());
        timetableTable->setItem(row, TIMETABLE_TRAIN_DIRECTION, new QTableWidgetItem());
        timetableTable->setItem(row, TIMETABLE_CURRENT_LOOP, new QTableWidgetItem());
        timetableTable->setItem(row, TIMETABLE_MAX_LOOP, new QTableWidgetItem());
        timetableTable->setItem(row, TIMETABLE_LOOP_COUNTER, new QTableWidgetItem());
        timetableTable->setItem(row, TIMETABLE_IGNORE_FLAG, new QTableWidgetItem());
    }
}

void ControlDebugger::setSensors(QMap<int, ControlSensor *> sensors)
{
    this->sensors = sensors;
}

void ControlDebugger::setRails(QMap<int, ControlRail *> rails)
{
    this->rails = rails;
}

void ControlDebugger::setTrains(QMap<int, ControlTrain *> trains)
{
    this->trains = trains;
}

void ControlDebugger::setSwitches(QMap<int, ControlSwitch *> switches)
{
    this->switches = switches;
}

void ControlDebugger::setTimetables(QMap<ControlTrain::TrainID, ControlTimetable *> *timetables)
{
    this->timetables = timetables;
}

void ControlDebugger::setAI(ControlAiViewModel *ai)
{
    this->ai = ai;
}

QString ControlDebugger::getTrainPriority(ControlTrain *train)
{
    return QString("PRIORITY_") + QString::number(8-(train->getTrainPriority()));
}

QString ControlDebugger::getTrainIDfromRail(ControlTrain *train)
{
    if (train)
        return getTrainID(train->getTrainID());
    return "";
}

QString ControlDebugger::getTrainFrom(ControlRail::TrainFrom trainFrom)
{
    switch (trainFrom) {
    case ControlRail::FROM_LAST:
        return "FROM_LAST";
    case ControlRail::FROM_NEXT:
        return "FROM_NEXT";
    case ControlRail::UNDEFINED:
        return "";
    }
}

QString ControlDebugger::getTimetableLoop(ControlTimetable::Loop loop)
{
    return QString("LOOP_") + QString::number(loop);
}

QString ControlDebugger::getSensorID(ControlSensor::SensorID id)
{
    return QString("S_") + QString::number(id);
}

QString ControlDebugger::getTrainID(ControlTrain::TrainID id)
{
    return QString("TRAIN_") + QString::number(id+1);
}

QString ControlDebugger::getRailID(ControlRail::RailID id)
{
    return QString("RAIL_") + QString::number(id+1);
}

QString ControlDebugger::getSwitchID(ControlSwitch::SwitchID id)
{
    return QString("SWITCH_") + QString::number(id+1);
}

void ControlDebugger::sensorClicked(int row, int column)
{
    if (column == 2) {
        ControlRail *rail = rails.value(row);
        rail->setReservation(!rail->isReserved());
    } else {
        QTableWidgetItem *item = railTable->item(row, column);
        if (item) {
            if (item->text().contains("S_")) {
                sensors.value(item->text().remove(0, 2).toInt() - 1)->debugSignal();
            }
        }
    }
}

void ControlDebugger::switchClicked(int row, int column)
{
    if (column == 2) {
        ControlSwitch *cswitch = switches.value(row);
        cswitch->setReservation(!cswitch->isReserved());
    }
}

void ControlDebugger::timetableClicked(int row, int column)
{
    if (column == 4) {
        ControlTimetable *timetable = timetables->value(ControlTrain::TrainID(row));
        if (timetable) {
            if (timetable->getDirection() == ControlTrain::DIRECTION_FORWARD)
                timetable->setDirection(ControlTrain::DIRECTION_REVERSE);
            else
                timetable->setDirection(ControlTrain::DIRECTION_FORWARD);
        }
    }
}

void ControlDebugger::debuggerLoop()
{
    if (aiModuleIsEnabled)
        ai->run();
    update();
}

void ControlDebugger::on_debuggerButton_clicked()
{
    if (debuggerIsRunning) {
        debuggerIsRunning = !debuggerIsRunning;
        ui->debuggerInfo->setText("debugger stopped");
        timerThread->terminate();
    } else {
        debuggerIsRunning = !debuggerIsRunning;
        ui->debuggerInfo->setText("debugger running");
        timerThread->start();
    }
}

void ControlDebugger::on_insertButton_clicked()
{
    rails.value(ui->railComboBox->currentIndex())->setTrain(trains.value(ui->trainComboBox->currentIndex()));
    rails.value(ui->railComboBox->currentIndex())->setReservation(true);
}

void ControlDebugger::on_removeButton_clicked()
{
    rails.value(ui->railComboBox->currentIndex())->getTrain(true);
    rails.value(ui->railComboBox->currentIndex())->setReservation(false);
    rails.value(ui->railComboBox->currentIndex())->setTrainFrom(ControlRail::UNDEFINED);
}

void ControlDebugger::on_pushButton_toggled(bool checked)
{
    if (checked)
        ui->pushButton->setText("Disable ai module");
    else
        ui->pushButton->setText("Enable ai module");
    aiModuleIsEnabled = checked;
}
