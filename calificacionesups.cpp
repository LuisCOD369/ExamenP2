#include "calificacionesups.h"
#include <QHeaderView>
#include <QFileDialog>
#include <QtDebug>
#include <QVBoxLayout>
#include <QDesktopServices>

CalificacionesUPS::CalificacionesUPS(QWidget *parent)
    : QWidget(parent), numEstudiantes(0)
{
    // Crear los widgets de la ventana
    tableWidget = new QTableWidget(this);
    buttonRegistrar = new QPushButton("Registrar", this);
    buttonGuardar = new QPushButton("Guardar", this);
    buttonCargarD = new QPushButton("Cargar", this);
    buttonCreditos = new QPushButton("Creditos", this);

    // Establecer la geometría de los widgets
    tableWidget->setGeometry(10, 10, 600, 300);
    buttonRegistrar->setGeometry(200, 320, 100, 30);
    buttonGuardar->setGeometry(200, 360, 100, 30);
    buttonCargarD->setGeometry(300, 360, 100, 30);
    buttonCreditos->setGeometry(400, 360, 100, 30 );

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
    connect(buttonGuardar, SIGNAL(clicked()), this, SLOT(onGuardarPushButtonClicked()));
    connect(buttonCargarD, SIGNAL(clicked()), this, SLOT(cargarDatos()));
    connect(buttonCreditos, SIGNAL(clicked()), this, SLOT(mostrarCreditos()));

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
        if (estudiante.notaFinal < 70) {
            tableWidget->setItem(numEstudiantes, 6, new QTableWidgetItem(QString::number(estudiante.notaRemedial)));
        } else {
            tableWidget->setItem(numEstudiantes, 6, new QTableWidgetItem(""));
        }
        // Incrementar el contador de estudiantes
        numEstudiantes++;
    }
}

void CalificacionesUPS::guardarEnArchivoCSV() {
    // Obtener la ruta del archivo usando un cuadro de diálogo
    QString rutaArchivo = QFileDialog::getSaveFileName(this, "Guardar como", QString(), "Archivos CSV (*.csv)");

    if (!rutaArchivo.isEmpty()) {
        QFile archivo(rutaArchivo);
        if (archivo.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&archivo);

            // Escribir las cabeceras
            QStringList cabeceras;
            for (int col = 0; col < tableWidget->columnCount(); ++col) {
                cabeceras << tableWidget->horizontalHeaderItem(col)->text();
            }
            stream << cabeceras.join(',') << "\n";

            // Escribir los datos
            for (int row = 0; row < numEstudiantes; ++row) {
                QStringList datosFila;
                for (int col = 0; col < tableWidget->columnCount(); ++col) {
                    QTableWidgetItem *item = tableWidget->item(row, col);
                    datosFila << (item ? item->text() : "");
                }
                stream << datosFila.join(',') << "\n";
            }

            archivo.close();
        }
    }
}
void CalificacionesUPS::onGuardarPushButtonClicked() {
    qDebug() << "Botón Guardar clickeado";
    guardarEnArchivoCSV();
}
void CalificacionesUPS::cargarDatos()
{
    // Obtener la ruta del archivo CSV
    QString rutaArchivo = QFileDialog::getOpenFileName(this, "Abrir archivo CSV", QString(), "Archivos CSV (*.csv)");

    if (!rutaArchivo.isEmpty()) {
        // Abrir el archivo en modo de lectura
        QFile archivo(rutaArchivo);
        if (archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream stream(&archivo);

            // Leer la cabecera (primera línea)
            QString lineaCabecera = stream.readLine();
            QStringList camposCabecera = lineaCabecera.split(',');

            // Verificar si la cabecera tiene el formato esperado
            if (camposCabecera.size() != 7 ||
                camposCabecera.at(0) != "Nombres" ||
                camposCabecera.at(1) != "Apellidos" ||
                camposCabecera.at(2) != "Nota 1" ||
                camposCabecera.at(3) != "Nota 2" ||
                camposCabecera.at(4) != "Nota Final" ||
                camposCabecera.at(5) != "Estado" ||
                camposCabecera.at(6) != "Min_Remedial") {
                // La cabecera no tiene el formato esperado
                QMessageBox::warning(this, "Advertencia", "El archivo no tiene el formato esperado.");
                archivo.close();
                return;
            }

            // Leer los datos
            while (!stream.atEnd()) {
                QString lineaDatos = stream.readLine();
                QStringList camposDatos = lineaDatos.split(',');

                // Verificar si hay suficientes campos
                if (camposDatos.size() == 7) {
                    // Crear un nuevo estudiante y asignar los valores
                    Estudiante estudiante;
                    estudiante.nombres = camposDatos.at(0);
                    estudiante.apellidos = camposDatos.at(1);
                    estudiante.nota1 = camposDatos.at(2).toInt();
                    estudiante.nota2 = camposDatos.at(3).toInt();
                    estudiante.notaFinal = camposDatos.at(4).toInt();
                    estudiante.estado = camposDatos.at(5);
                    estudiante.notaRemedial = camposDatos.at(6).toInt();

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
                } else {
                    // La línea no tiene el formato esperado
                    QMessageBox::warning(this, "Advertencia", "El archivo contiene datos incorrectos.");
                }
            }

            archivo.close();
        } else {
            QMessageBox::warning(this, "Error", "No se pudo abrir el archivo.");
        }
    }
}

void CalificacionesUPS::mostrarCreditos()
{
    // Crear y mostrar la ventana de créditos
    QString nombreUsuario = "LuisCOD369";
    QDialog creditosDialog(this);
    creditosDialog.setWindowTitle("Créditos");

    QLabel *labelNombre = new QLabel("Nombre: " + nombreUsuario, &creditosDialog);
    QPushButton *buttonEnlace = new QPushButton("Abrir Enlace", &creditosDialog);

    connect(buttonEnlace, &QPushButton::clicked, [&]() {
        // Abrir el enlace en el navegador predeterminado
        QDesktopServices::openUrl(QUrl("https://github.com/LuisCOD369"));
    });

    QVBoxLayout *layout = new QVBoxLayout(&creditosDialog);
    layout->addWidget(labelNombre);
    layout->addWidget(buttonEnlace);

    creditosDialog.setLayout(layout);

    creditosDialog.exec();
}
