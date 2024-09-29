#include "mainwindow.h"
#include "connection.h"
#include "login.h"
#include "config.h"
#include "user.h"
#include <QApplication>



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    // read db path/name from config
    QString dbname=NULL;
    CConfig config;
    dbname = config.read_config();

    if (dbname.isEmpty())
    {
        qDebug() << "dbname is not set";
        return EXIT_FAILURE;
    }

    // create db connection
    if (!createConnection(dbname))
    {
        qDebug() << "database:" + dbname + " could not be opened";
        return EXIT_FAILURE;
    }

    // open login window
    CLogin login;
    login.setModal(true);
    login.show();
    login.exec();

    // login was unsuccessful
    if (CUserHandling::_current_user.isEmpty())
    {
        return EXIT_FAILURE;
    }

    // open the mainwindow
    CMainWindow w;
    w.show();
    return a.exec();
}
