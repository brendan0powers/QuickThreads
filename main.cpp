#include <QCoreApplication>
#include <QDebug>

#include "QuickThread.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    qDebug() << "Test";

    int testVar = -123;

    QuickThread([&] () {
        qDebug() << "Lambda!" << testVar;
        testVar = 456;
    }).run();

    qDebug() << "After:" << testVar;

    return a.exec();
}
