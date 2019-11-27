#ifndef CONTROLLABEL_H
#define CONTROLLABEL_H

#include <QLabel>

class ControlLabel : public QLabel
{
public:
    explicit ControlLabel(QWidget *parent = nullptr);
    void setID(qint32 id);

private:
    qint32 ID;
};

#endif // CONTROLLABEL_H
