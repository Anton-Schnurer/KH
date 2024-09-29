#include "perm.h"
#include "ui_perm.h"
#include "mngperm.h"
#include "user.h"

CPerm::CPerm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CPerm)
{
    ui->setupUi(this);
    this->setWindowTitle("Manage Permissions");

    // Manages the search button + field
    QObject::connect(ui->searchPBtn, SIGNAL(clicked()), SLOT(search()));

    // manage quit button
    QObject::connect(ui->quitBtn, SIGNAL(clicked()), SLOT(quitWin()));

    // manage new button
    QObject::connect(ui->newPBtn, SIGNAL(clicked()), SLOT(newPerm()));

    // table view for Permissions
    QObject::connect(ui->PermTableView, SIGNAL(clicked(const QModelIndex&)), SLOT(editPerm(const QModelIndex&)));

    sql = new QSqlQueryModel();
    sqlquery(false);

    checkPerm();
}

CPerm::~CPerm()
{
    delete ui;
    delete sql;
}

void CPerm::quitWin()
{
    this->close();
}

void CPerm::newPerm()
{
    // opens mngperm window to create new permission
    CMngPerm mngperm(this,0);
    mngperm.setModal(true);
    mngperm.show();
    mngperm.exec();

    // update table view of permissions
    sqlquery(false);

}

void CPerm::editPerm(const QModelIndex &index)
{
    // get the id of the record and call the mngperm window
    int PermID = ui->PermTableView->model()->index(index.row(), _PermID).data().toInt();
    // open mngperm window to edit selected permission
    CMngPerm mngperm(this, PermID);
    mngperm.setModal(true);
    mngperm.show();
    mngperm.exec();

    // update table view of permissions
    sqlquery(false);

}

void CPerm::search()
{

    // search button has been selected
    sqlquery(true);

}

void CPerm::checkPerm()
{
    QString search_string="sysadmin";
    if (CUserHandling::search_perm_list(search_string))
    {
        // only sysadmins can create new entries
        return;
    }
    // not sysadmin -> not allowed to create new entry
    ui->newPBtn->setEnabled(false);
}

void CPerm::sqlquery(bool filter)
{

    QString query = _permissionstr;

    if (filter)
    {
        QString name = ui->searchPlineEdit->text();
        if (!name.isEmpty())
        {
            query += " where PermName like '%" + name + "%'";
        }
    }

    sql->setQuery(query);
    sql->setHeaderData(0, Qt::Horizontal, "Id");
    sql->setHeaderData(1, Qt::Horizontal, "Name");
    sql->setHeaderData(2, Qt::Horizontal, "Description");

    // connect model to view
    ui->PermTableView->setModel(sql);
    ui->PermTableView->setAlternatingRowColors(true);
    ui->PermTableView->hideColumn(0);                                       // hides the id column
    ui->PermTableView->horizontalHeader()->setStretchLastSection(true);     // expands last column description to window-width

}
