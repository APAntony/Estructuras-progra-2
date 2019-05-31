#include "estructuras.h"
#include <QtDebug>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <QVector>

using namespace std;

QString Persona::imprimir(){
    QString msg = "";
    msg.append("Identificacion: " + QString::number(id));
    msg.append("\n");
    msg.append("Nombre: " + nombre + "\n");
    msg.append("Apellido: " + apellido + "\n");
    msg.append("Continente: " + continente + "\n");
    msg.append("Pais: " + pais + "\n");
    msg.append("Creencia: " + creencia + "\n");
    msg.append("Profesion: " + profesion + "\n");
    msg.append("Fecha de nacimiento: " + fecha + "\n");
    msg.append("Hora de nacimiento: " + hora + "\n");

    msg += "\n";

    return msg;
}

void ListaPersonas::insertarPersonaOrdenada(Persona *persona){
    if(primerNodo == nullptr) {
        primerNodo = ultimoNodo = new NodoPersona(persona);
    } else if(persona->id < primerNodo->persona->id) {
        NodoPersona *nuevo = new NodoPersona(persona);
        nuevo->siguiente = primerNodo;
        primerNodo = nuevo;
    } else if(persona->id > ultimoNodo->persona->id){
        NodoPersona *nuevo = new NodoPersona(persona);
        ultimoNodo->siguiente = nuevo;
        ultimoNodo = nuevo;
    } else {
        NodoPersona *tmp = primerNodo;
        NodoPersona *nuevo = new NodoPersona(persona);
        while (tmp->siguiente->persona->id < nuevo->persona->id) {
            tmp = tmp->siguiente;
        }

        nuevo->siguiente = tmp->siguiente;
        tmp->siguiente = nuevo;
    }
    contNodos++;
}

QString ListaPersonas::imprimir(){
    QString msg = "";
    NodoPersona *tmp = primerNodo;
    while (tmp != nullptr){
        msg.append(tmp->persona->imprimir());
        tmp = tmp->siguiente;
    }

    return msg;
}

void Mundo::lectura(QString array[], string url) {
    ifstream archivo;
    string texto;
    QString txt;

    archivo.open(url, ios::in);  //Se abre el archivo en modo lectura.

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

void Mundo::crearPersonas(int cantidad){
    int ptrnombre = 0;
    int ptrcreencias = 0;
    int ptrprofesiones = 0;
    int ptrapellidos = 0;
    int ptrpaises = 0;
    int id = 0;
    //QVector<int> ids;

    //int ids[9999999];

    //qDebug()<<"estoy sirviendo3";

    int i = 0;
    while (i < cantidad) {
        //qDebug()<<"estoy sirviendo while"<<i;
        ptrnombre = rand()%1000;
        ptrpaises = rand()%100;
        ptrapellidos = rand()%1000;
        ptrprofesiones = rand()%50;
        ptrcreencias = rand()%10;
        id = rand()%10000000;

        while (this->ids.contains(id)) {
            id = rand()%10000000;
        }

        this->ids.append(id);

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

        lista->insertarPersonaOrdenada(person);
        i++;
    }
}


//ARBOL AVL

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

            if(padre) {
               if(padre->derecho == actual)
                   Equilibrar(padre, DERECHO, false);

               else {
                   Equilibrar(padre, IZQUIERDO, false);
               }
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

// FIN ARBOL AVL



// INICIO ARBOL HEAP

void ArbolHeap::infiltArriba(int i){
    while ((i/2) > 0) {
        if (listaHeap[i]->sumapecados > listaHeap[i/2]->sumapecados) {
            NodoHeap *tmp = listaHeap[i/2];
            listaHeap[i/2] = listaHeap[i];
            listaHeap[i] = tmp;
        }

        i = i/2;
    }
}

void ArbolHeap::infiltAbajo(int i){
    while ((i*2) <= tamanoActual) {
        int hm = hijoMin(i);
        if (listaHeap[i]->sumapecados < listaHeap[hm]->sumapecados) {
            NodoHeap *tmp = listaHeap[i];
            listaHeap[i] = listaHeap[hm];
            listaHeap[hm] = tmp;
        }
        i = hm;
    }
}

int ArbolHeap::hijoMin(int i){
    if ((i*2+1) > tamanoActual) {
        return i*2;
    }
    else {
        if (listaHeap[i*2]->sumapecados < listaHeap[i*2+1]->sumapecados) {
            return i*2;
        } else {
            return i*2+1;
        }
    }
}

NodoHeap* ArbolHeap::eliminarMin() {
    NodoHeap *valorSacado = listaHeap[1];
    listaHeap[1] = listaHeap[tamanoActual];
    tamanoActual = tamanoActual-1;
    listaHeap.pop_back();
    infiltAbajo(1);
    return valorSacado;
}

NodoHeap* ArbolHeap::buscarFamilia(QString apellido_pais) {
    for (NodoHeap* nodo : listaHeap) {
        if(nodo->identificacion == apellido_pais) {
            return nodo;
        }
    }

    return nullptr;
}

int ArbolHeap::buscarUbiacion(QString apellido_pais) {
    for (int i=0; i <= listaHeap.length(); i++) {
        if(listaHeap.at(i)->identificacion == apellido_pais) {
            return i;
        }
    }
    return -1;
}

void ArbolHeap::insertarNuevo(QString familia_pais, Persona *person, int pecado) {
    //qDebug()<<"Pero que?3";
    NodoHeap *nuevo = new NodoHeap(familia_pais);
    nuevo->agregarPersona(person, pecado);
    listaHeap.append(nuevo);
    tamanoActual = tamanoActual+1;
    infiltArriba(tamanoActual);
}



void ArbolHeap::insertar(Persona *person, int pecado) {
    if(buscarFamilia(person->apellido + "-" + person->pais) == nullptr) {
        insertarNuevo(person->apellido + "-" + person->pais, person, pecado);      //inserta un nuevo nodo.
    } else {
        NodoHeap *tmp = buscarFamilia(person->apellido + "-" + person->pais);
        tmp->agregarPersona(person, pecado);                    // inserta una persona en un nodo existente.
        infiltArriba(buscarUbiacion(person->apellido + "-" + person->pais));
    }
}

void ArbolHeap::construirMonticulo(QVector<NodoHeap*> persons){
    QVector<NodoHeap*> personas;

    NodoHeap *p = new NodoHeap();
    personas.append(p);

    for(NodoHeap *per : persons){  //Se acomoda la lista dada para que quede como si fuera [0, dato, dato, dato,...]
        personas.append(per);
    }

    int i = (persons.length()/2);
    tamanoActual = persons.length();
    listaHeap = personas;
    while (i > 0) {
        infiltAbajo(i);
        i = i-1;
    }
}

QString ArbolHeap::recorrer(){
    QString msg = "";

    for (int i = 1; i <= tamanoActual; i++) {
        msg += listaHeap[i]->identificacion + '\n';
    }

    return msg;
}
//FIN DE ARBOL HEAP


//INICIO DE INFIERNO
QString Infierno::consultarDemonioPecado() {
    QString msg = "";

    for(int i=0; i<7; i++) {
        if(i==0){
            msg += "Lucifer";
        }
        else if (i==1) {
            msg += "Belcebu";
        }
        else if (i==2) {
            msg += "Satan";
        }
        else if (i==3) {
            msg += "Abadon";
        }
        else if (i==4){
            msg += "Mammon";
        }
        else if (i==5) {
            msg += "Belfegor";
        }
        else if (i==6) {
            msg += "Asmodeo";
        }

        int cont = 0;
        for(NodoHeap *tmp : demonios[i]->listaHeap) {
            cont += tmp->sumapecados;
        }

        msg += ": "+ QString::number(cont) + "\n";
    }

    return msg;
}

QString Infierno::consultarCantidadHumanos(){
    int contador = 0;
    for(ArbolHeap *demonio : demonios) {
        for(NodoHeap *family : demonio->listaHeap) {
            contador += family->familia->contNodos;
        }
    }

    QString msg = "Cantidad de Humanos en el infierno: " + QString::number(contador);

    return msg;
}

int Infierno::consultarCantidadHumanosInt(){
    int contador = 0;
    for(ArbolHeap *demonio : demonios) {
        for(NodoHeap *family : demonio->listaHeap) {
            contador += family->familia->contNodos;
        }
    }


    return contador;
}

QString Infierno::consultarPromedioDePecados() {
    int sumaDePecados = 0;
    for(ArbolHeap *demonio : demonios) {
        for(NodoHeap *family : demonio->listaHeap) {
            sumaDePecados += family->sumapecados;
        }
    }

    int total = sumaDePecados/consultarCantidadHumanosInt();
    QString msg = "Promedio de pecados en el infierno: " + QString::number(total);

    return msg;
}

QString Infierno::consultarMaximoDePecados() {
    int total = 0;
    for(ArbolHeap *demonio : demonios) {
        total += demonio->listaHeap[1]->sumapecados;   //Suma los pecados de los mas pecadores de los demonios
    }

    QString msg = "Maximo numero de pecados en el infierno: " + QString::number(total);

    return msg;
}

QString Infierno::consultarMinimoDePecados() {
    int total = 0;
    for(ArbolHeap *demonio : demonios) { //ultima posicion del heap
        total += demonio->listaHeap[demonio->listaHeap.length()]->sumapecados;
    }   //Suma los pecados de los menos pecadores de los demonios

    QString msg = "Minimo numero de pecados en el infierno: " + QString::number(total);

    return msg;
}

QString Infierno::consultarMasPecadoresMenosPecadores() {
    QString msg = "";
    for(int i=0; i<7; i++) {
        if(i==0){
            msg += "-----------------Lucifer-----------------";
        }
        else if (i==1) {
            msg += "-----------------Belcebu-----------------";
        }
        else if (i==2) {
            msg += "-----------------Satan-----------------";
        }
        else if (i==3) {
            msg += "-----------------Abadon-----------------";
        }
        else if (i==4){
            msg += "-----------------Mammon-----------------";
        }
        else if (i==5) {
            msg += "-----------------Belfegor-----------------";
        }
        else if (i==6) {
            msg += "-----------------Asmodeo-----------------";
        }

        for(NodoHeap *tmp : demonios[i]->listaHeap) {
            //msg += "----Familia: " + tmp->identificacion+"----\n";
            NodoPersona *nodoTmp = tmp->familia->primerNodo;
            while(nodoTmp != nullptr) {
                msg += nodoTmp->persona->imprimir() +"Pecados:"+
                        QString::number(nodoTmp->persona->pecados[i] - nodoTmp->persona->buenasAcciones[i]) +"\n";
                nodoTmp = nodoTmp->siguiente;
            }
        }

        msg += "\n\n";
    }

    return msg;
}

//FIN DEL INFIERNO

void ArbolAngeles::rellenarPrimerosNiveles() {
    raiz = new NodoTriario();
    raiz->izq = new NodoTriario();
    raiz->cen = new NodoTriario();
    raiz->der = new NodoTriario();
}

/**
 * @brief ArbolAngeles::crearAngeles
 * @param raiz  debe ser
 * @param nivel  siempre debe ser 0
 * @param version siempre debe ser 1
 * @param infierno
 */
void ArbolAngeles::crearAngeles(NodoTriario *raiz, int nivel, int version, ArbolHeap *infierno) {
    if(raiz->izq == nullptr && raiz->cen == nullptr && raiz->der == nullptr) {
        AngelSec *angelIzq = new AngelSec(version, nivel++, infierno);
        //AngelSec *angelIzq = new AngelSec(version, nivel, infierno);
        //AngelSec *angelIzq = new AngelSec(version, nivel, infierno);

        raiz->izq = new NodoTriario(angelIzq);
    } else {

    }
}



void ABBMundo::crearArbol(int tamano) {

}
