// Copyright Lebedev Alexander 2020
#include "mainwindow.h"

#include <iostream>
#include <functional>
#include <cmath>

#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>

#include <statistic.hpp>
#include <task.hpp>
 
Window::Window(QWidget *parent)
        : QWidget(parent) {
    // Layouts
    QVBoxLayout *layout       = new QVBoxLayout(this);
    QHBoxLayout *headerLayout = new QHBoxLayout();
    QGridLayout *setupLayout  = new QGridLayout();
    QVBoxLayout *infoLayout   = new QVBoxLayout();
    QHBoxLayout *tableLayout  = new QHBoxLayout();
    

    // LineEdit boxes
    sizeXLineEdit = new QLineEdit("80", this);
    sizeYLineEdit = new QLineEdit("80", this);
    epsLineEdit   = new QLineEdit("0.000005", this);
    countLineEdit = new QLineEdit("1000", this);

    infoTextEdit  = new QTextEdit("", this);
    storyTextEdit = new QTextEdit("", this);

    infoTextEdit->setReadOnly(true);
    storyTextEdit->setReadOnly(true);
    storyTextEdit->setMinimumHeight(270);
    setInfo();

    // Labels
    sizeXLabel = new QLabel("Число разбиений по X (Кратно 8):", this);
    sizeYLabel = new QLabel("Число разбиений по Y (Кратно 4):", this);
    epsLabel   = new QLabel("Точность:", this);
    countLabel = new QLabel("Максимально число итераций:", this);

    // Tables
    realTable  = new QTableWidget(11, 11, this);
    solveTable = new QTableWidget(11, 11, this);
    diffTable  = new QTableWidget(11, 11, this);

    prepareTable(realTable, 9, 9);
    prepareTable(solveTable, 9, 9);
    prepareTable(diffTable, 9, 9);
 
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
    Task task;
    task.setBoundaries(0., 1., 0., 1.);
    task.setPartition(sizeXLineEdit->text().toInt(), sizeYLineEdit->text().toInt());

    auto result = task.solve(epsLineEdit->text().toDouble(), countLineEdit->text().toInt());

    storyTextEdit->setText(QString::fromStdString(result.getReference()));

    fillTable(realTable, result.realValue);
    fillTable(solveTable, result.solvedValue);
    fillTable(diffTable, result.diffValue);
}

void Window::prepareTable(QTableWidget *table, int n, int m)
{
    QStringList x, y;
    for (int i = 0; i < n; i++)
    {
        x.append("x" + QString::number(i));
    }

    for (int i = 0; i < m; i++)
    {
        y.append("y" + QString::number(m - i - 1));
    }

    table->setColumnCount(n);
    table->setRowCount(m);

    table->setHorizontalHeaderLabels(x);
    table->setVerticalHeaderLabels(y);
}

void Window::fillTable(QTableWidget *table, const std::vector<std::vector<double>> &v)
{
    int n = v.size();
    int m = v[0].size();

    prepareTable(table, n, m);

    for (int j = 0; j < m; j++)
    {
        for (int i = 0; i < n; i++)
        {
            table->setItem(m - j - 1, i, new QTableWidgetItem(QString::number(v[i][j], 'g', 6)));
        }
    }

    table->resizeColumnsToContents();
    table->resizeRowsToContents();
}

void Window::setInfo()
{
    infoTextEdit->setText(
        "   ПОСТАНОВКА ЗАДАЧИ \n\
        Вариант 1\n\
        Δu(x,y) = –f*(x, y), где x пренадлежит (a, b), y пренадлежит (c, d).\n\
        Функции:\n \
        u(x,y) = exp(sin(pi*x*y)^2)\n \
        Область №3 c параметрами: \n\
        a = 0, b = 1, c = 0, d = 1. \n\
        ");
    infoTextEdit->setMaximumHeight(130);
}
