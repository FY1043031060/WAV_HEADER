#include <QCoreApplication>
#include <WaveHeader.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    WaveHeader s;
    s.func();
    return a.exec();
}
