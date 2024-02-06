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






/*
// Incluir los archivos de cabecera necesarios
#include <QApplication>
#include <QDialog>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QRegExpValidator>

// Definir una constante para el número máximo de estudiantes
#define MAX_ESTUDIANTES 100

// Definir una estructura para almacenar los datos de un estudiante
struct Estudiante {
    QString nombres;
    QString apellidos;
    int nota1;
    int nota2;
    int notaFinal;
    QString estado;
    int notaRemedial;
};

// Definir una clase para el formulario de registro de estudiantes y notas
class Formulario : public QDialog {
    Q_OBJECT
public:
    // Constructor de la clase
    Formulario(QWidget *parent = nullptr) : QDialog(parent) {
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

    // Método para obtener los datos del formulario
    Estudiante getDatos() {
        return datos;
    }

private slots:
    // Slot para guardar los datos del formulario
    void guardar() {
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

    // Slot para cancelar el formulario
    void cancelar() {
        // Cerrar el formulario sin éxito
        reject();
    }

private:
    // Widgets del formulario
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

    // Estructura para almacenar los datos
    Estudiante datos;
};

// Definir una clase para la ventana principal de la aplicación
class Ventana : public QWidget {
    Q_OBJECT
public:
    // Constructor de la clase
    Ventana(QWidget *parent = nullptr) : QWidget(parent) {
        // Crear los widgets de la ventana
        tableWidget = new QTableWidget(this);
        buttonRegistrar = new QPushButton("Registrar", this);

        // Establecer la geometría de los widgets
        tableWidget->setGeometry(10, 10, 500, 300);
        buttonRegistrar->setGeometry(200, 320, 100, 30);

        // Establecer las propiedades del widget de tabla
        tableWidget->setColumnCount(6);
        tableWidget->setRowCount(MAX_ESTUDIANTES);
        tableWidget->setHorizontalHeaderLabels(QStringList() << "Nombres" << "Apellidos" << "Nota 1" << "Nota 2" << "Nota Final" << "Estado");
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        // Inicializar el contador de estudiantes
        numEstudiantes = 0;

        // Conectar las señales y los slots
        connect(buttonRegistrar, SIGNAL(clicked()), this, SLOT(registrar()));
    }

private slots:
    // Slot para registrar un estudiante y sus notas
    void registrar() {
        // Crear un objeto de tipo Formulario
        Formulario *formulario = new Formulario(this);

        // Mostrar el formulario de manera modal
        int resultado = formulario->exec();

        // Verificar si el formulario se cerró con éxito
if (resultado == QDialog::Accepted) {
    // Obtener los datos del formulario
    Estudiante estudiante = formulario->getDatos();

    // Mostrar los datos en el cuadro de calificaciones
    tableWidget->setItem(numEstudiantes, 0, new QTableWidgetItem(estudiante.nombres));
    tableWidget->setItem(numEstudiantes, 1, new QTableWidgetItem(estudiante.apellidos));
    tableWidget->setItem(numEstudiantes, 2, new QTableWidgetItem(QString::number(estudiante.nota1)));
    tableWidget->setItem(numEstudiantes, 3, new QTableWidgetItem(QString::number(estudiante.nota2)));
    tableWidget->setItem(numEstudiantes, 4, new QTableWidgetItem(QString::number(estudiante.notaFinal)));
    tableWidget->setItem(numEstudiantes, 5, new QTableWidgetItem(estudiante.estado));

    // Incrementar el contador de estudiantes
    numEstudiantes++;
}

// Eliminar el objeto del formulario
delete formulario;*/
