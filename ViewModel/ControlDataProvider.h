#ifndef CONTROLDATAPROVIDER_H
#define CONTROLDATAPROVIDER_H

#include <QObject>
#include <QByteArray>
#include <QSerialPort>
#include <QThread>
#include <QDebug>

class ControlDataProvider : public QThread
{
    Q_OBJECT
public:
    ControlDataProvider(QObject *parent = nullptr);
    void run() override;
    void setSerialPort(QSerialPort* serialPort);
    void readDataFromSerialDevice();
    void sendDataToSerialDevice();

private:
    static const int READ_DATA_SIZE = 32;
    QSerialPort *serialPort = nullptr;
    char dataFromSerialDevice[READ_DATA_SIZE];
    QByteArray dataToSerialDevice;

signals:
    void dataFromSerialDeviceReady(QByteArray dataFromSerialDevice);

public slots:
    void dataToSerialDeviceReady(QByteArray dataToSerialDevice);
};

#endif // CONTROLDATAPROVIDER_H
