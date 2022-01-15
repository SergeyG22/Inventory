#include "menu.h"

Menu::Menu(QWidget *parent):QPushButton(parent) {
    setText(QString::fromUtf8("Главное меню"));
    setGeometry(QRect(590, 390, 150, 60));
    QFont font;
    font.setPointSize(12);
    setFont(font);
    setEnabled(false);
    show();
}

Menu::~Menu(){

}
