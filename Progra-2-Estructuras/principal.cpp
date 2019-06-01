#include "principal.h"
#include "ui_principal.h"

#include "smtp.h"

Principal::Principal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Principal)
{
    ui->setupUi(this);
    mundo=new Mundo();
    infierno=new Infierno;
    mundo->crearPersonas(10000);
    ui->cantidadPersonas->setMaximum(30000);
}

Principal::~Principal()
{
    delete ui;
}

void Principal::on_contiPecadores_clicked()
{
    NodoPersona * tmp=mundo->lista->primerNodo;
    int america=0,europa=0,asia=0,oceania=0,africa=0;
    while(tmp!=nullptr){
        int pecadosTotales=0;
        pecadosTotales+=tmp->persona->pecados[0];
        pecadosTotales+=tmp->persona->pecados[1];
        pecadosTotales+=tmp->persona->pecados[2];
        pecadosTotales+=tmp->persona->pecados[3];
        pecadosTotales+=tmp->persona->pecados[4];
        pecadosTotales+=tmp->persona->pecados[5];
        pecadosTotales+=tmp->persona->pecados[6];
        if(tmp->persona->continente=="America"){
            america+=pecadosTotales;
        }else if(tmp->persona->continente=="Africa"){
            africa+=pecadosTotales;
        }else if(tmp->persona->continente=="Asia"){
            asia+=pecadosTotales;
        }else if(tmp->persona->continente=="Europa"){
            europa+=pecadosTotales;
        }else{
            oceania+=pecadosTotales;
        }
        tmp=tmp->siguiente;
    }
    qDebug()<<america<<endl;
    qDebug()<<europa<<endl;
    qDebug()<<africa<<endl;
    qDebug()<<asia<<endl;
    qDebug()<<oceania<<endl;
    qDebug()<<"Hola"<<endl;

}

void Principal::on_contiBuenos_clicked()
{
    NodoPersona *tmp=mundo->lista->primerNodo;
    int america=0,europa=0.,asia=0,oceania=0,africa=0;
    while(tmp!=nullptr){
        int accionesTotales=0;
        accionesTotales+=tmp->persona->buenasAcciones[0];
        accionesTotales+=tmp->persona->buenasAcciones[1];
        accionesTotales+=tmp->persona->buenasAcciones[2];
        accionesTotales+=tmp->persona->buenasAcciones[3];
        accionesTotales+=tmp->persona->buenasAcciones[4];
        accionesTotales+=tmp->persona->buenasAcciones[5];
        accionesTotales+=tmp->persona->buenasAcciones[6];
        if(tmp->persona->continente=="America"){
            america+=accionesTotales;
        }else if(tmp->persona->continente=="Africa"){
            africa+=accionesTotales;
        }else if(tmp->persona->continente=="Asia"){
            asia+=accionesTotales;
        }else if(tmp->persona->continente=="Europa"){
            europa+=accionesTotales;
        }else{
            oceania+=accionesTotales;
        }
        tmp=tmp->siguiente;
    }
    qDebug()<<america<<endl;
    qDebug()<<europa<<endl;
    qDebug()<<africa<<endl;
    qDebug()<<asia<<endl;
    qDebug()<<oceania<<endl;
}

void Principal::buscarDeAqui(NodoPersona * inicio,NodoPersona * buscado,int arreglo[],bool tipo){
    qDebug()<<"Mdre mia";
    while(inicio->persona->id!=buscado->persona->id){
        qDebug()<<"Mdre mia4";
        qDebug()<<"inicio"<<inicio->persona->id;
        qDebug()<<"buscado"<<buscado->persona->id;
        inicio=inicio->siguiente;
    }
    qDebug()<<"Mdre mia2";
    if(tipo){
        inicio->persona->buenasAcciones[0]+=arreglo[0];
        inicio->persona->buenasAcciones[1]+=arreglo[1];
        inicio->persona->buenasAcciones[2]+=arreglo[2];
        inicio->persona->buenasAcciones[3]+=arreglo[3];
        inicio->persona->buenasAcciones[4]+=arreglo[4];
        inicio->persona->buenasAcciones[5]+=arreglo[5];
        inicio->persona->buenasAcciones[6]+=arreglo[6];
    }else{
        qDebug()<<"Mdre mia3";
        inicio->persona->pecados[0]+=arreglo[0];
        inicio->persona->pecados[1]+=arreglo[1];
        inicio->persona->pecados[2]+=arreglo[2];
        inicio->persona->pecados[3]+=arreglo[3];
        inicio->persona->pecados[4]+=arreglo[4];
        inicio->persona->pecados[5]+=arreglo[5];
        inicio->persona->pecados[6]+=arreglo[6];
    }
}

void Principal::buscarEnArbol(int arreglo[],NodoPersona * nodo,NodoArbol * arbol,bool tipo){
    bool lol = arbol->persona == nodo->persona;
    qDebug()<<"Morimos "<<lol;
    if(arbol->persona->id == nodo->persona->id){
        if(tipo){
            qDebug()<<"Morimos2";
            arbol->persona->buenasAcciones[0]+=arreglo[0];
            arbol->persona->buenasAcciones[1]+=arreglo[1];
            arbol->persona->buenasAcciones[2]+=arreglo[2];
            arbol->persona->buenasAcciones[3]+=arreglo[3];
            arbol->persona->buenasAcciones[4]+=arreglo[4];
            arbol->persona->buenasAcciones[5]+=arreglo[5];
            arbol->persona->buenasAcciones[6]+=arreglo[6];
        }else{
            qDebug()<<"Morimos3";
            arbol->persona->pecados[0]+=arreglo[0];
            arbol->persona->pecados[1]+=arreglo[1];
            arbol->persona->pecados[2]+=arreglo[2];
            arbol->persona->pecados[3]+=arreglo[3];
            arbol->persona->pecados[4]+=arreglo[4];
            arbol->persona->pecados[5]+=arreglo[5];
            arbol->persona->pecados[6]+=arreglo[6];
        }
    }else if(arbol->nodo!=nullptr){
        qDebug()<<"Morimos4";
        buscarDeAqui(arbol->nodo,nodo,arreglo,tipo);
    }//else if(arbol->persona->id>nodo->persona->id){
        //qDebug()<<"Morimos5";
        //buscarEnArbol(arreglo,nodo,arbol->izq,tipo);
    //}
    else{
        qDebug()<<"Morimos6";
        buscarEnArbol(arreglo,nodo,arbol->izq,tipo);
    }
}

void Principal::pasarHerencia(int hijos[],int nietos[],ListaPersonas *descendientes,bool tipo){
    qDebug()<<"What!!";
    NodoPersona * hijo=descendientes->primerNodo;
    while(hijo!=nullptr){
        qDebug()<<"What!!2";
        buscarEnArbol(hijos,hijo,mundo->arbolMundo->raiz,tipo);\
        qDebug()<<"What!!3";
        NodoPersona * nieto=hijo->persona->hijos->primerNodo;
        while(nieto!=nullptr){
            qDebug()<<"What!!4";
            buscarEnArbol(nietos,nieto,mundo->arbolMundo->raiz,tipo);
            nieto=nieto->siguiente;
        }
        hijo=hijo->siguiente;
    }
}

void Principal::on_accionesBt_clicked()
{
    NodoPersona * tmp=mundo->lista->primerNodo;
    while(tmp!=nullptr){
        int castidad=rand()%101;
        int ayuno=rand()%101;
        int donacion=rand()%101;
        int diligencia=rand()%101;
        int calma=rand()%101;
        int solidaridad=rand()%101;
        int humildad=rand()%101;
        int buenasHijos[]={castidad/2,ayuno/2,donacion/2,diligencia,calma/2,solidaridad/2,humildad/2};
        int buenasNietos[]={castidad/4,ayuno/4,donacion/4,diligencia/4,calma/4,solidaridad/4,humildad/4};
        pasarHerencia(buenasHijos,buenasNietos,tmp->persona->hijos,true);
        tmp->persona->buenasAcciones[0]+=castidad;
        tmp->persona->buenasAcciones[1]+=ayuno;
        tmp->persona->buenasAcciones[2]+=donacion;
        tmp->persona->buenasAcciones[3]+=diligencia;
        tmp->persona->buenasAcciones[4]+=calma;
        tmp->persona->buenasAcciones[5]+=solidaridad;
        tmp->persona->buenasAcciones[6]+=humildad;
        tmp=tmp->siguiente;
    }
}

void Principal::on_pecarBt_clicked()
{
    NodoPersona * tmp=mundo->lista->primerNodo;

    while(tmp!=nullptr){
        qDebug()<<"Estoy vivo";
        int lujuria=rand()%101;
        int gula=rand()%101;
        int avaricia=rand()%101;
        int pereza=rand()%101;
        int ira=rand()%101;
        int envidia=rand()%101;
        int soberbia=rand()%101;
        int pecadosHijos[]={lujuria/2,gula/2,avaricia/2,pereza,ira/2,envidia/2,soberbia/2};
        int pecadosNietos[]={lujuria/4,gula/4,avaricia/4,pereza/4,ira/4,envidia/4,soberbia/4};
        qDebug()<<"Estoy vivo2";
        pasarHerencia(pecadosHijos,pecadosNietos,tmp->persona->hijos,false);
        qDebug()<<"Estoy vivo3";
        tmp->persona->pecados[0]+=lujuria;
        tmp->persona->pecados[1]+=gula;
        tmp->persona->pecados[2]+=avaricia;
        tmp->persona->pecados[3]+=pereza;
        tmp->persona->pecados[4]+=ira;
        tmp->persona->pecados[5]+=envidia;
        tmp->persona->pecados[6]+=soberbia;
        qDebug()<<"Estoy vivo4";
        tmp=tmp->siguiente;
    }
}

void Principal::on_crearPersonas_clicked()
{
    mundo->crearPersonas(ui->cantidadPersonas->value());
    mundo->hacerHijos();


}
