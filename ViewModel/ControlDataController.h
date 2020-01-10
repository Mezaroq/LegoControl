#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H

#define GET_BIT(k, n) (k & (1 << (n)))
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDataStream>

class ControlDataController : public QObject
{
    Q_OBJECT
public:
    explicit ControlDataController(QObject *parent = nullptr);
    ~ControlDataController();
    void connectController();

private:
    const int DATA_SIZE = 4;
    const int SENSORS = 32;
    QSerialPort *sender = nullptr; //one plate: controller
    QSerialPort *receiver = nullptr;//one plate: remove

signals:
    void controllerConnected();
    void receiverSignal(); //one plate: remove
    void sensorsData(QByteArray);//one plate: controllerData

public slots:
    void senderReady(); //one plate: controllerReady
    void receiverReady(); //one plate: remove
    void sendData(QByteArray data);
};

#endif // DATACONTROLLER_H
