#ifndef ITEM_H
#define ITEM_H
#include <QTableWidget>
#include <QMediaPlayer>

class Item{

public:
    virtual ~Item(){ };
    virtual QTableWidget *getItemTable() = 0;
    virtual bool getCellState() = 0;
    virtual QSize getCellSize() = 0;
    virtual void cellActivation() = 0;
    virtual void setCellState(bool) = 0;
    virtual QMediaPlayer* getSound()const{ return nullptr;};
};

#endif // ITEM_H
