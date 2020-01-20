#include "ControlDataController.h"

ControlDataController::ControlDataController(QObject *parent) : QObject(parent)
{

}

ControlDataController::~ControlDataController()
{
    if (controller)
        controller->close();
}

void ControlDataController::connectController(QSerialPortInfo port)
{
    if (port.vendorIdentifier() == 8137) {
        controller = new QSerialPort(port);
        if (controller->open(QIODevice::ReadWrite)) {
            controller->setBaudRate(QSerialPort::Baud115200);
            controller->clear();
            connect(controller, SIGNAL(readyRead()), this, SLOT(controllerReady()));
            emit controllerConnected();
        }
    }
}

void ControlDataController::controllerReady()
{
    QByteArray data;
    uint32_t *buffer = reinterpret_cast<uint32_t*>(controller->readAll().data());

    for (int sensor = 0; sensor < SENSORS; sensor++) {
        if (GET_BIT(buffer[0], sensor)) {
            data[sensor] = 0;
        } else {
            data[sensor] = 0;
        }
    }

//    qDebug() << data.toHex('|');
    emit sensorsData(data);
}

void ControlDataController::sendData(QByteArray data)
{
    controller->write(data);
}
