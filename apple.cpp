#include "apple.h"

Apple::Apple(QWidget *parent):QTableWidget(parent) {
    if (columnCount() < 1)
            setColumnCount(1);
    if (rowCount() < 1)
            setRowCount(1);
    setGeometry(QRect(580, 150, 160, 160));
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setDragEnabled(true);
    setDragDropMode(QAbstractItemView::DragOnly);
    setDefaultDropAction(Qt::IgnoreAction);
    setRowCount(1);
    setColumnCount(1);
    setDisabled(true);
    horizontalHeader()->setVisible(false);
    horizontalHeader()->setMinimumSectionSize(160);
    horizontalHeader()->setHighlightSections(false);
    verticalHeader()->setVisible(false);
    verticalHeader()->setDefaultSectionSize(160);
    verticalHeader()->setHighlightSections(false);
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    QTableWidgetItem *item = new QTableWidgetItem();
    icon.pixmap(size,QIcon::Mode::Normal);
    item->setIcon(icon);
    item->setText(item_ +" "+ number);
    setItem(0,0,item);
    setIconSize(size);
    sound = new QMediaPlayer;
    sound->setMedia(QUrl("qrc:/new/prefix1/sound/bite.wav"));
    executeQuery();
    connect(this,&QTableWidget::cellPressed,this,&Apple::cellActivation);
}

bool Apple::getCellState() {       //получить состояние ячейки
    return state;
};

void Apple::cellActivation() {    //активирует ячейку при нажатии
    state = true;
};

void Apple::setCellState(bool state_) {  //отключить ячейку
    state = state_;
};

QSize Apple::getCellSize() {           //размер ячейки
    return size;
};

void Apple::executeQuery() {             //выполнить запрос к базе данных

    sql_database.clearTable("Item");

    QString request = QString ("INSERT INTO Item(type,image) VALUES ('%1', '%2');").arg(item_).arg(path);
    sql_database.writeToDataBase(request);
    sql_database.closeDataBase();
}

Apple::~Apple() {

}

QTableWidget* Apple::getItemTable() {     //получить итем таблицы
    return this;
}

QMediaPlayer* Apple::getSound()const {     //получить звук
    return sound;
}

