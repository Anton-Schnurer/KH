#include "staff.h"
#include "ui_staff.h"
#include "mngstaff.h"
#include "user.h"

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
    QObject::connect(ui->stafftableView, SIGNAL(clicked(const QModelIndex&)), SLOT(editStaff(const QModelIndex&)));

    sql = new QSqlQueryModel();
    sqlquery(false);

    // depending on the role of current user certain UI elements will be disabled
    checkRole();
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
    // open mngstaff window to create new staff
    CMngStaff mngstaff(this, 0);
    mngstaff.setModal(true);
    mngstaff.show();
    mngstaff.exec();

    // update list of staff
    sqlquery(false);
}

void CStaff::editStaff(const QModelIndex & index)
{
    // get the id of the record and call the mngstaff window
    int StaffID = ui->stafftableView->model()->index(index.row(), _StaffID).data().toInt();
    // open mngstaff window to edit selected staff
    CMngStaff mngstaff(this, StaffID);
    mngstaff.setModal(true);
    mngstaff.show();
    mngstaff.exec();

    // update list of staff
    sqlquery(false);
}

void CStaff::search()
{
    // search button has been selected
    sqlquery(true);
}

void CStaff::checkRole()
{
    // check if current user is allowed to create a new staff member

    // admin is allowed
    QString search_string="admin";
    if (CUserHandling::search_role_list(search_string))
    {
        return;
    }
    // not admin -> not allowed to create new staff member
    ui->newStaffBtn->setDisabled(true);

}

void CStaff::sqlquery(bool filter)
{
    QString query = _staffstr;

    if (filter)
    {
        QString name = ui->searchSlineEdit->text();
        if (!name.isEmpty())
        {
        query += " where StaffFirstName like '%" + name + "%' or StaffLastName like '%" + name + "%'";
        }
    }
    query += " group by StaffID";

    sql->setQuery(query);
    sql->setHeaderData(0, Qt::Horizontal, "Id");
    sql->setHeaderData(1, Qt::Horizontal, "Username");
    sql->setHeaderData(2, Qt::Horizontal, "Password");
    sql->setHeaderData(3, Qt::Horizontal, "First Name");
    sql->setHeaderData(4, Qt::Horizontal, "Last Name");
    sql->setHeaderData(5, Qt::Horizontal, "Phone Number");
    sql->setHeaderData(6, Qt::Horizontal, "Permissions");
    sql->setHeaderData(7, Qt::Horizontal, "Roles");

    // connect model to view
    ui->stafftableView->setModel(sql);
    ui->stafftableView->setAlternatingRowColors(true);
    ui->stafftableView->hideColumn(0);                   // hides the id column
    ui->stafftableView->hideColumn(2);                   // hides the password

}

