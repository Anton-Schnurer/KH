#include "mainwindow.h"
#include "connection.h"
#include "login.h"
#include "user.h"

#include <QApplication>



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    // create db connection
    if (!createConnection())
    {
        return EXIT_FAILURE;
    }

    // open login window
    CLogin login;
    login.setModal(true);
    login.show();
    login.exec();
    if (CUserHandling::_current_user.isEmpty())
    {
        return EXIT_FAILURE;
    }

    CMainWindow w;
    w.show();
    return a.exec();
}
