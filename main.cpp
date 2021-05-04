#include "MainWindow.h"

#include <QApplication>
#include <QThread>

#include "Starter.h"
#include "CoreGlobals.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CoreGlobals::app = &a;

    MainWindow w;

    Starter::runStarter(QThread::currentThread());

    w.show();
    return a.exec();
}
