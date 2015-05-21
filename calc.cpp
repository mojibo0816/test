#include "calc.h"

Calc::Calc(QObject* parent):QObject(parent),prevNum(0.0),nextNum(""),
    operation(""),counter(0)
{

}
void Calc::setNum(const QString& entered)
{
    QString total="";
    if (operation=="=")
    {
        operation="";
        total=entered;
     }
    else
    {
        total=nextNum+entered;
    }
    this->nextNum=total;
    emit getResult(total);
}
void Calc::getOperator(const QString& entered)
{
    QString lastOperation=this->operation;
    this->operation=entered;
    if (counter!=0)//handles chaining ex) 1+2-3
    {
        double result;
        computation(lastOperation,result);
        this->prevNum=result;
        this->nextNum="";
    }
    else if (lastOperation!="=")
    {
        this->prevNum=this->nextNum.toDouble();
        this->nextNum="";
    }
    else //handles equal sign 3+2=5+1=6
    {
        this->nextNum="";
    }
    emit getResult(this->operation);
    ++counter;
}
void Calc::calculateResult( )
{
    counter=0;
    double result;
    computation(this->operation,result);
    emit getResult(QString::number(result));
    //reset for future
    this->operation="=";
    this->prevNum=result;
    this->nextNum="";
}
void Calc::clearAll()
{
    this->prevNum=0;
    this->nextNum="";
    this->operation="";
    this->counter=0;
    emit getResult("Cleared");
}
void Calc::computation(const QString& operation,double &result)
{
    if (operation=="+")
        result=this->prevNum+this->nextNum.toDouble();
    else if (operation=="-")
        result=this->prevNum-this->nextNum.toDouble();
    else if (operation=="*")
        result=this->prevNum*this->nextNum.toDouble();
    else
        result=this->prevNum/this->nextNum.toDouble();
}
