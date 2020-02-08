#ifndef CONTROLLABEL_H
#define CONTROLLABEL_H

#include <QLabel>

class LabelModel : public QLabel
{
public:
    enum LabelID{
        LABEL_CHANNEL_1,
        LABEL_CHANNEL_2,
        LABEL_CHANNEL_3,
        LABEL_CHANNEL_4,
        LABEL_CHANNEL_5,
        LABEL_CHANNEL_6,
        LABEL_CHANNEL_7,
        LABEL_CHANNEL_8
    };
    explicit LabelModel(QWidget *parent = nullptr);
    void setID(int id);

private:
    int labelID;
};

#endif // CONTROLLABEL_H
