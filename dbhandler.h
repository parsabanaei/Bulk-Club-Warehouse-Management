#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QString>
#include <QtSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include "consts.h"



class DbHandler
{
private:
    QSqlDatabase mydb;
    QMessageBox msgBox;

public:
    DbHandler(QString dbPath, QString dbConnectionName);
    bool open();
    void close();

};

#endif // DBHANDLER_H
