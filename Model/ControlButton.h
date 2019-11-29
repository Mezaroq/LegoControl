#ifndef CONTROLBUTTON_H
#define CONTROLBUTTON_H

#include <QPushButton>
#include <Model/ControlSlider.h>

class ControlButton : public QPushButton
{
    Q_OBJECT
public:
    enum ButtonID{
        BUTTON_CHANNEL_1,
        BUTTON_CHANNEL_2,
        BUTTON_CHANNEL_3,
        BUTTON_CHANNEL_4,
        BUTTON_CHANNEL_5,
        BUTTON_CHANNEL_6,
        BUTTON_CHANNEL_7,
        BUTTON_CHANNEL_8,
    };
    ControlButton(QWidget *parent = nullptr);
    void setID(int id);
    void setSlider(ControlSlider *slider);

private:
    int buttonID;
    ControlSlider *slider = nullptr;

public slots:
    void buttonClicked();
};

#endif // CONTROLBUTTON_H
