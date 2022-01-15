#ifndef INVENTORY_H
#define INVENTORY_H
#include <QTableWidget>
#include <item.h>

class Inventory {

public:
    Inventory() {};
    virtual QTableWidget* getTable() = 0;
    virtual void setItemPointer(Item* item) = 0;
    virtual ~Inventory() {}
};

#endif // INVENTORY_H
