#include "ControlDataProvider.h"

ControlDataProvider::ControlDataProvider(QObject *parent) : QThread(parent)
{

}

void ControlDataProvider::run()
{
    while (isRunning()) {
        readDataFromSerialDevice();
        msleep(1);
    }
}

void ControlDataProvider::setSerialPort(QSerialPort *serialPort)
{
    this->serialPort = serialPort;
}

void ControlDataProvider::readDataFromSerialDevice()
{
//    qDebug() << "emit readDataFromSerialDeviceReady()";
//    QByteArray array;
//    emit dataFromSerialDeviceReady(array);

    //istnieje opcja aby zrobic dataProvider jako Object i w nim utworzyć wątek, przenieść dataProvider do wątku, następnie utworzyc connect z serial readyRead() i tutaj zrobić odczyt
    //nastęnie trzeba sprawdzić dane na microcontrollerze jak one sa wysylane i odbierane bo trzeba zrobic optmalizacje

    if (serialPort->read(dataFromSerialDevice, READ_DATA_SIZE) >= READ_DATA_SIZE)
        emit dataFromSerialDeviceReady(dataFromSerialDevice);
}

void ControlDataProvider::sendDataToSerialDevice()
{
//    qDebug() << "sendDataToSerialDevice()";
    if (dataToSerialDevice.size())
        serialPort->write(dataToSerialDevice);
}

void ControlDataProvider::dataToSerialDeviceReady(QByteArray dataToSerialDevice)
{
    this->dataToSerialDevice = dataToSerialDevice;
    sendDataToSerialDevice();
}
