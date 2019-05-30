#include "mainwindow.h"
#include <QApplication>

#include "estructuras.h"
#include <QtDebug>
#include <stdlib.h>
#include <string.h>
#include <fstream>

#include "email.h"
#include "smtpclient.h"
#include "emailaddress.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    Persona *p1 = new Persona(12,"Antony", "Artavia", "Costa Rica", "Cristianismo protestante",
                                  "Otaku", "antonyartavia59@gmail.com");

    Persona *p2 = new Persona(1,"Cristopher", "Mora", "Costa Rica", "Cristianismo catolico",
                                  "Friky", "cristomora@gmail.com");

    Persona *p3 = new Persona(15,"Andres", "Artavia", "Costa Rica", "Cristianismo",
                                  "Otaku", "andresartaviacr@gmail.com");

    Persona *p4 = new Persona(4,"Angie", "Garcia", "Costa Rica", "Budismo",
                                  "Modelo", "tamara677@gmail.com");

    Persona *p5 = new Persona(5,"Dillan", "Guzman", "Costa Rica", "Ninguna",
                                  "Piloto", "dilguzdias@gmail.com");


    for (int i=0; i < 7 ; i++) {
        p1->pecados[i] = 12;
    }

    for (int i=0; i < 7 ; i++) {
        p2->pecados[i] = 13;
    }

    for (int i=0; i < 7 ; i++) {
        p3->pecados[i] = 4;
    }


    for (int i=0; i < 7 ; i++) {
        p4->pecados[i] = 22;
    }


    for (int i=0; i < 7 ; i++) {
        p5->pecados[i] = 34;
    }

    ArbolHeap *arbol = new ArbolHeap();
    //arbol->insertar(p1);
    //arbol->insertar(p2);
    //arbol->insertar(p3);
    //arbol->insertar(p4);
    //arbol->insertar(p5);

    /*NodoHeap *fa1 = arbol->buscarFamilia("Artavia-America");
    NodoHeap *fa2 = arbol->buscarFamilia("Mora-America");
    NodoHeap *fa3 = arbol->buscarFamilia("Garcia-America");
    NodoHeap *fa4 = arbol->buscarFamilia("Guzman-America");

    qDebug() <<"Artavia-America";
    fa1->familia->imprimir();

    qDebug() <<"Mora-America";
    fa2->familia->imprimir();

    qDebug() <<"Garcia-America";
    fa3->familia->imprimir();

    qDebug() <<"Guzman-America";
    fa4->familia->imprimir();*/

    //qDebug()<<arbol->listaHeap.length();
    //for (int z : p1->pecados) {
    //    qDebug()<<z;
    //}
    //arbol->recorrer();

    Mundo *m = new Mundo();

    qDebug()<<m->lista->imprimir();

    return a.exec();
}
