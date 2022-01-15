#ifndef EXIT_H
#define EXIT_H
#include <QPushButton>
#include <QDebug>
#include <buttons.h>

class Exit: public QPushButton, public Buttons {
    Q_OBJECT;
public:
    Exit(QWidget* parent);
    ~Exit();
};

#endif // EXIT_H
