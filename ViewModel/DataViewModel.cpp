#include "DataViewModel.h"

DataViewModel::DataViewModel(QObject *parent) : QObject(parent)
{

}

DataViewModel::~DataViewModel()
{
    if (controller)
        controller->close();
}

void DataViewModel::connectController(QSerialPortInfo port)
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

void DataViewModel::controllerReady()
{
    QByteArray data;
    uint32_t *buffer = reinterpret_cast<uint32_t*>(controller->readAll().data());

    for (int sensor = 0; sensor < SENSORS; sensor++) {
        if (GET_BIT(buffer[0], sensor)) {
            data[sensor] = 0;
        } else {
            data[sensor] = 1;
        }
    }

    emit sensorsData(data);
}

void DataViewModel::sendData(QByteArray data)
{
    controller->write(data);
}
