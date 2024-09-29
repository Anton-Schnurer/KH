#include "patient.h"
#include "ui_patient.h"
#include "mngpatient.h"
#include "user.h"

CPatient::CPatient(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CPatient)
{
    ui->setupUi(this);
    this->setWindowTitle("Manage Patients");

    // Manages the search button + field
    QObject::connect(ui->searchPBtn, SIGNAL(clicked()), SLOT(search()));

    // manage quit button
    QObject::connect(ui->quitBtn, SIGNAL(clicked()), SLOT(quitWin()));

    // manage new Patient button
    QObject::connect(ui->newPatientBtn, SIGNAL(clicked()), SLOT(newPatient()));

    // table view for Patients
    QObject::connect(ui->patientTableView, SIGNAL(clicked(const QModelIndex&)), SLOT(editPatient(const QModelIndex&)));

    sql = new QSqlQueryModel();
    sqlquery(false);

    // depending on the role of the current user certain ui elements are disabled
    checkRole();
}


CPatient::~CPatient()
{
    delete ui;
    delete sql;
}

void CPatient::quitWin()
{
    this->close();
}

void CPatient::newPatient()
{
    // open mngpatient window to create new patient
    CMngPatient mngpatient(this, 0);
    mngpatient.setModal(true);
    mngpatient.show();
    mngpatient.exec();

    // update the table view of patients
    sqlquery(false);

}

void CPatient::editPatient(const QModelIndex &index)
{
    // get the id of the record and call the mngstaff window
    int PatientID = ui->patientTableView->model()->index(index.row(), _PatientID).data().toInt();
    // open mngpatient window to edit selected patient
    CMngPatient mngpatient(this, PatientID);
    mngpatient.setModal(true);
    mngpatient.show();
    mngpatient.exec();

    // update the table view of patients
    sqlquery(false);

}

void CPatient::search()
{
    // search button has been selected
    sqlquery(true);
}

void CPatient::checkRole()
{
    // check if user is allowed to create a new patient
    QString search_string="default";
    if (CUserHandling::search_role_list(search_string))
    {
        // not allowed
        ui->newPatientBtn->setDisabled(true);
        return;
    }

}

void CPatient::sqlquery(bool filter)
{   
    QString query = _patientstr;

    if (filter)
    {
        // search field is filled
        QString name = ui->searchPlineEdit->text();
        if (!name.isEmpty())
        {
            query += " where PatientFirstName like '%" + name + "%' or PatientLastName like '%" + name + "%'";
        }
    }
    query += " group by PatientID";

    sql->setQuery(query);
    sql->setHeaderData(0, Qt::Horizontal, "Id");
    sql->setHeaderData(1, Qt::Horizontal, "Last Name");
    sql->setHeaderData(2, Qt::Horizontal, "First Name");
    sql->setHeaderData(3, Qt::Horizontal, "SSN");
    sql->setHeaderData(5, Qt::Horizontal, "Phone Number");

    // connect model to view
    ui->patientTableView->setModel(sql);
    ui->patientTableView->setAlternatingRowColors(true);
    ui->patientTableView->hideColumn(0);                   // hides the id column
}
