#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <QString>

struct Persona{
    int id;
    QString nombre;
    QString apellido;
    QString pais;
    QString continente
    QString creencia;
    QString profesion;
    QString correo;
    //Falta:
    //lo de la fecha de nacimiento
    //Los arrays o listas de pecados y buenas acciones
    //lista de hijos
    Persona(int pId,QString pNom,QString pApell,QString continente,QString pPais,QString pCreencia,QString pProf,QString pCorreo){
        id=pId;
        nombre=pNom;
        apellido=pApell;
        pais=pPais;
        creencia=pCreencia;
        profesion=pProf;
        correo=pCorreo;
    }
    Persona(){
    }
};

struct Mundo{
    QString paises[100];
    QString nombre[1000];
    QString apellidos[1000];
    QString continentes[5];

    Mundo(){

    }

    void lectura(QString array[]);
};

#endif // ESTRUCTURAS_H
