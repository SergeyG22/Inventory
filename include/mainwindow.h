#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <buttons.h>
#include <newgame.h>
#include <menu.h>
#include <exit.h>
#include <inventory.h>
#include <apple.h>
#include <game.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Game* game;
private:
    Ui::MainWindow *ui;
private slots:
    void closeGame();
    void createGame();
    void stopGame();
};
#endif // MAINWINDOW_H
