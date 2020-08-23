#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "world.h"

#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("War! Age of Imperialism");
    setWindowIcon(QIcon(":/root/cannon.png"));

    connect(ui->loadButton, SIGNAL(released()), this, SLOT(loadGameFromFile()));
    connect(ui->saveAsButton, SIGNAL(released()), this, SLOT(renameGame()));
    connect(ui->saveStateButton, SIGNAL(released()), this, SLOT(saveState()));

    filePath = "save.json";
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(saveGame()));
    timer->start(1000);

    World::GetInstance();
    loadGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveGame()
{
    QFile saveFile(filePath);

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QJsonObject worldObject;
    World::GetInstance()->write(worldObject);
    saveFile.write(QJsonDocument(worldObject).toJson());
}

void MainWindow::loadGameFromFile()
{
    filePath = QFileDialog::getOpenFileName(this,
                                            tr("Open Game"), QDir::currentPath(), tr("save file (*.json)"));
    loadGame();
}

void MainWindow::loadGame()
{
    QFile loadFile(filePath);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    World::GetInstance()->read(loadDoc.object());

    QString fileName = filePath.right(filePath.length() - filePath.lastIndexOf('/') - 1);
    fileName = fileName.left(fileName.lastIndexOf('.'));
    setWindowTitle("War! Age of Imperialism - " + fileName);
}

void MainWindow::renameGame()
{
    filePath = QFileDialog::getSaveFileName(this,
                                            tr("Open Game"), QDir::currentPath(), tr("save file (*.json)"));

    QString fileName = filePath.right(filePath.length() - filePath.lastIndexOf('/') - 1);
    fileName = fileName.left(fileName.lastIndexOf('.'));
    setWindowTitle("War! Age of Imperialism - " + fileName);
}

void MainWindow::saveState()
{

}
