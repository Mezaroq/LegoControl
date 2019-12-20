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
    ~ControlDataProvider();
    void setSender(QSerialPort* sender);
    void setReceiver(QSerialPort *receiver);
    void sendDataToReceiver(QByteArray data);

private:
    static const int SENDER_DATA_SIZE = 4;
    static const int SENSORS = 32;
    QByteArray dataFromSerialDeviceBuffer;
    QByteArray dataFromSerialDevice;

    /// NEW
    QByteArray dataFromSender;
    QByteArray dataFromSenderBuffer;
    QSerialPort *sender = nullptr;
    QSerialPort *receiver = nullptr;

signals:
    void dataFromSenderReady(QByteArray dataFromSerialDevice);
    void receiverReady();

public slots:
    void dataFromSenderReady();
    void dataFromReceiverReady();
};

#endif // CONTROLDATAPROVIDER_H
