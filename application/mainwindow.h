// Copyright Lebedev Alexander 2020
#pragma once
 
#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>

#include <vector>
 
class Window : public QWidget {
    
public:
    Window(QWidget *parent = 0);

    ~Window() = default;

    void prepareTable(QTableWidget *table, int n, int m);

    void fillTable(QTableWidget *table, const std::vector<std::vector<double>> &v);

    void setInfo();

    void run();

private:
    QLineEdit *sizeXLineEdit;
    QLineEdit *sizeYLineEdit;
    QLineEdit *epsLineEdit;
    QLineEdit *countLineEdit;

    QTextEdit *infoTextEdit;
    QTextEdit *storyTextEdit;

    QLabel *sizeXLabel;
    QLabel *sizeYLabel;
    QLabel *epsLabel;
    QLabel *countLabel;

    QPushButton *runButton;

    QTableWidget *realTable;
    QTableWidget *solveTable;
    QTableWidget *diffTable;
};
