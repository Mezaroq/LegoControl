#include "ControlDataController.h"

ControlDataController::ControlDataController(QObject *parent) : QObject(parent)
{

}

ControlDataController::~ControlDataController()
{
    if (sender)
        sender->close();
    if (receiver)
        receiver->close();
//    if (controller) //one plate
//        controller->close();
}

void ControlDataController::connectController()
{
    bool senderStatus = false, receiverStatus = false;
    for (auto port : QSerialPortInfo::availablePorts()) {
        if (port.serialNumber() == "NXP-7S") { //SENDER
            sender = new QSerialPort(port);
            if (sender->open(QIODevice::ReadWrite)) {
                sender->setBaudRate(QSerialPort::Baud115200);
                sender->clear();
                connect(sender, SIGNAL(readyRead()), this, SLOT(senderReady()));
                senderStatus = true;
            }
        } else if (port.serialNumber() == "NXP-77") { //RECEIVER
            receiver = new QSerialPort(port);
            if (receiver->open(QIODevice::ReadWrite)) {
                receiver->setBaudRate(QSerialPort::Baud115200);
                receiver->clear();
                connect(receiver, SIGNAL(readyRead()), this, SLOT(receiverReady()));
                receiverStatus = true;
            }
        }
    }
    if (senderStatus & receiverStatus) {
        emit controllerConnected();
    }
}

void ControlDataController::senderReady()
{
    QByteArray data;
    uint32_t *buffer = reinterpret_cast<uint32_t*>(sender->read(DATA_SIZE).data());

    for (int sensor = 0; sensor < SENSORS; sensor++) {
        if (GET_BIT(buffer[0], sensor)) {
            data[sensor] = 0;
        } else {
            data[sensor] = 1;
        }
    }

    emit sensorsData(data);
}

void ControlDataController::receiverReady()
{
    receiver->clear();
    emit receiverSignal();
}

void ControlDataController::sendData(QByteArray data)
{
    receiver->write(data);
}
