#include "perm.h"
#include "ui_perm.h"
#include "mngperm.h"

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
    CMngPerm mngperm(this,0);
    mngperm.setModal(true);
    mngperm.show();
    mngperm.exec();

    // update the table view
    sqlquery(false);

}

void CPerm::editPerm(const QModelIndex &index)
{
    // get the id of the record and call the mngperm window
    int PermID = ui->PermTableView->model()->index(index.row(), _PermID).data().toInt();
    // open window
    CMngPerm mngperm(this, PermID);
    mngperm.setModal(true);
    mngperm.show();
    mngperm.exec();

    // update list of staff
    sqlquery(false);

}

void CPerm::search()
{

    // search button has been selected
    sqlquery(true);

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
    // query += " group by PermID";

    sql->setQuery(query);
    sql->setHeaderData(0, Qt::Horizontal, "Id");
    sql->setHeaderData(1, Qt::Horizontal, "Name");
    sql->setHeaderData(2, Qt::Horizontal, "Description");

    // Zuweisung zur Table
    ui->PermTableView->setModel(sql);
    // Verschönerung
    ui->PermTableView->setAlternatingRowColors(true);
    ui->PermTableView->hideColumn(0);                   // hides the id column
    ui->PermTableView->horizontalHeader()->setStretchLastSection(true);     // expands last column description to window-width

}
