#include "inventorytable.h"

InventoryTable::InventoryTable(QWidget *parent): QTableWidget(parent) {
    if (columnCount() < 3)
           setColumnCount(3);
    if (rowCount() < 3)
           setRowCount(3);
    setStyleSheet(QString::fromUtf8("QTableWidget::item:selected{ background-color: rgba(155, 211, 250, 90); }"));
    setGeometry(QRect(40, 120, 480, 480));
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setDragEnabled(true);
    setDragDropMode(QAbstractItemView::DragDrop);
    setDefaultDropAction(Qt::IgnoreAction);
    setRowCount(3);
    setColumnCount(3);
    setDisabled(true);
    horizontalHeader()->setVisible(false);
    horizontalHeader()->setMinimumSectionSize(160);
    horizontalHeader()->setHighlightSections(false);
    verticalHeader()->setVisible(false);
    verticalHeader()->setDefaultSectionSize(160);
    verticalHeader()->setHighlightSections(false);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setAutoScroll(false);
    insertWidgetsToTable();
    initializationData();
    setCounters(parent);
    connect(this,&QTableWidget::cellChanged,this,&InventoryTable::cellChanged);
    connect(this,&QTableWidget::cellPressed,this,&InventoryTable::cellPressed);
}

void InventoryTable::setItemPointer(Item* item) {    //получить указатель на Item
    item_ = item;
    setCellSize();
    setIconSize(size);
}

void InventoryTable::setCellSize() {                  //установить размер ячейки инвентаря
    size.setWidth(item_->getCellSize().width());
    size.setHeight(item_->getCellSize().height());
}

void InventoryTable::mousePressEvent(QMouseEvent *event) {
    QTableWidget::mousePressEvent(event) ;

    if (event->button() == Qt::RightButton) {
        int x = this->currentRow();
        int y = this->currentColumn();
        useCurrenItem(x,y);
    }

}

void InventoryTable::useCurrenItem(int x,int y) {                  //использовать текущий предмет
    if (!this->item(x,y)->text().isEmpty()) {
        int count = getNumberItem(item(x,y)->text());
        QString str = getNameItem(item(x,y)->text());
        count -= 1;

        if (!count) {
            clearData(x,y);
            clearLabel(x,y);
            clearTableItem(x,y);
            item_->getSound()->play();
            return;
        }

        data[x][y]->number += count;
        item(x,y)->setText(str + " " + QString::number(count));
        setNewTextLabelData(x, y, QString::number(count));
        item_->getSound()->play();
    }

}

void InventoryTable::cellPressed(int x,int y) {                     //вызывается когда ячейка таблицы нажата
    mouse_pos_x = x;
    mouse_pos_y = y;
    item_->setCellState(false);
}

void InventoryTable::cellChanged(int x, int y) {

    Data data_item = itemCellInitialization();                      //получает данные предмета и инициализирует их значениями

    if (dragFromItem()) {                                           //разрешить перенос данных из таблицы предмета в таблицу инвентаря
        copingFromItemToInventory();                                //чтобы функция поняла из какой таблицы брать значения (инвентаря или предмета) текущий триггер устанавливается в положение false
        assignInventoryCell(x,y,data_item);                         //присвоить полученые данные ячейки в координатах x и y
        setTextLabelInventory(x,y);                                 //установить текст ярлыка инвентаря
        setTextWidgetInventory(x,y);                                //установить текст виджета инвентаря
        repaintCounters();                                          //перерисовать ярлыки
        executeQuery();
      // debug();
    }

   if (dragFromInvetory()) {                                         //разрешить перенос из таблицы инвентаря в таблицу инвентаря
     if (item(mouse_pos_x,mouse_pos_y)) {                            //запрещает дроп пустых ячеек
            if ((x == mouse_pos_x) && (y == mouse_pos_y)) {           //запрещает дроп ячейки на саму себя
                return;
            }
            Data inventory;
            assignNewValues(inventory);                                   //получить новые значения
            clearTableItem(mouse_pos_x,mouse_pos_y);                      //очистить виджет
            setNewValuesData(x,y,inventory,data_item);                    //установить новые значения
            clearData(mouse_pos_x,mouse_pos_y);                           //очистить старые данные
            clearLabel(mouse_pos_x,mouse_pos_y);                          //очистить старые ярлыки
            setNewTextLabelData(x,y,QString::number(data[x][y]->number));//установить новый текст ярлыка
            repaintCounters();                                            //перерисовать ярлыки
            setNewTextItem(x,y,data_item);                                //присвоить новый текст предмету
            executeQuery();                                               //выполнить запрос в sql database
        //  debug();
       }
    }
}

void InventoryTable::executeQuery() {         //функция запрос к базе данных
    sql_base.clearTable("Inventory");
    QString size = QString::number(columnCount()) + 'x' + QString::number(columnCount());
    for (int i = 0; i < rowCount(); ++i) {
        for (int j = 0; j < columnCount(); ++j) {
            QSqlQuery query;
            query.prepare("INSERT INTO Inventory (size,row,column,item,quantity)"
                           "VALUES (:size,:row,:column,:item,:quantity);");
            query.bindValue(":size", size);
            query.bindValue(":row", i);
            query.bindValue(":column", j);
            query.bindValue(":item",getNameItem(item(i,j)->text()));
            query.bindValue(":quantity",getNumberItem(item(i,j)->text()));
            query.exec();
        }
    }
}

void InventoryTable::setNewTextItem(int x,int y, Data data_item) {
             /*data[x][y]->type_item*/
    QString str = data_item.type_item  +" "+ QString::number(data[x][y]->number);
    item(x,y)->setText(str);
}

void InventoryTable::setNewTextLabelData(int x, int y, QString str) {           //установить новый текст ярлыку
    counters[x][y]->setText(str);
}

void InventoryTable::clearLabel(int x, int y) {                                 //очистить ярлык
    counters[x][y]->setText("0");
    counters[x][y]->hide();
}

void InventoryTable::clearData(int x, int y) {                                  //очистить данные
    data[x][y]->number = 0;
    data[x][y]->type_item = "";
}

void InventoryTable::setNewValuesData(int x,int y, Data inventory, Data item) { //установить новые значения
    data[x][y]->number += inventory.number;
    data[x][y]->type_item = item.type_item;
}

void InventoryTable::clearTableItem(int x,int y) {                             //очистить элемент таблицы
    item(x,y)->setText("");
    item(x,y)->setIcon(QIcon());
}

void InventoryTable::assignNewValues(Data& data) {                            //присвоить Data новые значения
    data.number = getNumberItem(item(mouse_pos_x,mouse_pos_y)->text());
    data.type_item = getNameItem(item(mouse_pos_x,mouse_pos_y)->text());
}

Data InventoryTable::itemCellInitialization() {                               //Инициализация исходными значениями ячейки предмета
    Data data;
    data.type_item = getNameItem(item_->getItemTable()->item(0,0)->text());
    data.number = getNumberItem(item_->getItemTable()->item(0,0)->text());
    return data;
}

void InventoryTable::assignInventoryCell(int pos_x,int pos_y,Data item) {    //Присваивание значения ячейки предмета  предмету находящемуся в инветаре
    data[pos_x][pos_y]->number += item.number;
    data[pos_x][pos_y]->type_item = item.type_item;
}

void InventoryTable::copingFromItemToInventory() {                           //копировать из ячейки итема в ячейку инвентаря
    item_->setCellState(false);
}

void InventoryTable::setTextLabelInventory(int pos_x,int pos_y) {           //установить текст ярлыка
    counters[pos_x][pos_y]->setText(QString::number(data[pos_x][pos_y]->number));
}

void InventoryTable::setTextWidgetInventory(int x,int y) {                  //установить текст виджета
    item(x,y)->setText(data[x][y]->type_item + " " + QString::number(data[x][y]->number));
}

QString InventoryTable::getNameItem(QString str) {                          //получить имя предмета из строки QString
   QString string;
   for (int i = 0; i < str.indexOf(" "); ++i ) {
       string += str[i];
    }
    return string;
}

int InventoryTable::getNumberItem(QString str) {                             //получить количество итемов из строки QString
    QString count;
        for (int i = str.indexOf(" ") + 1; i < str.size(); ++i ) {
            count += str[i];
        }
    return count.toInt();
}

void InventoryTable::insertWidgetsToTable() {                                 //заполнить таблицу виджетами
        for (int i = 0; i < rowCount(); ++i) {
            QTableWidgetItem* item;
            for (int j = 0; j < columnCount(); ++j) {
                item =  new QTableWidgetItem;
                setItem(i,j,item);
            }
         }
}

void InventoryTable::repaintCounters() {                                       //перерисовать ярлыки
    for (int i = 0; i < rowCount(); ++i) {
        for (int j = 0; j < columnCount(); ++j) {
             if (!counters[i][j]->text().toInt()) {
                counters[i][j]->hide();
             } else {
                counters[i][j]->show();
             }
        }
    }
}

void InventoryTable::setCounters(QWidget* parent) {            //сохранить ярлыки в контейнере

    int x = pos().x() + 125;                                  //x = положение таблицы относительно окна + расстояние в ячейке
    int y = pos().y() + 135;                                  //y = положение таблицы относительно окна + расстояние в ячейке

     for (int i = 0; i < rowCount(); ++i) {
          QVector<QLabel*>vec;
          for (int j = 0; j < columnCount(); ++j) {
              QLabel* label = new QLabel(parent);
              label->setText("0");
              label->hide();
              label->setGeometry(QRect(x, y, 35, 15));
              vec.push_back(label);
              x += 165;
          }
          counters.push_back(vec);
              x = 165;
              y += 160;
    }

}

void InventoryTable::initializationData() {                 //инициализация данных
    for (int i = 0; i < rowCount(); ++i) {
         QVector<Data*>vec;
         for (int j = 0; j < columnCount(); ++j) {
             Data* data = new Data();
             vec.push_back(data);
         }
         data.push_back(vec);
   }
}

QTableWidget* InventoryTable::getTable() {                       //получить таблицу
    return this;
}

InventoryTable::~InventoryTable() {

}
                                                                //функция для дебага
void InventoryTable::debug() {
            QDebug debug = qDebug();
            debug.nospace();

            qDebug() <<"#######DATA#########";
            //################################ ОТОБРАЖЕНИЕ ДАННЫХ #######################
            for (int i = 0; i < rowCount(); ++i) {
                 for (int j = 0; j < columnCount(); ++j) {
                    debug  << data[i][j]->number;
                 }
                    debug <<'\n';
            }

            qDebug() <<"#######COUNTERS#########";
            //################################ ОТОБРАЖЕНИЕ ЯРЛЫКОВ #######################
                 for (int i = 0; i < rowCount(); ++i) {
                      for (int j = 0; j < columnCount(); ++j){
                              debug  << counters[i][j]->text();
                           }
                              debug <<'\n';
            }
            qDebug() <<"#######ITEMS#########";
            //################################ ОТОБРАЖЕНИЕ ИТЕМОВ ТАБЛИЦЫ #######################
                 for (int i = 0; i < rowCount(); ++i) {
                     for (int j = 0; j < columnCount(); ++j){
                            debug << item(i,j)->text();
                       }
                        debug <<'\n';
                  }
}






































































