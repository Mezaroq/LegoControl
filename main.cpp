#include <ViewModel/MainProvider.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainProvider p;

    return a.exec();
}
