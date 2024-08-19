#include "staff.h"
#include "ui_staff.h"
#include "mngstaff.h"

CStaff::CStaff(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CStaff)
{
    ui->setupUi(this);
    this->setWindowTitle("Manage Staff");

    // Manages the search button + field
    QObject::connect(ui->searchBtn, SIGNAL(clicked()), SLOT(search()));

    // Manages the Quit btn
    QObject::connect(ui->quitBtn, SIGNAL(clicked()), SLOT(quitWin()));

    // Manages the new staff btn
    QObject::connect(ui->newStaffBtn, SIGNAL(clicked()), SLOT(newStaff()));

    // table view for staff
    QObject::connect(ui->tableView, SIGNAL(clicked(const QModelIndex&)), SLOT(editStaff(const QModelIndex&)));

    sql = new QSqlQueryModel();
    sqlquery(false);
}

CStaff::~CStaff()
{
    delete ui;
    delete sql;
}

void CStaff::quitWin()
{
    this->close();
}

void CStaff::newStaff()
{
    CMngStaff mngstaff(this, 0);
    mngstaff.setModal(true);
    mngstaff.show();
    mngstaff.exec();

}

void CStaff::editStaff(const QModelIndex &)
{
    // get the id of the record and call the mngstaff window
}

void CStaff::search()
{
    // search button has been selected
    sqlquery(true);
}

void CStaff::sqlquery(bool filter)
{
    QString query = "select * from staff";

    if (filter)
    {
        QString name = ui->searchSlineEdit->text();
        if (!name.isEmpty())
        {
        query += " where StaffFirstName like '%" + name + "%' or StaffLastName like '%" + name + "%'";
        }
    }
    sql->setQuery(query);
    sql->setHeaderData(0, Qt::Horizontal, "Id");
    sql->setHeaderData(1, Qt::Horizontal, "Username");
    sql->setHeaderData(2, Qt::Horizontal, "Password");
    sql->setHeaderData(3, Qt::Horizontal, "First Name");
    sql->setHeaderData(4, Qt::Horizontal, "Last Name");
    sql->setHeaderData(5, Qt::Horizontal, "Phone Number");

    // Zuweisung zur Table
    ui->tableView->setModel(sql);
    // Verschönerung
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(2);

}

