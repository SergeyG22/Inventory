#include "exit.h"

Exit::Exit(QWidget *parent):QPushButton(parent) {
    setText(QString::fromUtf8("Выход"));
    setGeometry(QRect(300, 30, 150, 60));
    QFont font;
    font.setPointSize(12);
    setFont(font);
    show();
}

Exit::~Exit() {

}
