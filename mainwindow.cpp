#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("War! Age of Imperialism");
    setWindowIcon(QIcon(":/root/cannon.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
