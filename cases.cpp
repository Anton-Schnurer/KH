#include "cases.h"
#include "ui_cases.h"
#include "mngcase.h"
#include "user.h"

CCases::CCases(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CCases)
{
    ui->setupUi(this);
    this->setWindowTitle("Manage Cases --- user: "+CUserHandling::_current_user);

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

    checkRole();
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

void CCases::newCase()                                      // opens the mngcase window for creating a new case
{
    CMngCase mngcase(this,0);
    mngcase.setModal(true);
    mngcase.show();
    mngcase.exec();

    sqlquery(false);

}

void CCases::editCase(const QModelIndex &index)             // opens the mngcase window to edit an existing case selected from the tableview
{
    int CaseID = ui->casesTableView->model()->index(index.row(), _CaseID).data().toInt();
    // open window
    CMngCase mngcase(this, CaseID);
    mngcase.setModal(true);
    mngcase.show();
    mngcase.exec();

    // update list of cases
    sqlquery(false);

}

void CCases::search()
{

    sqlquery(true);

}

void CCases::checkRole()
{
    // check if user is allowed to create a new case
    QString search_string="admin";
    if (CUserHandling::search_role_list(search_string))
    {
        // allowed
        return;
    }
    search_string="doctor";
    if (CUserHandling::search_role_list(search_string))
    {
        // allowed
        return;
    }
    search_string="nurse";
    if (CUserHandling::search_role_list(search_string))
    {
        // allowed
        return;
    }
    // not allowed to create new case
    ui->newCaseBtn->setDisabled(true);
}

void CCases::sqlquery(bool filter)
{
    QString query = _casestr;

    if (filter)                                                     // search function has been used
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


    // connect sql to view
    ui->casesTableView->setModel(sql);
    ui->casesTableView->setAlternatingRowColors(true);
    ui->casesTableView->hideColumn(0);                   // hides the id column
    ui->casesTableView->horizontalHeader()->setStretchLastSection(true);     // expands last column description to window-width
    //ui->casesTableView->resizeRowsToContents();

}
