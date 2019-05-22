#include "mainwindow.h"
#include <QApplication>

#include "estructuras.h"
#include <QtDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Persona p1 = Persona(12,"Antony", "Artavia", "America", "Costa Rica", "Cristianismo protestante",
                              "Otaku", "antonyartavia59@gmail.com");

    Persona p2 = Persona(1,"Cristopher", "Mora", "America", "Costa Rica", "Cristianismo catolico",
                              "Friky", "cristomora@gmail.com");

    Persona p3 = Persona(15,"Andres", "Artavia", "America", "Costa Rica", "Cristianismo",
                              "Otaku", "andresartaviacr@gmail.com");

    Persona p4 = Persona(23,"Angie", "Garcia", "America", "Costa Rica", "Budismo",
                              "Modelo", "tamara677@gmail.com");

    Persona p5 = Persona(5,"Dillan", "Guzman", "America", "Costa Rica", "Ninguna",
                              "Piloto", "dilguzdias@gmail.com");

    QVector<Persona> personas = {p1, p2, p3, p4, p5};

    ArbolHeap miMonticulo = ArbolHeap();

    miMonticulo.insertar(p1);
    miMonticulo.insertar(p2);
    miMonticulo.insertar(p3);
    miMonticulo.insertar(p4);
    miMonticulo.insertar(p5);
    miMonticulo.insertar(p1);

    //miMonticulo.construirMonticulo(personas);

    qDebug() << miMonticulo.recorrer();

    qDebug()<<"";

    //qDebug()<< miMonticulo.eliminarMin().nombre;
    //qDebug()<< miMonticulo.eliminarMin().nombre;
    //qDebug()<< miMonticulo.eliminarMin().nombre;
    //qDebug()<< miMonticulo.eliminarMin().nombre;
    //qDebug()<< miMonticulo.eliminarMin().nombre;


    return a.exec();
}
