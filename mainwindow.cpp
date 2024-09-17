#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "staff.h"
#include "patient.h"
#include "roles.h"
#include "perm.h"
#include "cases.h"
#include "login.h"
#include "user.h"


CMainWindow::CMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CMainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Hospital Management --- user: "+CUserHandling::_current_user);
    //this->setWindowTitle("Hospital Management --- user: "+UserHandling._current_user);

    // manages Staff in drop-down menue and the button
    QObject::connect(ui->manageStaff, SIGNAL(clicked()), SLOT(manageStaff()));
    QObject::connect(ui->actionManage_Staff, SIGNAL(triggered()), SLOT(manageStaff()));

    // manages Patient in drop-down menue and the button
    QObject::connect(ui->managePatients, SIGNAL(clicked()), SLOT(managePatients()));
    QObject::connect(ui->actionManage_Patients, SIGNAL(triggered()), SLOT(managePatients()));

    // manages Cases in drop-down menue and the button
    QObject::connect(ui->manageCases, SIGNAL(clicked()), SLOT(manageCases()));
    QObject::connect(ui->actionManage_Cases, SIGNAL(triggered()), SLOT(manageCases()));

    // manages Quit in drop-down menue and the button
    QObject::connect(ui->quitBtn, SIGNAL(clicked()), SLOT(quitWin()));
    QObject::connect(ui->actionQuit, SIGNAL(triggered()), SLOT(quitWin()));

    // manages Roles in drop-down menue
    QObject::connect(ui->actionManage_Roles, SIGNAL(triggered()), SLOT(manageRoles()));

    // grey out manage roles in drop-down menue
    // ui->actionManage_Roles->setEnabled(false);

    // manages Permissions in drop-down menue
    QObject::connect(ui->actionManage_Permissions, SIGNAL(triggered()), SLOT(managePerm()));

    // grey out manage permissions in drop-down menue
    // ui->actionManage_Permissions->setEnabled(false);

    // manages ChangeUser in drop-down menue and the button
    QObject::connect(ui->changeUser, SIGNAL(clicked()), SLOT(changeUser()));
    QObject::connect(ui->actionChange_User, SIGNAL(triggered()), SLOT(changeUser()));

    // Manages the search button + field
    QObject::connect(ui->searchBtn, SIGNAL(clicked()), SLOT(search()));


    sql = new QSqlQueryModel();
    sqlquery(false);

}

CMainWindow::~CMainWindow()
{
    delete ui;
    delete sql;
}

void CMainWindow::manageStaff()
{
    CStaff staffwin;
    staffwin.setModal(true);
    staffwin.show();
    staffwin.exec();
}

void CMainWindow::managePatients()
{
    CPatient patientwin;
    patientwin.setModal(true);
    patientwin.show();
    patientwin.exec();
}

void CMainWindow::manageCases()
{
    CCases caseswin;
    caseswin.setModal(true);
    caseswin.show();
    caseswin.exec();
}

void CMainWindow::manageRoles()
{
    CRoles roleswin;
    roleswin.setModal(true);
    roleswin.show();
    roleswin.exec();
}

void CMainWindow::managePerm()
{
    CPerm permwin;
    permwin.setModal(true);
    permwin.show();
    permwin.exec();
}

void CMainWindow::quitWin()
{
    this->close();
}

void CMainWindow::changeUser()
{
    // open login and check if user has been changed or not
    CLogin login;
    login.setModal(true);
    login.show();
    login.exec();
    if (CUserHandling::_current_user.isEmpty())
    //if (UserHandling._current_user.isEmpty())
    {
        quitWin();
    }
    this->setWindowTitle("Hospital Management --- user: "+CUserHandling::_current_user);
    //this->setWindowTitle("Hospital Management --- user: "+UserHandling._current_user);

}

void CMainWindow::search()
{
    sqlquery(true);
}

void CMainWindow::sqlquery(bool filter)
{
    QString query = _casetreestr;

    if (filter)
    {
        QString name = ui->searchText->text();
        if (!name.isEmpty())
        {
            query += " where PatientLastName like '%" + name + "%' or PatientFirstName like '%" + name + "%'";
        }
    }
    // query += " group by PermID";

    sql->setQuery(query);

    sql->setHeaderData(0, Qt::Horizontal, "Last Name");
    sql->setHeaderData(1, Qt::Horizontal, "First Name");
    sql->setHeaderData(2, Qt::Horizontal, "Case Id");
    sql->setHeaderData(3, Qt::Horizontal, "Case Start");
    sql->setHeaderData(4, Qt::Horizontal, "Case End");
    sql->setHeaderData(5, Qt::Horizontal, "Description");


    // Zuweisung zur Table
    ui->treeView->setModel(sql);
    // Verschönerung
    ui->treeView->setAlternatingRowColors(true);
    //ui->treeView->hideColumn(0);                   // hides the id column

}
