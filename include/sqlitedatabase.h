#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>
#include <QApplication>
#include <QStandardPaths>

class SQLiteDataBase {
    QSqlDatabase db;
public:
    SQLiteDataBase();
    void writeToDataBase(const QString);
    void closeDataBase();
    void clearTable(const QString);
};

#endif // SQLITEDATABASE_H
