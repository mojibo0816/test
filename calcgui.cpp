#include "calcgui.h"
#include <QFont>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QString>
#include <QList>
#include <QSignalMapper>

CalcGUI::CalcGUI():UserWin(new QLineEdit())
{

    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    QHBoxLayout *dispLayout = new QHBoxLayout;
    QGridLayout *buttonLayout = new QGridLayout;
    setStyleSheet("background-color:#CCFFFF;");

    mainLayout->addLayout(dispLayout);
    mainLayout->addLayout(buttonLayout);
    dispLayout->addWidget(UserWin);

    UserWin->setReadOnly(true);
    UserWin->setStyleSheet("background-color:#FFFFCC;");

    QFont font = UserWin->font();
    font.setPointSize(font.pointSize() + 20);
    UserWin->setFont(font);

    /*------------------------Digit Button------------------------*/
    Calc *calculator=new Calc(this);
    QSignalMapper *numMapper = new QSignalMapper(this);
    QSignalMapper *operationMapper = new QSignalMapper(this);
    QList<QPushButton*> buttonList;
    for (unsigned int i=0;i<=9;++i)
    {
        QPushButton *b = new QPushButton;
        b->setText(QString::number(i));
        b->setStyleSheet("QPushButton{background-color: #FF6699;"
                         "height: 30px;}");
        buttonList.append(b);

        connect(buttonList[i],SIGNAL(clicked()),numMapper,
                SLOT(map()));
        numMapper->setMapping(buttonList[i],
                buttonList[i]->text());
    }
    unsigned int key=1;
    //display number key
    buttonLayout->addWidget(buttonList[0],1,1);
    for (unsigned int row=2;row<=4;++row)
    {
        for (unsigned int col=1;col<=3;++col)
        {
            buttonLayout->addWidget(buttonList[key],row,col);
            ++key;
        }
    }
    /*------------------------Functional Button------------------------*/
    QPushButton *pointButton=new QPushButton(".");
    pointButton->setStyleSheet("QPushButton{background-color: #0099FF;"
                     "height: 30px;}");
    buttonLayout->addWidget(pointButton,1,2);

    connect(pointButton,SIGNAL(clicked()),numMapper,
            SLOT(map()));
    numMapper->setMapping(pointButton,
            ".");

    QPushButton *clearButton=new QPushButton("Clear");
    clearButton->setStyleSheet("QPushButton{background-color: #0099FF;"
                     "height: 30px;}");
    buttonLayout->addWidget(clearButton,1,3);
    connect(clearButton,SIGNAL(clicked()),calculator,SLOT(clearAll()));
    /*------------------------Operation Buttons------------------------*/
    QList<QString> operation({"+","-","*","/","="});
    QList<QPushButton*> operationalButton;
    for (unsigned int i=0;i<5;++i)
    {
        QPushButton *b = new QPushButton;
        b->setText(operation[i]);
        operationalButton.append(b);
        if (i!=4)
        {
            operationalButton[i]->setStyleSheet("QPushButton{background-color: #00CC99;"
                             "height: 30px;}");
            buttonLayout->addWidget(operationalButton[i],i+1,4);
            connect( operationalButton[i],SIGNAL(clicked()),operationMapper,
                    SLOT(map()));
            operationMapper->setMapping( operationalButton[i],
                     operationalButton[i]->text());
        }
        else
        {
            b->setStyleSheet("QPushButton{background-color: #FFCC00;"
                             "height: 160px;}");
            buttonLayout->addWidget(operationalButton[i],1,5,4,1);
            connect( operationalButton[i],SIGNAL(clicked()),calculator,
                     SLOT(calculateResult()));
        }
    }
    /*------------------------Events Handling------------------------*/
    connect(numMapper,SIGNAL(mapped(const QString &)),
            calculator,SLOT(setNum(const QString&)));
    connect(operationMapper,SIGNAL(mapped(const QString &)),
            calculator,SLOT(getOperator(const QString&)));
    connect(calculator,SIGNAL(getResult(QString))
                              ,UserWin,SLOT(setText(QString)));
    setWindowTitle(tr("Simple Calculator"));
}


