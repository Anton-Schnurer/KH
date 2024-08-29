#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtSql>
#include <QMessageBox>

static bool createConnection()
{
    // define Database
    // qDebug() << QSqlDatabase::drivers();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    // change in the future to read from an config file
    db.setDatabaseName("C:/Users/anton/Documents/_projects/C++/_KH proj/KH/KH.db");
    if (!db.open())
    {
        // error opening database
        QMessageBox msg;
        msg.setText("Error opening database");
        msg.setWindowTitle("Error");
        msg.addButton("Ok", QMessageBox::YesRole);
        msg.exec();
        return false;
    }
    return true;
}

#endif // CONNECTION_H
