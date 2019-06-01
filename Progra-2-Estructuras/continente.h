#ifndef CONTINENTE_H
#define CONTINENTE_H

#include <QWidget>

namespace Ui {
class Continente;
}

class Continente : public QWidget
{
    Q_OBJECT

public:
    explicit Continente(QWidget *parent = nullptr);
    ~Continente();

private:
    Ui::Continente *ui;
};

#endif // CONTINENTE_H
