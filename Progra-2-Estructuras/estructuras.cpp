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
    if(primerNodo == nullptr){
        primerNodo = ultimoNodo = new NodoPersona(persona);
	}
	else{
        ultimoNodo->siguiente = new NodoPersona(persona);
        ultimoNodo = ultimoNodo->siguiente;
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


// Poda: borrar todos los NodoAVLs a partir de uno, incluido
void AVL::Podar(NodoAVL* &NodoAVL) {
   // Algoritmo recursivo, recorrido en postorden
   if(NodoAVL) {
      Podar(NodoAVL->izquierdo); // Podar izquierdo
      Podar(NodoAVL->derecho);   // Podar derecho
      delete NodoAVL;            // Eliminar NodoAVL
      NodoAVL = nullptr;
   }
}

// Insertar un dato en el árbol AVL
void AVL::Insertar(Persona *per) {
   NodoAVL *padre = nullptr;

   qDebug() << "Insertar: " << per->nombre << endl;
   actual = raiz;

   // Buscar el dato en el árbol, manteniendo un puntero al NodoAVL padre
   while(!Vacio(actual) && per->id != actual->persona->id) {
      padre = actual;
      if(per->id > actual->persona->id)
        actual = actual->derecho;
      else if(per->id < actual->persona->id)
        actual = actual->izquierdo;
   }

   // Si se ha encontrado el elemento, regresar sin insertar
   if(!Vacio(actual))
        return;

   // Si padre es NULL, entonces el árbol estaba vacío, el nuevo NodoAVL será
   // el NodoAVL raiz
   if(Vacio(padre))
        raiz = new NodoAVL(per);

   // Si el dato es menor que el que contiene el NodoAVL padre, lo insertamos
   // en la rama izquierda
   else if(per->id < padre->persona->id) {
      padre->izquierdo = new NodoAVL(per, padre);
      Equilibrar(padre, IZQUIERDO, true);
   }

   // Si el dato es mayor que el que contiene el NodoAVL padre, lo insertamos
   // en la rama derecha
   else if(per->id > padre->persona->id) {
      padre->derecho = new NodoAVL(per, padre);
      Equilibrar(padre, DERECHO, true);
   }
}

 // Equilibrar árbol AVL partiendo del NodoAVL nuevo
void AVL::Equilibrar(NodoAVL *NodoAVL, int rama, bool nuevo) {
   bool salir = false;

   // Recorrer camino inverso actualizando valores de FE:
   while(NodoAVL && !salir) {
      if(nuevo)
         if(rama == IZQUIERDO) NodoAVL->FE--; // Depende de si añadimos ...
         else                  NodoAVL->FE++;
      else
         if(rama == IZQUIERDO) NodoAVL->FE++; // ... o borramos
         else                  NodoAVL->FE--;
      if(NodoAVL->FE == 0) salir = true; // La altura de las rama que
                                         // empieza en NodoAVL no ha variado,
                                         // salir de Equilibrar
      else if(NodoAVL->FE == -2) { // Rotar a derechas y salir:
         if(NodoAVL->izquierdo->FE == 1) RDD(NodoAVL); // Rotación doble
         else RSD(NodoAVL);                         // Rotación simple
         salir = true;
      }

      else if(NodoAVL->FE == 2) {  // Rotar a izquierdas y salir:
         if(NodoAVL->derecho->FE == -1) RDI(NodoAVL); // Rotación doble
         else RSI(NodoAVL);                        // Rotación simple
         salir = true;
      }

      if(NodoAVL->padre)
         if(NodoAVL->padre->derecho == NodoAVL) rama = DERECHO; else rama = IZQUIERDO;
      NodoAVL = NodoAVL->padre; // Calcular FE, siguiente NodoAVL del camino.
   }
}

 // Rotación doble a derechas
void AVL::RDD(NodoAVL* pNodoAVL) {
   qDebug() << "RDD" <<'\n';

   NodoAVL *Padre = pNodoAVL->padre;
   NodoAVL *P = pNodoAVL;
   NodoAVL *Q = P->izquierdo;
   NodoAVL *R = Q->derecho;
   NodoAVL *B = R->izquierdo;
   NodoAVL *C = R->derecho;

   if(Padre)
     if(Padre->derecho == pNodoAVL) Padre->derecho = R;
     else Padre->izquierdo = R;
   else raiz = R;

   // Reconstruir árbol:
   Q->derecho = B;
   P->izquierdo = C;
   R->izquierdo = Q;
   R->derecho = P;

   // Reasignar padres:
   R->padre = Padre;
   P->padre = Q->padre = R;
   if(B) B->padre = Q;
   if(C) C->padre = P;

   // Ajustar valores de FE:
   switch(R->FE) {
      case -1: Q->FE = 0; P->FE = 1; break;
      case 0:  Q->FE = 0; P->FE = 0; break;
      case 1:  Q->FE = -1; P->FE = 0; break;
   }
   R->FE = 0;
}

 // Rotación doble a izquierdas
void AVL::RDI(NodoAVL* pNodoAVL) {
   qDebug() << "RDI" << endl;
   NodoAVL *Padre = pNodoAVL->padre;
   NodoAVL *P = pNodoAVL;
   NodoAVL *Q = P->derecho;
   NodoAVL *R = Q->izquierdo;
   NodoAVL *B = R->izquierdo;
   NodoAVL *C = R->derecho;

   if(Padre)
     if(Padre->derecho == pNodoAVL) Padre->derecho = R;
     else Padre->izquierdo = R;
   else raiz = R;

   // Reconstruir árbol:
   P->derecho = B;
   Q->izquierdo = C;
   R->izquierdo = P;
   R->derecho = Q;

   // Reasignar padres:
   R->padre = Padre;
   P->padre = Q->padre = R;
   if(B) B->padre = P;
   if(C) C->padre = Q;

   // Ajustar valores de FE:
   switch(R->FE) {
      case -1: P->FE = 0; Q->FE = 1; break;
      case 0:  P->FE = 0; Q->FE = 0; break;
      case 1:  P->FE = -1; Q->FE = 0; break;
   }
   R->FE = 0;
}


 // Rotación simple a derechas
void AVL::RSD(NodoAVL* pNodoAVL) {
   qDebug() << "RSD" << endl;
   NodoAVL *Padre = pNodoAVL->padre;
   NodoAVL *P = pNodoAVL;
   NodoAVL *Q = P->izquierdo;
   NodoAVL *B = Q->derecho;

   if(Padre)
     if(Padre->derecho == P) Padre->derecho = Q;
     else Padre->izquierdo = Q;
   else raiz = Q;

   // Reconstruir árbol:
   P->izquierdo = B;
   Q->derecho = P;

   // Reasignar padres:
   P->padre = Q;
   if(B) B->padre = P;
   Q->padre = Padre;

   // Ajustar valores de FE:
   P->FE = 0;
   Q->FE = 0;
}

 // Rotación simple a izquierdas
void AVL::RSI(NodoAVL* pNodoAVL) {
   qDebug() << "RSI" << endl;
   NodoAVL *Padre = pNodoAVL->padre;
   NodoAVL *P = pNodoAVL;
   NodoAVL *Q = P->derecho;
   NodoAVL *B = Q->izquierdo;

   if(Padre)
     if(Padre->derecho == P) Padre->derecho = Q;
     else Padre->izquierdo = Q;
   else raiz = Q;

   // Reconstruir árbol:
   P->derecho = B;
   Q->izquierdo = P;

   // Reasignar padres:
   P->padre = Q;
   if(B) B->padre = P;
   Q->padre = Padre;

   // Ajustar valores de FE:
   P->FE = 0;
   Q->FE = 0;
}


 // Eliminar un elemento de un árbol AVL
void AVL::Borrar(int dat) {
   NodoAVL *padre = nullptr;
   NodoAVL *NodoAVL;
   int aux;

   actual = raiz;

   // Mientras sea posible que el valor esté en el árbol
   while(!Vacio(actual)) {
      if(dat == actual->persona->id) { // Si el valor está en el NodoAVL actual
         if(EsHoja(actual)) { // Y si además es un NodoAVL hoja: lo borramos
            if(padre) // Si tiene padre (no es el NodoAVL raiz)
               // Anulamos el puntero que le hace referencia
               if(padre->derecho == actual) padre->derecho = nullptr;
               else if(padre->izquierdo == actual) padre->izquierdo = nullptr;
            delete actual; // Borrar el NodoAVL
            actual = nullptr;

            // El NodoAVL padre del actual puede ser ahora un NodoAVL hoja, por lo tanto su
            // FE es cero, pero debemos seguir el camino a partir de su padre, si existe.
            if((padre->derecho == actual && padre->FE == 1) ||
               (padre->izquierdo == actual && padre->FE == -1)) {
               padre->FE = 0;
               actual = padre;
               padre = actual->padre;
            }

            if(padre)
               if(padre->derecho == actual) Equilibrar(padre, DERECHO, false);

               else {
                   Equilibrar(padre, IZQUIERDO, false);
               }
            return;
         }

         else { // Si el valor está en el NodoAVL actual, pero no es hoja
            // Buscar NodoAVL
            padre = actual;
            // Buscar NodoAVL más izquierdo de rama derecha
            if(actual->derecho) {
               NodoAVL = actual->derecho;
               while(NodoAVL->izquierdo) {
                  padre = NodoAVL;
                  NodoAVL = NodoAVL->izquierdo;
               }
            }

            // O buscar NodoAVL más derecho de rama izquierda
            else {
               NodoAVL = actual->izquierdo;
               while(NodoAVL->derecho) {
                  padre = NodoAVL;
                  NodoAVL = NodoAVL->derecho;
               }
            }

            // Intercambiar valores de no a borrar u NodoAVL encontrado
            // y continuar, cerrando el bucle. El NodoAVL encontrado no tiene
            // por qué ser un NodoAVL hoja, cerrando el bucle nos aseguramos
            // de que sólo se eliminan NodoAVLs hoja.
            aux = actual->persona->id;
            actual->persona->id = NodoAVL->persona->id;
            NodoAVL->persona->id = aux;
            actual = NodoAVL;
         }
      }

      else { // Todavía no hemos encontrado el valor, seguir buscándolo
         padre = actual;
         if(dat > actual->persona->id) actual = actual->derecho;
         else if(dat < actual->persona->id) actual = actual->izquierdo;
      }
   }
}


// Recorrido de árbol en inorden, aplicamos la función func, que tiene el prototipo: void func(int&, int);
void AVL::InOrden(void (*func)(QString, int) , NodoAVL *NodoAVL, bool r) {
   if(r) NodoAVL = raiz;
   if(NodoAVL->izquierdo) InOrden(func, NodoAVL->izquierdo, false);
   func(NodoAVL->persona->nombre, NodoAVL->FE);
   if(NodoAVL->derecho) InOrden(func, NodoAVL->derecho, false);
}

// Recorrido de árbol en preorden, aplicamos la función func, que tiene el prototipo: void func(int&, int);
void AVL::PreOrden(void (*func)(QString, int), NodoAVL *NodoAVL, bool r) {
   if(r) NodoAVL = raiz;
   func(NodoAVL->persona->nombre, NodoAVL->FE);
   if(NodoAVL->izquierdo) PreOrden(func, NodoAVL->izquierdo, false);
   if(NodoAVL->derecho) PreOrden(func, NodoAVL->derecho, false);
}

// Recorrido de árbol en postorden, aplicamos la función func, que tien el prototipo: void func(int&, int);
void AVL::PostOrden(void (*func)(QString, int), NodoAVL *NodoAVL, bool r) {
   if(r) NodoAVL = raiz;
   if(NodoAVL->izquierdo) PostOrden(func, NodoAVL->izquierdo, false);
   if(NodoAVL->derecho) PostOrden(func, NodoAVL->derecho, false);
   func(NodoAVL->persona->nombre, NodoAVL->FE);
}


// Buscar un valor en el árbol
bool AVL::Buscar(const int dat) {
   actual = raiz;

   // Todavía puede aparecer, ya que quedan NodoAVLs por mirar
   while(!Vacio(actual)) {
      if(dat == actual->persona->id) return true; // dato encontrado
      else if(dat > actual->persona->id) actual = actual->derecho; // Seguir
      else if(dat < actual->persona->id) actual = actual->izquierdo;
   }

   return false; // No está en árbol
}

// Buscar un valor en el árbol
NodoAVL* AVL::BuscarNodoAVL(const int dat) {
   actual = raiz;

   // Todavía puede aparecer, ya que quedan NodoAVLs por mirar
   while(!Vacio(actual)) {
      if(dat == actual->persona->id) return actual; // dato encontrado
      else if(dat > actual->persona->id) actual = actual->derecho; // Seguir
      else if(dat < actual->persona->id) actual = actual->izquierdo;
   }

   return nullptr; // No está en árbol
}

// Calcular la altura del NodoAVL que contiene el dato dat
int AVL::Altura(const int dat) {
   int altura = 0;
   actual = raiz;

   // Todavía puede aparecer, ya que quedan NodoAVLs por mirar
   while(!Vacio(actual)) {
      if(dat == actual->persona->id) return altura; // dato encontrado

      else {
         altura++; // Incrementamos la altura, seguimos buscando
         if(dat > actual->persona->id) actual = actual->derecho;
         else if(dat < actual->persona->id) actual = actual->izquierdo;
      }
   }

   return -1; // No está en árbol
}

// Contar el número de NodoAVLs
int AVL::NumeroNodoAVLs() {
   contador = 0;

   auxContador(raiz); // FUnción auxiliar
   return contador;
}

// Función auxiliar para contar NodoAVLs. Función recursiva de recorrido en
//   preorden, el proceso es aumentar el contador
void AVL::auxContador(NodoAVL *NodoAVL) {
   contador++;  // Otro NodoAVL

   // Continuar recorrido
   if(NodoAVL->izquierdo) auxContador(NodoAVL->izquierdo);
   if(NodoAVL->derecho)   auxContador(NodoAVL->derecho);
}

// Calcular la altura del árbol, que es la altura del NodoAVL de mayor altura.
int AVL::AlturaArbol() {
   altura = 0;

   auxAltura(raiz, 0); // Función auxiliar
   return altura;
}

// Función auxiliar para calcular altura. Función recursiva de recorrido en
// postorden, el proceso es actualizar la altura sólo en NodoAVLs hojas de mayor
// altura de la máxima actual
void AVL::auxAltura(NodoAVL *NodoAVL, int a) {
   // Recorrido postorden
   if(NodoAVL->izquierdo) auxAltura(NodoAVL->izquierdo, a+1);
   if(NodoAVL->derecho)   auxAltura(NodoAVL->derecho, a+1);

   // Proceso, si es un NodoAVL hoja, y su altura es mayor que la actual del
   // árbol, actualizamos la altura actual del árbol
   if(EsHoja(NodoAVL) && a > altura) altura = a;
}

// Función de prueba para recorridos del árbol
void Mostrar(QString n, int FE) {
   qDebug() << n << "(" << FE << "),";
}
