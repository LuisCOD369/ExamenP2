#ifndef CALIFICACIONESUPS_H
#define CALIFICACIONESUPS_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include "formulario.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QKeySequence>

#define MAX_ESTUDIANTES 5

class CalificacionesUPS : public QWidget {
    Q_OBJECT
public:
    CalificacionesUPS(QWidget *parent = nullptr);
    void calcularMinRemedial(Estudiante& estudiante);
public slots:
    void guardarEnArchivoCSV();


private slots:
    void registrar();

private:
    QTableWidget *tableWidget;
    QPushButton *buttonRegistrar;
    void onGuardarPushButtonClicked();

    int numEstudiantes;
    QPushButton *buttonGuardar;
};

#endif // CALIFICACIONESUPS_H
