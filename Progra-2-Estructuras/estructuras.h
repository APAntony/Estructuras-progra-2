#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <QString>
#include <QDate>
#include <QVector>
#include <string>
#include <cstdlib>
#include <QDebug>

using namespace std;

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
    }

    Persona(){
    }

    void obtenerHora(QString hora);
    QString imprimir();
};

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
	
	ListaPersonas(){
        primerNodo = ultimoNodo = nullptr;
	}
	
    void insertarPersona(Persona*);
	Persona buscarPersona(int);
    QString imprimir();
};

struct Mundo{
    QString paises[100];
    QString nombres[1000];
    QString apellidos[1000];
    QString profesiones[50];
    QString creencias[10];
    ListaPersonas *lista;

    Mundo() {
        qDebug()<<"estoy sirviendo1";
        lectura(paises, "paises.txt");
        lectura(nombres, "nombres.txt");
        lectura(apellidos, "apellidos.txt");
        lectura(profesiones, "profesiones.txt");
        lectura(creencias, "creencias.txt");
        lista = new ListaPersonas();

        qDebug()<<"estoy sirviendo2";

        int ptrnombre = 0;
        int ptrcreencias = 0;
        int ptrprofesiones = 0;
        int ptrapellidos = 0;
        int ptrpaises = 0;
        int id = 0;
        QVector<int> ids;

        //int ids[9999999];

        qDebug()<<"estoy sirviendo3";

        int i = 0;
        while (i < 100) {
            qDebug()<<"estoy sirviendo while";
            ptrnombre = rand()%1000;
            ptrpaises = rand()%100;
            ptrapellidos = rand()%1000;
            ptrprofesiones = rand()%50;
            ptrcreencias = rand()%10;
            id = rand()%10000000;

            while (ids.contains(id)) {
                id = rand()%10000000;
            }

            ids.append(id);

            Persona *person = new Persona(id,nombres[ptrnombre], apellidos[ptrapellidos], paises[ptrpaises],
                                         creencias[ptrcreencias], profesiones[ptrprofesiones], "");
            if(ptrpaises < 21){
                person->continente = "Africa";
            }
            else if(ptrpaises < 41){
                person->continente = "Asia";
            }
            else if(ptrpaises < 64){
                person->continente = "Europa";
            }
            else if(ptrpaises < 86){
                person->continente = "America";
            }
            else {
                person->continente = "Africa";
            }

            lista->insertarPersona(person);
            i++;
        }
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


struct ArbolHeap {
    int tamanoActual;
    QVector<Persona> listaHeap;

    ArbolHeap(){
        tamanoActual = 0;
         Persona p = Persona(0,"nulo","","","","","");
        listaHeap.append(p);
    }

    void infiltArriba(int i);
    void infiltAbajo(int i);
    void insertar(Persona person);
    int hijoMin(int i);
    Persona eliminarMin();
    void construirMonticulo(QVector<Persona> personas);
    QString recorrer();
};

#endif // ESTRUCTURAS_H
