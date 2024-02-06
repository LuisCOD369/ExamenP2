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
#include <QMessageBox>

#define MAX_ESTUDIANTES 10

class CalificacionesUPS : public QWidget {
    Q_OBJECT
public:
    CalificacionesUPS(QWidget *parent = nullptr);
    void calcularMinRemedial(Estudiante& estudiante);

public slots:
    void guardarEnArchivoCSV();


private slots:
    void registrar();
    void onGuardarPushButtonClicked();
    void cargarDatos();
    void mostrarCreditos();

private:
    QTableWidget *tableWidget;
    QPushButton *buttonRegistrar;
    QPushButton *buttonCargarD;


    int numEstudiantes;
    QPushButton *buttonGuardar;
    QPushButton *buttonCreditos;
};

#endif // CALIFICACIONESUPS_H
