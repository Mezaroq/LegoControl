#include "ControlDataProvider.h"
#define GET_BIT(k, n)     (k &   (1 << (n)))

ControlDataProvider::ControlDataProvider(QObject *parent) : QObject(parent)
{

}

void ControlDataProvider::setSerialPort(QSerialPort *serialPort)
{
    this->serialPort = serialPort;
    connect(serialPort, SIGNAL(readyRead()), this, SLOT(dataFromDeviceReadyRead()));
}

void ControlDataProvider::sendDataToSerialDevice(QByteArray dataToSerialDevice)
{
    serialPort->write(dataToSerialDevice);
}

void ControlDataProvider::dataToSerialDeviceReady(QByteArray dataToSerialDevice)
{
    sendDataToSerialDevice(dataToSerialDevice);
}

void ControlDataProvider::dataFromDeviceReadyRead()
{
    if (serialPort->size() >= DATA_SIZE) {
        dataFromSerialDevice = serialPort->readAll();
        uint32_t *ptrData=reinterpret_cast<uint32_t*>(dataFromSerialDevice.data());

        dataFromSerialDeviceBuffer[0] = bool(GET_BIT(ptrData[0], 10));

        for (int i = 0; i < SENSORS; i++) {
            if( GET_BIT(ptrData[0], i)) {
                dataFromSerialDeviceBuffer[i] = 1;
            } else {
                dataFromSerialDeviceBuffer[i] = 0;
            }
        }

        emit dataFromSerialDeviceReady(dataFromSerialDeviceBuffer);
    }
}
