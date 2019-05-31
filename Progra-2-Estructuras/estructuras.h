#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <QString>
#include <QDate>
#include <QVector>
#include <string>
#include <cstdlib>
#include <QDebug>
#include "math.h"

using namespace std;

struct ListaPersonas;
struct Persona;
struct NodoPecado;
struct ListaPecados;

struct NodoPersona{
    Persona *persona;
    NodoPersona *siguiente;

    NodoPersona(Persona *pPersona){
        persona = pPersona;
        siguiente=nullptr;
    }

    NodoPersona(){
    }
};

struct ListaPersonas{
    NodoPersona *primerNodo;
    NodoPersona *ultimoNodo;
    int contNodos;

    ListaPersonas(){
        primerNodo = ultimoNodo = nullptr;
        contNodos = 0;
    }

    void insertarPersonaOrdenada(Persona*);
    Persona buscarPersona(int);
    QString imprimir();
    void eliminarPrimero();
};

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
    Persona *padre;
    ListaPersonas *hijos;
    int pecados[7] = {0,0,0,0,0,0,0};
    int buenasAcciones[7] = {0,0,0,0,0,0,0};

    Persona(int pId,QString pNom,QString pApell,QString pPais,QString pCreencia,QString pProf,QString pCorreo){
        id=pId;
        nombre=pNom;
        apellido=pApell;
        pais=pPais;
        creencia=pCreencia;
        profesion=pProf;
        correo=pCorreo;
        fecha=(QDate::currentDate()).toString("dd/MM/yy");
        hora=(QTime::currentTime()).toString("hh:mm");
        padre = nullptr;
        hijos = new ListaPersonas();
    }

    Persona(){
    }

    void obtenerHora(QString hora);
    QString imprimir();
};


struct NodoArbol{
    Persona * persona;
    NodoPersona * nodo;
    NodoArbol * izq,*der;
    NodoArbol(Persona * pPersona){
        persona=pPersona;
        nodo=nullptr;
        izq=der=nullptr;
    }
    NodoArbol(){}
};

struct ArbolBinario{
    NodoArbol * raiz;
    ArbolBinario(){
        raiz=nullptr;
    }
    void insertar(NodoPersona*);
    NodoArbol * insertar(NodoPersona*,NodoArbol*);
    void inOrden(NodoArbol*);
    void buscarProfundidad(int);
    void buscarProfundidad(int,NodoArbol*,int);
};

struct Mundo{
    QString paises[100];
    QString nombres[1000];
    QString apellidos[1000];
    QString profesiones[50];
    QString creencias[10];
    ListaPersonas *lista;
    QVector<int> ids;
    ArbolBinario * arbolMundo;

    Mundo() {
        //qDebug()<<"estoy sirviendo1";
        lectura(paises, "paises.txt");
        lectura(nombres, "nombres.txt");
        lectura(apellidos, "apellidos.txt");
        lectura(profesiones, "profesiones.txt");
        lectura(creencias, "creencias.txt");
        lista = new ListaPersonas();
        arbolMundo=new ArbolBinario();
    }

    void lectura(QString array[], string url);
    void crearPersonas(int cantidad);
    void generarArbol();
};


// Clase NodoAVL de Arbol AVL:
struct NodoAVL {
   Persona *persona;
   int FE;
   NodoAVL *padre;
   NodoAVL *izquierdo;
   NodoAVL *derecho;

   friend struct AVL;

    NodoAVL(Persona *per, NodoAVL *pad=nullptr, NodoAVL *izq=nullptr, NodoAVL *der=nullptr) :
     persona(per), FE(0), padre(pad), izquierdo(izq), derecho(der) {

    }
};

struct AVL {
public: NodoAVL *raiz;
  private:
   enum {IZQUIERDO, DERECHO};
   // Punteros de la lista, para cabeza y NodoAVL actual:

   NodoAVL *actual;
   int contador;
   int altura;

  public:
   // Constructor y destructor básicos:
   AVL() : raiz(nullptr), actual(nullptr) {}
   ~AVL() { Podar(raiz); }

   // Insertar en árbol ordenado:
   void Insertar(Persona *per);

   // Borrar un elemento del árbol:
   void Borrar(int dat);

   // Función de búsqueda:
   bool Buscar(const int dat);

   //Buscar un dato(NodoAVL) en especifica
   NodoAVL* BuscarNodoAVL(const int dat);

   // Comprobar si el árbol está vacío:
   bool Vacio(NodoAVL *r) {
        return r==nullptr;
   }

   // Comprobar si es un NodoAVL hoja:
   bool EsHoja(NodoAVL *r) {
        return !r->derecho && !r->izquierdo;
   }

   // Contar número de NodoAVLs:
   int NumeroNodoAVLs();
   int AlturaArbol();

   // Calcular altura de un dato:
   int Altura(const int dat);

   // Devolver referencia al dato del NodoAVL actual:
   int &ValorActual() {
       return actual->persona->id;
   }

   // Moverse al NodoAVL raiz:
   void Raiz() { actual = raiz; }

   // Aplicar una función a cada elemento del árbol:
   void InOrden(void (*func)(QString, int) , NodoAVL *NodoAVL=nullptr, bool r=true);
   void PreOrden(void (*func)(QString, int) , NodoAVL *NodoAVL=nullptr, bool r=true);
   void PostOrden(void (*func)(QString, int) , NodoAVL *NodoAVL=nullptr, bool r=true);

  private:
   // Funciones de equilibrado:
   void Equilibrar(NodoAVL *NodoAVL, int, bool);
   void RSI(NodoAVL* NodoAVL);
   void RSD(NodoAVL* NodoAVL);
   void RDI(NodoAVL* NodoAVL);
   void RDD(NodoAVL* NodoAVL);

   // Funciones auxiliares
   void Podar(NodoAVL* &);
   void auxContador(NodoAVL*);
   void auxAltura(NodoAVL*, int);
}; void Mostrar(QString n, int FE);


struct NodoHeap {
    ListaPersonas *familia;
    QString identificacion;   //apellido-continente
    int sumapecados;

    NodoHeap(){
        sumapecados=0;
        identificacion = "";
        familia = new ListaPersonas();
    }

    NodoHeap(QString id) {
        this->identificacion = id;
        sumapecados = 0;
        familia = new ListaPersonas();
    }

    void agregarPersona(Persona *person, int pecado) {
        familia->insertarPersonaOrdenada(person);
        sumapecados += (person->pecados[pecado]-person->buenasAcciones[pecado]);

    }
};

struct ArbolHeap {
    int tamanoActual;
    QVector<NodoHeap*> listaHeap;

    ArbolHeap(){
        tamanoActual = 0;
        NodoHeap *nodoNulo = new NodoHeap();
        listaHeap.append(nodoNulo);
    }

    void infiltArriba(int i);
    void infiltAbajo(int i);
    void insertarNuevo(QString familia_continente, Persona *person, int pecado);
    void insertar(Persona *person,int pecado);
    int hijoMin(int i);
    NodoHeap* buscarFamilia(QString apellido_pais);
    int buscarUbiacion(QString apellido_pais);
    NodoHeap* eliminarMin();
    void construirMonticulo(QVector<NodoHeap*> personas);
    QString recorrer();
};

struct Infierno {
    ArbolHeap* demonios[7];

    Infierno() {
        for(int i=0; i<7; i++) {
            demonios[i] = new ArbolHeap();
        }
    }

    void condenar();
    QString consultarDemonioPecado();
    QString consultarCantidadHumanos();
    int consultarCantidadHumanosInt();
    QString consultarPromedioDePecados();
    QString consultarMaximoDePecados();
    QString consultarMinimoDePecados();
    QString consultarMasPecadoresMenosPecadores();
};

struct AngelSec {
    QString nombre;  //es uno de los nomres de la lista de ángeles
    int version;     //es el número de ese angel en esa generación
    int generacion; //es el nivel del árbol
    Persona *humano;  //es un puntero al humano que fue salvado por el ángel.

    QString nombres[10] = {"Miguel", "Nuriel", "Aniel", "Rafael", "Gabriel", "Shamsiel",
                           "Raguel", "Uriel", "Azrael", "Sariel"};

    AngelSec(int version, int generacion, ArbolHeap *personas) {
        int ptr = rand()%10;
        Persona *person = personas->listaHeap.takeAt(personas->listaHeap.length())->familia->ultimoNodo->persona;
        //
        //..........................Eliminar esa persona que se saco del infierno..........................
        //
        this->nombre = nombres[ptr];
        this->version = version;
        this->generacion = generacion;
        this->humano = person;
    }

    AngelSec() {
        humano = nullptr;
        version = generacion = 0;
        nombre = "";
    }
};

struct NodoTriario {
    NodoTriario *izq;
    NodoTriario *der;
    NodoTriario *cen;
    AngelSec *angel;

    NodoTriario(AngelSec *angel) {
        this->angel = angel;
        izq = der = cen = nullptr;
    }

    NodoTriario() {
        izq = der = cen = nullptr;
        angel = nullptr;
    }
};

struct ArbolAngeles {
    NodoTriario *raiz;

    ArbolAngeles () {
        raiz = nullptr;
    }

    void rellenarPrimerosNiveles();
    void crearAngeles(NodoTriario *raiz, int nivel, int version, ArbolHeap *infierno);
};

struct NodoArbolMundo {
    Persona *persona;
    NodoArbolMundo *izquierda;
    NodoArbolMundo *derecha;

    NodoArbolMundo() {
        persona = nullptr;
        izquierda = derecha = nullptr;
    }

    NodoArbolMundo(Persona *person) {
        persona = person;
        izquierda = derecha = nullptr;
    }
};

#endif // ESTRUCTURAS_H
