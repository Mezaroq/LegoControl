#ifndef TRAFFICMANAGERBUTTONMODEL_H
#define TRAFFICMANAGERBUTTONMODEL_H

#include <QPushButton>

class TrafficManagerButtonModel : public QPushButton
{
    Q_OBJECT
public:
    enum ButtonCategory{
        BUTTON_GENERAL,
        BUTTON_TRAIN_1,
        BUTTON_TRAIN_2,
        BUTTON_TRAIN_3
    };
    enum ButtonType{
        NORMAL_SPEED_INCREASE,
        NORMAL_SPEED_DECREASE,
        SLOWDOWN_SPEED_INCREASE,
        SLOWDOWN_SPEED_DECREASE,
        START_SPEED_INCREASE,
        START_SPEED_DECREASE,
        PRIORITY_INCREASE,
        PRIORITY_DECREASE,
        WAITING_TIME_INCREASE,
        WAITING_TIME_DECREASE,
        CENTRAL_STATION,
        NORTH_STATION,
        SOUTH_STATION,
        DIRECTION_BUTTON,
        INVERSE_SPEED
    };
    explicit TrafficManagerButtonModel(QWidget *parent = nullptr);
    void setButtonType(ButtonType buttonType);
    void setButtonCategory(ButtonCategory buttonCategory);
    static int getButtonIndex(ButtonCategory buttonCategory, ButtonType buttonType);

private:
    ButtonType buttonType;
    ButtonCategory buttonCategory;

signals:
    void managerButtonClicked(TrafficManagerButtonModel::ButtonCategory, TrafficManagerButtonModel::ButtonType, bool);

public slots:
    void buttonClicked(bool state);

};

#endif // TRAFFICMANAGERBUTTONMODEL_H
