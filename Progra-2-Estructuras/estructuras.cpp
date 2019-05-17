#include "estructuras.h"
#include <QtDebug>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

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
