#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <QString>
#include <QDate>
#include <QVector>
#include <string>
#include <cstdlib>
#include <QDebug>

using namespace std;

struct ListaPersonas;
struct Persona;

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

    void insertarPersona(Persona*);
    Persona buscarPersona(int);
    QString imprimir();
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


struct Mundo{
    QString paises[100];
    QString nombres[1000];
    QString apellidos[1000];
    QString profesiones[50];
    QString creencias[10];
    ListaPersonas *lista;
    QVector<int> ids;

    Mundo() {
        //qDebug()<<"estoy sirviendo1";
        lectura(paises, "paises.txt");
        lectura(nombres, "nombres.txt");
        lectura(apellidos, "apellidos.txt");
        lectura(profesiones, "profesiones.txt");
        lectura(creencias, "creencias.txt");
        lista = new ListaPersonas();

        crearPersonas();
    }

    void lectura(QString array[], string url);
    void crearPersonas();
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
    }

    NodoHeap(QString id) {
        this->identificacion = id;
        sumapecados = 0;
    }

    void agregarPersona(Persona *person) {
        familia->insertarPersona(person);
        for (int pecado : person->pecados) {
         sumapecados += pecado;
        }
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
    void insertarNuevo(QString familia_continente, Persona *person);
    void insertar(Persona *person);
    int hijoMin(int i);
    NodoHeap* buscarFamilia(QString apellido_pais);
    int buscarUbiacion(QString apellido_pais);
    NodoHeap* eliminarMin();
    void construirMonticulo(QVector<NodoHeap*> personas);
    QString recorrer();
};

struct Infierno {
    AVL demonios[7];
};

#endif // ESTRUCTURAS_H
