#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "staff.h"
#include "patient.h"
#include "roles.h"
#include "perm.h"
#include "cases.h"
#include "login.h"
#include "user.h"
#include <QDateTime>


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

    // manages Permissions in drop-down menue
    QObject::connect(ui->actionManage_Permissions, SIGNAL(triggered()), SLOT(managePerm()));

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

    // reflect possible changes
    sqlquery(false);

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
    {
        quitWin();
    }
    this->setWindowTitle("Hospital Management - User: "+CUserHandling::_current_user);

}

void CMainWindow::search()
{
    sqlquery(true);
}

void CMainWindow::sqlquery(bool filter)
{
    QString query = _casetreestr;

    QDate date = QDate::currentDate();
    QString fromDate;
    QString toDate;

    // calculate start and end dates for this week in the format yyyy-MM-dd (needed for SQLite date function)

    switch (date.dayOfWeek())
    {
    case 1:
        // Monday
        fromDate = date.toString("yyyy-MM-dd");
        toDate = date.addDays(6).toString("yyyy-MM-dd");
        break;
    case 2:
        // Tuesday
        fromDate = date.addDays(-1).toString("yyyy-MM-dd");
        toDate = date.addDays(5).toString("yyyy-MM-dd");
        break;
    case 3:
        // Wednesday
        fromDate = date.addDays(-2).toString("yyyy-MM-dd");
        toDate = date.addDays(4).toString("yyyy-MM-dd");
        break;
    case 4:
        // Thursday
        fromDate = date.addDays(-3).toString("yyyy-MM-dd");
        toDate = date.addDays(3).toString("yyyy-MM-dd");
        break;
    case 5:
        // Friday
        fromDate = date.addDays(-4).toString("yyyy-MM-dd");
        toDate = date.addDays(2).toString("yyyy-MM-dd");
        break;
    case 6:
        // Saturday
        fromDate = date.addDays(-5).toString("yyyy-MM-dd");
        toDate = date.addDays(1).toString("yyyy-MM-dd");
        break;
    case 7:
        // Sunday
        fromDate = date.addDays(-6).toString("yyyy-MM-dd");
        toDate = date.toString("yyyy-MM-dd");
        break;
    }

    //    query += " where date(substr(CaseEnd,7,4)||'-'||substr(CaseEnd,4,2)||'-'||substr(CaseEnd,1,2)) \
    //                        between date('" + fromDate + "') and date('" + toDate + "')";

    query += " where    date(substr(CaseEnd,7,4)||'-'||substr(CaseEnd,4,2)||'-'||substr(CaseEnd,1,2)) \
                        >= date('" + fromDate + "') or \
                        date(substr(CaseStart,7,4)||'-'||substr(CaseStart,4,2)||'-'||substr(CaseStart,1,2)) \
                        <= date('" + toDate + "')";

    if (filter)
    {
        QString name = ui->searchText->text();
        if (!name.isEmpty())
        {
            query += " and PatientLastName like '%" + name + "%' or PatientFirstName like '%" + name + "%'";
        }
    }

    query += " group by CaseID";

    // qDebug() << query;

    sql->setQuery(query);

    sql->setHeaderData(0, Qt::Horizontal, "PatientId");
    sql->setHeaderData(1, Qt::Horizontal, "Last Name");
    sql->setHeaderData(2, Qt::Horizontal, "First Name");
    sql->setHeaderData(3, Qt::Horizontal, "Case Start");
    sql->setHeaderData(4, Qt::Horizontal, "Case End");
    sql->setHeaderData(5, Qt::Horizontal, "Supervisor");
    sql->setHeaderData(6, Qt::Horizontal, "Description");

    ui->treeView->setModel(sql);
    ui->treeView->setAlternatingRowColors(true);
    ui->treeView->hideColumn(0);                   // hides the id column

}
