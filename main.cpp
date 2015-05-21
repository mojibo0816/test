#include <QApplication>
#include <QWidget>

#include "calcgui.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CalcGUI calculator;
    calculator.setAttribute(Qt::WA_QuitOnClose);
    calculator.show();
    return app.exec();
}
