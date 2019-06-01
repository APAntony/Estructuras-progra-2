#include "continente.h"
#include "ui_continente.h"

Continente::Continente(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Continente)
{
    ui->setupUi(this);
    ui->africa->setStyleSheet("background:orange");
    ui->america->setStyleSheet("background:red");
    ui->europa->setStyleSheet("background:lightgreen");
    ui->asia->setStyleSheet("background:blue");
    ui->oceania->setStyleSheet("background:yellow");
    QFont fuente("MS Shell Dlg 2",12,QFont::Thin);
    ui->labelPaises->setAlignment(Qt::AlignCenter);
    ui->labelPaises->setFont(fuente);
    ui->labelPaises->setText("Hola");
}

Continente::~Continente()
{
    delete ui;
}
