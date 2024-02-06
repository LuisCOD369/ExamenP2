#include "formulario.h"
#include <QMessageBox>

Formulario::Formulario(QWidget *parent)
    : QDialog(parent)
{
    // Crear los widgets del formulario
    labelNombres = new QLabel("Nombres:", this);
    labelApellidos = new QLabel("Apellidos:", this);
    labelNota1 = new QLabel("Nota 1 parcial:", this);
    labelNota2 = new QLabel("Nota 2 parcial:", this);
    lineEditNombres = new QLineEdit(this);
    lineEditApellidos = new QLineEdit(this);
    lineEditNota1 = new QLineEdit(this);
    lineEditNota2 = new QLineEdit(this);
    buttonGuardar = new QPushButton("Guardar", this);
    buttonCancelar = new QPushButton("Cancelar", this);

    // Establecer la geometría de los widgets
    labelNombres->setGeometry(10, 10, 100, 20);
    labelApellidos->setGeometry(10, 40, 100, 20);
    labelNota1->setGeometry(10, 70, 100, 20);
    labelNota2->setGeometry(10, 100, 100, 20);
    lineEditNombres->setGeometry(120, 10, 200, 20);
    lineEditApellidos->setGeometry(120, 40, 200, 20);
    lineEditNota1->setGeometry(120, 70, 50, 20);
    lineEditNota2->setGeometry(120, 100, 50, 20);
    buttonGuardar->setGeometry(50, 140, 100, 30);
    buttonCancelar->setGeometry(180, 140, 100, 30);

    // Establecer los validadores para los datos
    QRegExp regExpNombres("[A-Za-z ]{1,50}");
    QRegExp regExpApellidos("[A-Za-z ]{1,50}");
    QRegExp regExpNota("[0-4][0-9]|50");
    QRegExpValidator *validatorNombres = new QRegExpValidator(regExpNombres, this);
    QRegExpValidator *validatorApellidos = new QRegExpValidator(regExpApellidos, this);
    QRegExpValidator *validatorNota = new QRegExpValidator(regExpNota, this);
    lineEditNombres->setValidator(validatorNombres);
    lineEditApellidos->setValidator(validatorApellidos);
    lineEditNota1->setValidator(validatorNota);
    lineEditNota2->setValidator(validatorNota);

    // Conectar las señales y los slots
    connect(buttonGuardar, SIGNAL(clicked()), this, SLOT(guardar()));
    connect(buttonCancelar, SIGNAL(clicked()), this, SLOT(cancelar()));


}



Estudiante Formulario::getDatos()
{
    return datos;
}

void Formulario::guardar()
{
    // Obtener los datos de los widgets
    QString nombres = lineEditNombres->text();
    QString apellidos = lineEditApellidos->text();
    int nota1 = lineEditNota1->text().toInt();
    int nota2 = lineEditNota2->text().toInt();

    // Validar que los datos no estén vacíos
    if (nombres.isEmpty() || apellidos.isEmpty() || nota1 < 0 || nota2 < 0) {
        QMessageBox::warning(this, "Advertencia", "Debe ingresar todos los datos.");
        return;
    }

    // Calcular la nota final y el estado del estudiante
    int notaFinal = nota1 + nota2;
    QString estado;
    int notaRemedial = 0;
    if (notaFinal >= 70) {
        estado = "Aprobado";
    } else if (notaFinal >= 25 && notaFinal < 70) {
        estado = "Remedial";
        notaRemedial = 70 - notaFinal;
    } else {
        estado = "Reprobado";
    }

    // Guardar los datos en la estructura
    datos.nombres = nombres;
    datos.apellidos = apellidos;
    datos.nota1 = nota1;
    datos.nota2 = nota2;
    datos.notaFinal = notaFinal;
    datos.estado = estado;
    datos.notaRemedial = notaRemedial;

    // Cerrar el formulario con éxito
    accept();
}

void Formulario::cancelar()
{
    reject();
}



