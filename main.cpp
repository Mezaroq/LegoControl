#include <ViewModel/ControlProvider.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ControlProvider p;

    return a.exec();
}
