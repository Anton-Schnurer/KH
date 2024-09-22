#include "roles.h"
#include "ui_roles.h"
#include "mngroles.h"
#include "user.h"

CRoles::CRoles(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CRoles)
{
    ui->setupUi(this);
    this->setWindowTitle("Manage Roles");

    // manage quit button
    QObject::connect(ui->quitBtn, SIGNAL(clicked()), SLOT(quitWin()));

    // manage new Role button
    QObject::connect(ui->newRBtn, SIGNAL(clicked()), SLOT(newRole()));

    // Manages the search button + field
    QObject::connect(ui->searchRBtn, SIGNAL(clicked()), SLOT(search()));

    // table view for Permissions
    QObject::connect(ui->rolesTableView, SIGNAL(clicked(const QModelIndex&)), SLOT(editRole(const QModelIndex&)));

    sql = new QSqlQueryModel();
    sqlquery(false);

    checkPerm();
}

CRoles::~CRoles()
{
    delete ui;
    delete sql;
}

void CRoles::quitWin()
{
    this->close();
}

void CRoles::newRole()
{
    CMngRoles mngrole(this,0);
    mngrole.setModal(true);
    mngrole.show();
    mngrole.exec();

    sqlquery(false);

}

void CRoles::editRole(const QModelIndex &index)
{
    // get the id of the record and call the mngperm window
    int RoleID = ui->rolesTableView->model()->index(index.row(), _RoleID).data().toInt();
    // open window
    CMngRoles mngrole(this, RoleID);
    mngrole.setModal(true);
    mngrole.show();
    mngrole.exec();

    // update list of staff
    sqlquery(false);

}

void CRoles::search()
{
    // search button has been selected
    sqlquery(true);
}

void CRoles::checkPerm()
{
    QString search_string="sysadmin";
    if (CUserHandling::search_perm_list(search_string))
    {
        // only sysadmins can create new entries
        return;
    }
    // not sysadmin -> not allowed to create new entry
    ui->newRBtn->setEnabled(false);
}

void CRoles::sqlquery(bool filter)
{
    QString query = _rolestr;

    if (filter)
    {
        QString name = ui->searchRlineEdit->text();
        if (!name.isEmpty())
        {
            query += " where RoleName like '%" + name + "%'";
        }
    }
    // query += " group by PermID";

    sql->setQuery(query);
    sql->setHeaderData(0, Qt::Horizontal, "Id");
    sql->setHeaderData(1, Qt::Horizontal, "Name");
    sql->setHeaderData(2, Qt::Horizontal, "Description");

    // connect sql to view
    ui->rolesTableView->setModel(sql);
    ui->rolesTableView->setAlternatingRowColors(true);
    ui->rolesTableView->hideColumn(0);                   // hides the id column
    ui->rolesTableView->horizontalHeader()->setStretchLastSection(true);     // expands last column description to window-width

}
