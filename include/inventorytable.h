#ifndef INVENTORYTABLE_H
#define INVENTORYTABLE_H
#include <inventory.h>
#include <qdebug.h>
#include <QTableWidget>
#include <QLabel>
#include <QHeaderView>
#include <apple.h>
#include <data.h>
#include <QMouseEvent>
#include <iostream>
#include <sqlitedatabase.h>

class InventoryTable: public QTableWidget, public Inventory{
   Q_OBJECT;
   Item* item_;
   QVector<QVector<QLabel*>>counters;
   QVector<QVector<Data*>>data;
   QSize size;
   SQLiteDataBase sql_base;
   int mouse_pos_x;
   int mouse_pos_y;
public:
    InventoryTable(QWidget* parent);
    ~InventoryTable();
    QTableWidget * getTable() override;
    Data itemCellInitialization();
    QString getNameItem(QString str);
    void mousePressEvent(QMouseEvent* )override;
    void debug();
    void executeQuery();
    void setCellSize();
    void clearData(int,int);
    void clearLabel(int,int);
    void cellChanged(int,int);
    void cellPressed(int,int);
    void repaintCounters();
    void setCounters(QWidget*);
    void insertWidgetsToTable();
    void clearTableItem(int,int);
    void assignNewValues(Data&);
    void initializationData();
    int  getNumberItem(QString str);
    void setNewTextItem(int,int,Data);
    void copingFromItemToInventory();
    void setNewTextLabelData(int,int,QString);
    void setTextLabelInventory(int,int);
    void setTextWidgetInventory(int,int);
    void assignInventoryCell(int,int,Data);
    void setItemPointer(Item* item)override;
    void setNewValuesData(int,int,Data,Data);
    inline bool dragFromItem(){  return item_->getCellState(); };
    inline bool dragFromInvetory(){ return !item_->getCellState(); };
    void useCurrenItem(int,int);
};

#endif // INVENTORYTABLE_H
