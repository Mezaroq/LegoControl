#ifndef CONTROLBUTTON_H
#define CONTROLBUTTON_H

#include <QPushButton>

class ControlButton : public QPushButton
{
public:
    ControlButton(QWidget *parent = nullptr);
    void setID(qint32 id);

private:
    qint32 ID;
};

#endif // CONTROLBUTTON_H
