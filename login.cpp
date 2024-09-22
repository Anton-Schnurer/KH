#include "login.h"
#include "ui_login.h"
#include "user.h"
#include <QMessageBox>

// make static variables and lists known

QString CUserHandling::_current_user;
int CUserHandling::_current_staffid;
QList<QString> CUserHandling::_perm_list;
QList<QString> CUserHandling::_role_list;


CLogin::CLogin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CLogin)
{
    ui->setupUi(this);
    this->setWindowTitle("Login/Change User");
    ui->passwdLineEdit->setEchoMode(QLineEdit::Password);

    QObject::connect(ui->LoginButton,SIGNAL(clicked()), SLOT(login()));
    QObject::connect(ui->CancelButton,SIGNAL(clicked()),SLOT(cancel()));

}

CLogin::~CLogin()
{
    delete ui;
}

void CLogin::login()
{
    QString user = ui->userLineEdit->text();
    QString pwd = ui->passwdLineEdit->text();
    QByteArray bytea = pwd.toUtf8();
    QString passhash = QCryptographicHash::hash(bytea,QCryptographicHash::Sha256).toHex();

    // query the database for user/pwd combination
    QSqlQuery sql;
    sql.prepare("select * from Staff where StaffUser = :user and StaffPWD = :pwd");
    sql.bindValue(":user", user);
    sql.bindValue(":pwd", passhash);
    sql.exec();
    // check if a record exists
    if (sql.next())
    {
        CUserHandling::_current_staffid=sql.value(0).toInt();   // set current staffid
        CUserHandling::_current_user=user;                      // set current username
        CUserHandling::fill_perm_list();                        // fill list of permissions for this user
        CUserHandling::fill_role_list();                        // fill list of roles for this user

    }
    else
    {
        // entry has not been found
        QMessageBox msg;
        msg.setWindowTitle("Login Error");
        msg.addButton("Ok", QMessageBox::YesRole);
        msg.exec();
        CUserHandling::_current_user=NULL;
        CUserHandling::_current_staffid=0;
    }


    cancel();
}

void CLogin::cancel()
{
    this->close();
}
