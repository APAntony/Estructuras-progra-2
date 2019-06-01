#include "mainwindow.h"
#include <QApplication>

#include "estructuras.h"
#include <QtDebug>
#include <stdlib.h>
#include <string.h>
#include <fstream>

#include "smtp.h"

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
    Infierno *infi = new Infierno();

    infi->demonios[0]->insertar(p1, 0);
    infi->demonios[0]->insertar(p2, 0);
    infi->demonios[0]->insertar(p3, 0);
    infi->demonios[0]->insertar(p4, 0);
    infi->demonios[0]->insertar(p5, 0);

    //qDebug()<<arbol->listaHeap.length();
    //for (NodoHeap *z : arbol->listaHeap) {
        //qDebug()<<z->identificacion<<":"<<z->sumapecados;
    //}
    for(NodoHeap *nod : infi->demonios[0]->listaHeap) {
        qDebug()<<nod->identificacion<<":"<<nod->sumapecados;
    }


    qDebug()<<infi->demonios[0]->recorrer();
    qDebug()<<infi->consultarCantidadHumanos();
    qDebug()<<infi->consultarPromedioDePecados();
    //qDebug()<<infi->consultarMaximoDePecados();
    qDebug()<<infi->consultarDemonioPecado();
    qDebug()<<infi->consultarMasPecadoresMenosPecadores();


    qDebug()<<" ";
    qDebug()<<" ";
    qDebug()<<"Pruebas de ArbolAngeles";

    ArbolAngeles *angeles = new ArbolAngeles();
    angeles->crearAngeles(angeles->raiz, 0, 0, infi->demonios[0]);
    bool lol = angeles->raiz == nullptr;
    qDebug()<<lol;
    qDebug()<<angeles->contarNodos(angeles->raiz);


    qDebug()<<" ";
    qDebug()<<" ";

    qDebug()<<"Prueba de eliminar de listaSimple";
    ListaPersonas *lista = new ListaPersonas();
    //lista->insertarPersonaOrdenadaPorPecado(p1, 0);
    //lista->insertarPersonaOrdenadaPorPecado(p2, 0);
    //lista->insertarPersonaOrdenadaPorPecado(p3, 0);
    //lista->insertarPersonaOrdenadaPorPecado(p4, 0);
    //lista->insertarPersonaOrdenadaPorPecado(p5, 0);

    //qDebug()<<lista->imprimir();

    qDebug()<<" ";
    qDebug()<<" ";

    //NodoPersona *tmp = lista->primerNodo;
    //while(tmp != nullptr){
    //    qDebug()<<tmp->persona->pecados[0];
    //    tmp = tmp->siguiente;
    //}
    //lista->EliminarPersona(p1);

    //qDebug()<<lista->imprimir();
    //qDebug()<<arbol->buscarUbiacion("Artavia-Costa Rica");

    Mundo *m = new Mundo();
    m->crearPersonas(10000);

    infi->condenar(m->lista);

    qDebug()<<"------------------------Orgullo------------------------";
    for(NodoHeap *nod : infi->demonios[0]->listaHeap) {
        qDebug()<<nod->identificacion<<":"<<nod->sumapecados;
    }

    qDebug()<<"------------------------Envidia------------------------";
    for(NodoHeap *nod : infi->demonios[1]->listaHeap) {
        qDebug()<<nod->identificacion<<":"<<nod->sumapecados;
    }

    qDebug()<<"------------------------Ira------------------------";
    for(NodoHeap *nod : infi->demonios[2]->listaHeap) {
        qDebug()<<nod->identificacion<<":"<<nod->sumapecados;
    }

    qDebug()<<"------------------------Pereza------------------------";
    for(NodoHeap *nod : infi->demonios[3]->listaHeap) {
        qDebug()<<nod->identificacion<<":"<<nod->sumapecados;
    }

    qDebug()<<"------------------------Codicia------------------------";
    for(NodoHeap *nod : infi->demonios[4]->listaHeap) {
        qDebug()<<nod->identificacion<<":"<<nod->sumapecados;
    }

    qDebug()<<"------------------------Gula------------------------";
    for(NodoHeap *nod : infi->demonios[5]->listaHeap) {
        qDebug()<<nod->identificacion<<":"<<nod->sumapecados;
    }

    qDebug()<<"------------------------Lujuria------------------------";
    for(NodoHeap *nod : infi->demonios[6]->listaHeap) {
        qDebug()<<nod->identificacion<<":"<<nod->sumapecados;
    }


    //m->crearPersonas(5000);
    //m->crearPersonas();
    //m->crearPersonas();

    //Smtp *smtp = new Smtp("antonyartavia59@gmail.com","sbmr8520","smtp.gmail.com",465);
    //smtp->sendMail("antonyartavia59@gmail.com","antonyartavia59@gmail.com","PRUEBA",m->lista->imprimir(),nullptr);

    //qDebug()<<m->lista->imprimir();

    return a.exec();
}
