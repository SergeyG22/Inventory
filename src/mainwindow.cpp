#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <newgame.h>
#include <menu.h>
#include <exit.h>
#include <buttons.h>
#include <command.h>
#include <closegamecommand.h>
#include <creategamecommand.h>
#include <stopgamecommand.h>
#include <apple.h>
#include <item.h>
#include <inventory.h>
#include <inventorytable.h>
#include <game.h>
#include <sqlitedatabase.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Inventory");
    this->setMaximumSize(800,700);
    this->setMinimumSize(800,700);

    SQLiteDataBase data_base;
    Item* apple = new Apple(this);
    Inventory* inventory = new InventoryTable(this);
    inventory->setItemPointer(apple);
    QList<Buttons*>buttons{ new NewGame(this), new Menu(this), new Exit(this)};
    game = new Game(buttons,this,inventory,apple);
    QObject::connect(dynamic_cast<QPushButton*>(buttons.at(2)),&QPushButton::clicked, this, &MainWindow::closeGame);
    QObject::connect(dynamic_cast<QPushButton*>(buttons.at(0)),&QPushButton::clicked, this, &MainWindow::createGame);
    QObject::connect(dynamic_cast<QPushButton*>(buttons.at(1)),&QPushButton::clicked, this, &MainWindow::stopGame);
}

void MainWindow::closeGame() {
    Command* command = new CloseGameCommand(game);
    command->execute();
}

void MainWindow::createGame() {
    Command* command = new CreateGameCommand(game);
    command->execute();
}

void MainWindow::stopGame() {
    Command* command = new StopGameCommand(game);
    command->execute();
}

MainWindow::~MainWindow() {
    delete ui;
}









