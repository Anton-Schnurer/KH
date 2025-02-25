#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QSqlQuery>
#include <QCryptographicHash>

namespace Ui {
class CLogin;
}

class CLogin : public QDialog
{
    Q_OBJECT

public:
    explicit CLogin(QWidget *parent = nullptr);
    ~CLogin();

public slots:
    void login();                           // connected to login button, compares username/pwd to db-entry
    void cancel();                          // close the login window

private:
    Ui::CLogin *ui;

};

#endif // LOGIN_H
