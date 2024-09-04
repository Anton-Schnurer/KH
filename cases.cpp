#include "cases.h"
#include "ui_cases.h"
#include "mngcase.h"

CCases::CCases(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CCases)
{
    ui->setupUi(this);
    this->setWindowTitle("Manage Cases");

    // manage quit button
    QObject::connect(ui->quitBtn, SIGNAL(clicked()), SLOT(quitWin()));

    // manage new Role button
    QObject::connect(ui->newCaseBtn, SIGNAL(clicked()), SLOT(newCase()));

    // Manages the search button + field
    QObject::connect(ui->searchPBtn, SIGNAL(clicked()), SLOT(search()));

    // table view for Permissions
    QObject::connect(ui->casesTableView, SIGNAL(clicked(const QModelIndex&)), SLOT(editCase(const QModelIndex&)));

    sql = new QSqlQueryModel();
    sqlquery(false);

}

CCases::~CCases()
{
    delete ui;
    delete sql;
}

void CCases::quitWin()
{
    this->close();
}

void CCases::newCase()
{
    CMngCase mngcase(this,0);
    mngcase.setModal(true);
    mngcase.show();
    mngcase.exec();

    sqlquery(false);

}

void CCases::editCase(const QModelIndex &index)
{
    int CaseID = ui->casesTableView->model()->index(index.row(), _CaseID).data().toInt();
    // open window
    CMngCase mngcase(this, CaseID);
    mngcase.setModal(true);
    mngcase.show();
    mngcase.exec();

    // update list of staff
    sqlquery(false);

}

void CCases::search()
{

    sqlquery(true);

}

void CCases::sqlquery(bool filter)
{
    QString query = _casestr;

    if (filter)
    {
        QString name = ui->searchPlineEdit->text();
        if (!name.isEmpty())
        {
            query += " where PatientLastName like '%" + name + "%' or PatientFirstName like '%" + name + "%'";
        }
    }
    // query += " group by PermID";

    sql->setQuery(query);
    sql->setHeaderData(0, Qt::Horizontal, "Id");
    sql->setHeaderData(1, Qt::Horizontal, "Last Name");
    sql->setHeaderData(2, Qt::Horizontal, "First Name");
    sql->setHeaderData(3, Qt::Horizontal, "Case Start");
    sql->setHeaderData(4, Qt::Horizontal, "Case End");
    sql->setHeaderData(5, Qt::Horizontal, "Description");


    // Zuweisung zur Table
    ui->casesTableView->setModel(sql);
    // Verschönerung
    ui->casesTableView->setAlternatingRowColors(true);
    ui->casesTableView->hideColumn(0);                   // hides the id column
    ui->casesTableView->horizontalHeader()->setStretchLastSection(true);     // expands last column description to window-width

}
