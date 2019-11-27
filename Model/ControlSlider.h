#ifndef CONTROLSLIDER_H
#define CONTROLSLIDER_H

#include <Model/ControlLabel.h>
#include <QSlider>

class ControlSlider : public QSlider
{
    Q_OBJECT
public:
    explicit ControlSlider(QWidget *parent = nullptr);
    void setID(qint32 id);
    void setLabel(ControlLabel *label);

private:
    qint32 ID;
    ControlLabel *label = nullptr;

signals:
    void controlValueChanged(qint32 id, int value);

public slots:
    void sliderValueChanged(int value);
};

#endif // CONTROLSLIDER_H
