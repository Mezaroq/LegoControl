#ifndef CONTROLSLIDER_H
#define CONTROLSLIDER_H

#include <QSlider>
#include <Model/ControlLabel.h>

class ControlSlider : public QSlider
{
    Q_OBJECT
public:
    enum SliderID{
        SLIDER_CHANNEL_1,
        SLIDER_CHANNEL_2,
        SLIDER_CHANNEL_3,
        SLIDER_CHANNEL_4,
        SLIDER_CHANNEL_5,
        SLIDER_CHANNEL_6,
        SLIDER_CHANNEL_7,
        SLIDER_CHANNEL_8
    };
    explicit ControlSlider(QWidget *parent = nullptr);
    void setID(int id);
    void setLabel(ControlLabel *label);

private:
    int sliderID;
    ControlLabel *label = nullptr;

public slots:
    void sliderValueChanged(int value);
};

#endif // CONTROLSLIDER_H
