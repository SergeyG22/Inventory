#ifndef MENU_H
#define MENU_H
#include <QPushButton>
#include <QDebug>
#include <buttons.h>


class Menu: public QPushButton, public Buttons {
    Q_OBJECT;
public:
    Menu(QWidget* parent);
    ~Menu();
};

#endif // MENU_H
