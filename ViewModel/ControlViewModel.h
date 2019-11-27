#ifndef CONTROLVIEWMODEL_H
#define CONTROLVIEWMODEL_H

#include <QObject>
#include <Model/ControlLabel.h>

class ControlViewModel : public QObject
{
    Q_OBJECT
public:
    enum Switches{
        SWITCH1 = 1,
        SWITCH2,
        SWITCH3,
        SWITCH4,
        SWITCH5,
        SWITCH6,
        SWITCH7,
        SWITCH8,
        SWITCH9
    };
    enum Lights{
        LIGHT1 = SWITCH9 + 1,
        LIGHT2,
        LIGHT3,
        LIGHT4,
        LIGHT5,
        LIGHT6,
        LIGHT7,
        LIGHT8,
        LIGHT9,
        LIGHT10,
        LIGHT11,
        LIGHT12,
        LIGHT13,
        LIGHT14,
        LIGHT15,
        LIGHT16,
        LIGHT17,
        LIGHT18,
        LIGHT19,
        LIGHT20,
        LIGHT21
    };

    enum Buttons{
        BUTTON_CHANNEL_1 = 1,
        BUTTON_CHANNEL_2,
        BUTTON_CHANNEL_3,
        BUTTON_CHANNEL_4,
        BUTTON_CHANNEL_5,
        BUTTON_CHANNEL_6,
        BUTTON_CHANNEL_7,
        BUTTON_CHANNEL_8,
        BUTTON_STOP_ALL,
    };
    enum Sliders{
        SLIDER_CHANNEL_1 = 1,
        SLIDER_CHANNEL_2,
        SLIDER_CHANNEL_3,
        SLIDER_CHANNEL_4,
        SLIDER_CHANNEL_5,
        SLIDER_CHANNEL_6,
        SLIDER_CHANNEL_7,
        SLIDER_CHANNEL_8
    };
    enum Labels{
        LABEL_CHANNEL_1 = 1,
        LABEL_CHANNEL_2,
        LABEL_CHANNEL_3,
        LABEL_CHANNEL_4,
        LABEL_CHANNEL_5,
        LABEL_CHANNEL_6,
        LABEL_CHANNEL_7,
        LABEL_CHANNEL_8
    };
    explicit ControlViewModel(QObject *parent = nullptr);

signals:

public slots:
};

#endif // CONTROLVIEWMODEL_H
