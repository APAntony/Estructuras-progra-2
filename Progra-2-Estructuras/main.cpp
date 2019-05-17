#include "mainwindow.h"
#include <QApplication>

#include "estructuras.h"
//#include <QtCore>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Persona *p = new Persona();
    QString lol;
    p->obtenerHora(lol);

    return a.exec();
}
