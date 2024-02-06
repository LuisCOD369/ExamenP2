#ifndef CALIFICACIONESUPS_H
#define CALIFICACIONESUPS_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include "formulario.h"
#define MAX_ESTUDIANTES 5

class CalificacionesUPS : public QWidget {
    Q_OBJECT
public:
    CalificacionesUPS(QWidget *parent = nullptr);


private slots:
    void registrar();

private:
    QTableWidget *tableWidget;
    QPushButton *buttonRegistrar;

    int numEstudiantes;
};

#endif // CALIFICACIONESUPS_H
