// Copyright Lebedev Alexander 2020
#include "mainwindow.h"

#include <iostream>
#include <functional>
#include <cmath>

#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
 
Window::Window(QWidget *parent)
        : QWidget(parent) {
    // Layouts
    QVBoxLayout *layout       = new QVBoxLayout(this);
    QHBoxLayout *headerLayout = new QHBoxLayout();
    QGridLayout *setupLayout  = new QGridLayout();
    QVBoxLayout *infoLayout   = new QVBoxLayout();
    QHBoxLayout *tableLayout  = new QHBoxLayout();
    

    // LineEdit boxes
    sizeXLineEdit = new QLineEdit("10", this);
    sizeYLineEdit = new QLineEdit("10", this);
    epsLineEdit   = new QLineEdit("0.00000001", this);
    countLineEdit = new QLineEdit("1000", this);

    infoTextEdit  = new QTextEdit("", this);
    storyTextEdit = new QTextEdit("", this);

    infoTextEdit->setReadOnly(true);
    storyTextEdit->setReadOnly(true);
    setInfo();

    // Labels
    sizeXLabel = new QLabel("Число разбиений по X:", this);
    sizeYLabel = new QLabel("Число разбиений по Y:", this);
    epsLabel   = new QLabel("Точность:", this);
    countLabel = new QLabel("Максимально число итераций:", this);

    // Tables
    realTable  = new QTableWidget(11, 11, this);
    solveTable = new QTableWidget(11, 11, this);
    diffTable  = new QTableWidget(11, 11, this);

    prepareTable(realTable);
    prepareTable(solveTable);
    prepareTable(diffTable);
 
    // Buttons
    runButton = new QPushButton("Запуск решения", this);

    // Makeup
    setupLayout->addWidget(sizeXLabel, 0, 0);
    setupLayout->addWidget(sizeXLineEdit, 0, 1);
    setupLayout->addWidget(sizeYLabel, 1, 0);
    setupLayout->addWidget(sizeYLineEdit, 1, 1);
    setupLayout->addWidget(epsLabel, 2, 0);
    setupLayout->addWidget(epsLineEdit,2, 1);
    setupLayout->addWidget(countLabel, 3, 0);
    setupLayout->addWidget(countLineEdit, 3, 1);
    setupLayout->addWidget(runButton, 4, 0);

    infoLayout->addWidget(infoTextEdit);
    infoLayout->addWidget(storyTextEdit);

    headerLayout->addLayout(setupLayout);
    headerLayout->addLayout(infoLayout);

    tableLayout->addWidget(realTable);
    tableLayout->addWidget(solveTable);
    tableLayout->addWidget(diffTable);

    layout->addLayout(headerLayout);
    layout->addLayout(tableLayout);

    setLayout(layout);

    // Connection
    connect(runButton, &QPushButton::clicked, this, &Window::run);
}

void Window::run()
{

}

void Window::prepareTable(QTableWidget *table)
{
    int n = 11;
    QStringList x, y;
    for (int i = 0; i < n; i++)
    {
        x.append("x" + QString::number(i));
        y.append("y" + QString::number(n - i - 1));
    }
    table->setHorizontalHeaderLabels(x);
    table->setVerticalHeaderLabels(y);

    // table->resizeColumnsToContents();
    // table->resizeRowsToContents();
}

void Window::fillTable(QTableWidget *table, const std::vector<std::vector<double>> &v)
{

}

void Window::setInfo()
{
    infoTextEdit->setText(
        "   ПОСТАНОВКА ЗАДАЧИ \n\
        \
        Δu(x,y) = –f*(x, y), где x пренадлежит (a, b), y пренадлежит (c, d).\n\
        u(a,y) = μ*1(y), u(b,y) = μ*2(y), где y пренадлежит [c, d].\n\
        u(x,c) = μ*3(x), u(x,d) = μ*4(x), где x пренадлежит [a, b].\n\
        Функции:\n \
        u(x,y) = exp(sin(pi*x*y)^2)\n \
        f*(x,y) =  \n\
        ГУ: \n\
        μ1*(y) = 1, μ2*(y) = exp(sin(pi*y)^2) \n\
        μ3*(x) = 1, μ4*(x) = exp(sin(pi*x)^2) \n\
        Область: \n\
        a = 0, b = 1, c = 0, d = 1. \n\
        ");
}
