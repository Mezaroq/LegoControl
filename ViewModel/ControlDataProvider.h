#ifndef CONTROLDATAPROVIDER_H
#define CONTROLDATAPROVIDER_H

#define GET_BIT(k, n)     (k &   (1 << (n)))
#include <QObject>
#include <QByteArray>
#include <QSerialPort>
#include <QDebug>

class ControlDataProvider : public QObject
{
    Q_OBJECT
public:
    ControlDataProvider(QObject *parent = nullptr);
    void setSerialPort(QSerialPort* serialPort);
    void readDataFromSerialDevice();
    void sendDataToSerialDevice(QByteArray dataToSerialDevice);

private:
    static const int DATA_SIZE = 4;
    static const int SENSORS = 32;
    QSerialPort *serialPort = nullptr;
    QByteArray dataFromSerialDeviceBuffer;
    QByteArray dataFromSerialDevice;

signals:
    void dataFromSerialDeviceReady(QByteArray dataFromSerialDevice);

public slots:
    void dataToSerialDeviceReady(QByteArray dataToSerialDevice);
    void dataFromDeviceReadyRead();
};

#endif // CONTROLDATAPROVIDER_H
