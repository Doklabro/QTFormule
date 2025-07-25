#include "QTFormule.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTFormule window;
    window.setFixedSize(760,400);
    window.show();
    return app.exec();


}
