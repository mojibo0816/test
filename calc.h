#ifndef CALC
#define CALC
#include <QObject>

class Calc:public QObject
{
    Q_OBJECT
public:
    Calc(QObject *parent =0);
public slots:
    void setNum(const QString&);
    void clearAll();
    void getOperator(const QString&);
    void calculateResult();
signals:
    void getResult(QString);
private:
    void computation(const QString& operatotion,double &result);
    double prevNum;
    QString nextNum;
    QString operation;
    int counter;
};
#endif // CALC

