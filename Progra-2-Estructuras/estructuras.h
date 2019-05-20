#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <QString>
#include <QDate>

struct Persona{
    int id;
    QString nombre;
    QString apellido;
    QString pais;
    QString continente;
    QString creencia;
    QString profesion;
    QString correo;
	QString fecha;
	QString hora;
    //Falta:
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
		fecha=(QDate::currentDate()).toString("dd/MM/yy");
		hora=(QTime::currentTime()).toString("hh:mm");
    }

    Persona(){
    }

    void obtenerHora(QString hora);
};

struct NodoPersona{
	Persona persona;
	NodoPersona siguiente;
	
	NodoPersona(Persona pPersona){
		persona=pPersona;
		siguiente=nullptr;
	}
	
	NodoPersona(){
	}
};

struct ListaPersonas{
	NodoPersona primerNodo;
	NodoPersona ultimoNodo;
	
	ListaPersonas(){
		primerNodo=ultimoNodo=nullptr;
	}
	
	void insertarPersona(Persona);
	Persona buscarPersona(int);
};

struct Mundo{
    QString paises[100];
    QString nombre[1000];
    QString apellidos[1000];
    QString continentes[5];

    Mundo(){

    }

    void lectura(QString array[]);
    void crearPersonas();
};



#endif // ESTRUCTURAS_H
