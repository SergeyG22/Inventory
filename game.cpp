#include "game.h"

Game::Game(QList<Buttons*>& buttons,QWidget* window,Inventory* inventory, Item* item):button_ptr(buttons),
    window_ptr(window),inventory_ptr(inventory),item_ptr(item) {

}

void Game::createGame() {
    dynamic_cast<Exit*>(button_ptr.at(2))->hide();
    dynamic_cast<NewGame*>(button_ptr.at(0))->hide();
    dynamic_cast<Menu*>(button_ptr.at(1))->setEnabled(true);
    dynamic_cast<InventoryTable*>(inventory_ptr)->setEnabled(true);
    dynamic_cast<Apple*>(item_ptr)->setEnabled(true);
}

void Game::stopGame() {
    dynamic_cast<Exit*>(button_ptr.at(2))->show();
    dynamic_cast<NewGame*>(button_ptr.at(0))->show();
    dynamic_cast<Menu*>(button_ptr.at(1))->setEnabled(false);
    dynamic_cast<InventoryTable*>(inventory_ptr)->setEnabled(false);
    dynamic_cast<Apple*>(item_ptr)->setEnabled(false);
}

void Game::closeGame() {
    window_ptr->close();
}
