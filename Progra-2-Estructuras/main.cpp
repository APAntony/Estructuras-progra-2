#include "mainwindow.h"
#include <QApplication>

#include "estructuras.h"
#include <QtDebug>
#include <stdlib.h>
#include <string.h>
#include <fstream>

#include "email.h"
#include "smtpclient.h"
#include "emailaddress.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    Mundo *m = new Mundo();

    //for(QString p : m->paises) {
        //qDebug() << m->lista->imprimir();
    //}

    SMTPClient *cliente = new SMTPClient("smtp.gmail.com");
    EmailAddress credenciales("antonyartavia59@gmail.com", "sbmr8520");

    EmailAddress from("antonyartavia59@gmail.com");

    EmailAddress to("antonyartavia59@gmail.com");

    Email email(credenciales, from, to, "PROBANDO:", m->lista->imprimir());

    cliente->sendEmail(email);


    return a.exec();
}
