#include "calificacionesups.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalificacionesUPS w;
    w.show();
    return a.exec();
}
