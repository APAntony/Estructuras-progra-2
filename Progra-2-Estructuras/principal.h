#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QWidget>
#include "estructuras.h"

namespace Ui {
class Principal;
}

class Principal : public QWidget
{
    Q_OBJECT

public:
    explicit Principal(QWidget *parent = nullptr);
    ~Principal();

private slots:
    void on_contiPecadores_clicked();
    void on_contiBuenos_clicked();
    void on_accionesBt_clicked();
    void on_pecarBt_clicked();
    void pasarHerencia(int[],int[],ListaPersonas*,bool);
    void buscarEnArbol(int[],NodoPersona*,NodoArbol*,bool);
    void buscarDeAqui(NodoPersona*,NodoPersona*,int[],bool);

    void on_crearPersonas_clicked();

private:
    Ui::Principal *ui;
    Mundo * mundo;
    Infierno * infierno;
};

#endif // PRINCIPAL_H
