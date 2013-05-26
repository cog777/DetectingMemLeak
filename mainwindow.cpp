#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mynew.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QObject *pObject = new QObject(); // Memory leak
    pObject = new QObject(this); // Is is not memory leak
    int *ptr = new int; // It is okay too
    delete ptr;
    ptr = new int[10]; // Bad, It should be deleted as an array
    delete ptr;
}
