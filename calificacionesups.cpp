#include "calificacionesups.h"
#include <QHeaderView>

CalificacionesUPS::CalificacionesUPS(QWidget *parent)
    : QWidget(parent), numEstudiantes(0)
{
    // Crear los widgets de la ventana
    tableWidget = new QTableWidget(this);
    buttonRegistrar = new QPushButton("Registrar", this);

    // Establecer la geometría de los widgets
    tableWidget->setGeometry(10, 10, 600, 300);
    buttonRegistrar->setGeometry(200, 320, 100, 30);

    // Establecer las propiedades del widget de tabla
    tableWidget->setColumnCount(7);
    tableWidget->setRowCount(MAX_ESTUDIANTES);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Nombres" << "Apellidos" << "Nota 1" << "Nota 2" << "Nota Final" << "Estado"<<"Min_Remedial");
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Inicializar el contador de estudiantes
    numEstudiantes = 0;

    // Conectar las señales y los slots
    connect(buttonRegistrar, SIGNAL(clicked()), this, SLOT(registrar()));
}
void CalificacionesUPS::calcularMinRemedial(Estudiante& estudiante) {
    // Calcular la nota mínima del examen remedial
    double notaAprobacion = 70;
    double porcentajeNotaAprobacion = 0.4;
    double notaMinRemedial = (notaAprobacion - porcentajeNotaAprobacion * estudiante.notaFinal)/0.6;

    // Asignar la nota mínima del remedial al estudiante
    estudiante.notaRemedial = notaMinRemedial;

}
void CalificacionesUPS::registrar()
{
    // Crear un objeto de tipo Formulario
    Formulario *formulario = new Formulario(this);

    // Mostrar el formulario de manera modal
    int resultado = formulario->exec();

    // Verificar si el formulario se cerró con éxito
    if (resultado == QDialog::Accepted) {
        // Obtener los datos del formulario
        Estudiante estudiante = formulario->getDatos();
        calcularMinRemedial(estudiante);

        // Mostrar los datos en el cuadro de calificaciones
        tableWidget->setItem(numEstudiantes, 0, new QTableWidgetItem(estudiante.nombres));
        tableWidget->setItem(numEstudiantes, 1, new QTableWidgetItem(estudiante.apellidos));
        tableWidget->setItem(numEstudiantes, 2, new QTableWidgetItem(QString::number(estudiante.nota1)));
        tableWidget->setItem(numEstudiantes, 3, new QTableWidgetItem(QString::number(estudiante.nota2)));
        tableWidget->setItem(numEstudiantes, 4, new QTableWidgetItem(QString::number(estudiante.notaFinal)));
        tableWidget->setItem(numEstudiantes, 5, new QTableWidgetItem(estudiante.estado));
        tableWidget->setItem(numEstudiantes, 6, new QTableWidgetItem(QString::number(estudiante.notaRemedial)));

        // Incrementar el contador de estudiantes
        numEstudiantes++;
    }
}


