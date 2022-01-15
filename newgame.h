#ifndef NEWGAME_H
#define NEWGAME_H

#include <QPushButton>
#include <QDebug>
#include <buttons.h>

class NewGame: public QPushButton, public Buttons {
    Q_OBJECT;
public:
    NewGame(QWidget* parent);
    ~NewGame();
};


#endif // NEWGAME_H
