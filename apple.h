#ifndef APPLE_H
#define APPLE_H
#include <QTableWidget>
#include <QHeaderView>
#include <QMediaPlayer>
#include <sqlitedatabase.h>
#include <QDebug>
#include <item.h>

class Apple: public QTableWidget, public Item{
   Q_OBJECT;
public:
   Apple(QWidget* parent = 0);
   ~Apple();
   QTableWidget * getItemTable()  override;
   bool getCellState()            override;
   void cellActivation()          override;
   void setCellState(bool)        override;
   QSize   getCellSize()          override;
   QMediaPlayer *getSound()const  override;
   void executeQuery();
private:
   QString path{":/new/prefix1/images/apple.jpg"};
   QIcon icon{ path };
   QSize size{ 150,150 };
   QString item_ = "apple";
   QString number = "1";
   QMediaPlayer* sound;
   SQLiteDataBase sql_database;
   bool state = false;
};

#endif // APPLE_H
