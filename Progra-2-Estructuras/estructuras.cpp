#include "estructuras.h"
#include <QtDebug>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

void Persona::obtenerHora(QString hora){
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[128];
    strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
    hora.fromLatin1(output, 128);                   //Intentando pasar a QString
    qDebug()<< hora;
}

void ListaPersonas::insertarPersona(Persona persona){
	if(primerNodo==nullptr){
		primerNodo==ultimoNodo==new NodoPersona(persona);
	}
	else{
		ultimoNodo->siguiente=new NodoPersona(persona);
		ultimoNodo=ultimoNodo->siguiente;
	}
}

void Mundo::lectura(QString array[]) {
    ifstream archivo;
    string texto;
    QString txt;

    archivo.open("455-nombres.txt", ios::in);  //Se abre el archivo en modo lectura.

    if(archivo.fail()) {
        qDebug()<<"No se pudo abrir el programa";
        exit(1);
    }
    int ptr = 0;
    while (!archivo.eof()) { 		 //Mientras no sea el final del archivo
        getline(archivo, texto);   //Lee por linea
        array[ptr] = txt.fromStdString(texto);


        ptr++;
    }

    archivo.close();  //Cerramos el archivo
}
