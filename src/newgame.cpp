#include "newgame.h"

NewGame::NewGame(QWidget *parent):QPushButton(parent) {
    setText(QString::fromUtf8("Новая игра"));
    setGeometry(QRect(120, 30, 150, 60));
    QFont font;
    font.setPointSize(12);
    setFont(font);
    show();
}

NewGame::~NewGame() {

}
