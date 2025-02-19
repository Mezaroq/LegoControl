#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H

#define GET_BIT(byte, bit) (byte & (1 << (bit)))
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

class DataViewModel : public QObject
{
    Q_OBJECT
public:
    explicit DataViewModel(QObject *parent = nullptr);
    ~DataViewModel();
    void connectController(QSerialPortInfo port);
    void sendData(QByteArray data);

private:
    const int DATA_SIZE = 4;
    const int SENSORS = 32;
    QByteArray data;
    uint32_t *buffer;
    QSerialPort *controller = nullptr;

signals:
    void controllerConnected();
    void sensorsData(QByteArray);

public slots:
    void controllerReady();
};

#endif // DATACONTROLLER_H
