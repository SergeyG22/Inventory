#include "sqlitedatabase.h"

SQLiteDataBase::SQLiteDataBase() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString path = "С:\\database\\DataBase.db";
    db.setDatabaseName(path);
    if(!db.open()){
        qDebug() << db.lastError().text();
    }
}

void SQLiteDataBase::writeToDataBase(const QString request) {     //записать в базу данных
    QSqlQuery query;
    query.exec(request);
}

void SQLiteDataBase::clearTable(const QString table){             //очистить таблицу
    QSqlQuery query;
    query.exec("DELETE FROM " + table);
}

void SQLiteDataBase::closeDataBase() {                            //закрыть базу данных
    db.close();
}
