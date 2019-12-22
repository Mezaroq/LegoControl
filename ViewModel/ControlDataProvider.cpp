#include "ControlDataProvider.h"
#define GET_BIT(k, n)     (k &   (1 << (n)))

ControlDataProvider::ControlDataProvider(QObject *parent) : QObject(parent)
{

}

ControlDataProvider::~ControlDataProvider()
{
    if (sender) {
        sender->close();
    }
    if (receiver) {
        sender->close();
    }
}

void ControlDataProvider::setSender(QSerialPort *sender)
{
    this->sender = sender;
    connect(sender, SIGNAL(readyRead()), this, SLOT(dataFromSenderReady()));
}

void ControlDataProvider::setReceiver(QSerialPort *receiver)
{
    this->receiver = receiver;
    connect(receiver, SIGNAL(readyRead()), this, SLOT(dataFromReceiverReady()));
}

void ControlDataProvider::sendDataToReceiver(QByteArray data)
{
    if (receiver) {
        receiver->write(data);
    }
}

void ControlDataProvider::dataFromSenderReady()
{
    if (sender->size() >= SENDER_DATA_SIZE) {
        dataFromSender = sender->readAll();

        uint32_t *ptrData=reinterpret_cast<uint32_t*>(dataFromSender.data());

        for (int i = 0; i < SENSORS; i++) {
            if( GET_BIT(ptrData[0], i)) {
                dataFromSenderBuffer[i] = 0;
            } else {
                dataFromSenderBuffer[i] = 1;
            }
        }
        emit dataFromSenderReady(dataFromSenderBuffer);
    }
}

void ControlDataProvider::dataFromReceiverReady()
{
    receiver->clear();
    emit receiverReady();
}
