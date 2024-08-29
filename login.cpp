#include "login.h"
#include "ui_login.h"
#include <QMessageBox>

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
        _user = user;
    }
    else
    {
        QString a;
        // entry has not been found
        QMessageBox msg;
        msg.setText(a.number(sql.size())+" "+user+" "+pwd+" "+passhash);
        msg.setWindowTitle("Login Error");
        msg.addButton("Ok", QMessageBox::YesRole);
        msg.exec();
    }


    //if (user == "sysadmin" && passhash == "03ac674216f3e15c761ee1a5e255f067953623c8b388b4459e13f978d7c846f4")
    //{
    //    // ueberpruefung ist okay
    //    _user = user;
    //}
    cancel();
}

void CLogin::cancel()
{
    this->close();
}
