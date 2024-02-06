#ifndef FORMULARIO_H
#define FORMULARIO_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRegExpValidator>

struct Estudiante {
    QString nombres;
    QString apellidos;
    int nota1;
    int nota2;
    int notaFinal;
    QString estado;
    int notaRemedial;
};

class Formulario : public QDialog {
    Q_OBJECT
public:
    Formulario(QWidget *parent = nullptr);

    Estudiante getDatos();

private slots:
    void guardar();
    void cancelar();

private:
    Estudiante datos;
    QLabel *labelNombres;
    QLabel *labelApellidos;
    QLabel *labelNota1;
    QLabel *labelNota2;
    QLineEdit *lineEditNombres;
    QLineEdit *lineEditApellidos;
    QLineEdit *lineEditNota1;
    QLineEdit *lineEditNota2;
    QPushButton *buttonGuardar;
    QPushButton *buttonCancelar;


};

#endif // FORMULARIO_H
