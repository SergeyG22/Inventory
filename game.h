#ifndef GAME_H
#define GAME_H
#include <QDebug>
#include <exit.h>
#include <newgame.h>
#include <menu.h>
#include <buttons.h>
#include <inventory.h>
#include <inventorytable.h>
#include <item.h>

class Game {
    QList<Buttons*>button_ptr;
    QWidget* window_ptr;
    Inventory* inventory_ptr;
    Item* item_ptr;
public:
    Game(QList<Buttons*>&,QWidget*, Inventory*, Item*);
    void createGame();
    void stopGame();
    void closeGame();
};

#endif // GAME_H
