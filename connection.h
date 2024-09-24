#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtSql>
#include <QMessageBox>
#include <QDir>
#include <QFile>

static bool createConnection(QString dbname)
{
    // define Database
    // qDebug() << QSqlDatabase::drivers();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    if (dbname.isEmpty())
    {
        // db.setDatabaseName("KH.db");
        QMessageBox msg;
        msg.setWindowTitle("No database path/name set");
        msg.setText("Error");
        msg.addButton("Ok", QMessageBox::YesRole);
        msg.exec();
        return false;
    }
    else
    {
        QFile File(dbname);
        if (!File.exists())
        {
            QMessageBox msg;
            msg.setText("Error finding database file: " + dbname);
            msg.setWindowTitle("Error");
            msg.addButton("Ok", QMessageBox::YesRole);
            msg.exec();
            return false;
        }
        db.setDatabaseName(dbname);
    }

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
