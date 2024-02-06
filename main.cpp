#include "calificacionesups.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalificacionesUPS w;
    w.show();
    return a.exec();
}
