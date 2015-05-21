#ifndef CALCGUI
#define CALCGUI
#include "calc.h"
#include <QDialog>

class QLineEdit;

class CalcGUI:public QDialog
{
    Q_OBJECT
public:
    CalcGUI();
private:
    QLineEdit* UserWin;
};
#endif // CALCGUI

