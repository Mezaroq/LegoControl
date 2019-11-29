#ifndef CONTROLVIEWMODEL_H
#define CONTROLVIEWMODEL_H

#include <QObject>
#include <Model/ControlSlider.h>
#include <Model/ControlLight.h>
#include <Model/ControlSwitch.h>
#include <QMap>
#include <QDebug>

class ControlViewModel : public QObject
{
    Q_OBJECT
public:
    explicit ControlViewModel(QObject *parent = nullptr);
    void setSliders(QMap<int, ControlSlider*> sliders);
    void setLights(QMap<int, ControlLight*> lights);
    void setSwitches(QMap<int, ControlSwitch*> switches);

private:
    QMap<int, ControlSlider*> sliders;
    QMap<int, ControlLight*> lights;
    QMap<int, ControlSwitch*> switches;

signals:

public slots:
    void stopAllChannels();
    void controlObjectClicked(ControlObject::ObjectType objectType, int objectID);
};

#endif // CONTROLVIEWMODEL_H
