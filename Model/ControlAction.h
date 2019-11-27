#ifndef CONTROLACTION_H
#define CONTROLACTION_H

#include <QAction>

class ControlAction : public QAction
{
public:
    ControlAction(const QIcon &icon, const QString &text, QObject *parent = nullptr);
    void setID(qint32 id);

private:
    qint32 ID;
};

#endif // CONTROLACTION_H
