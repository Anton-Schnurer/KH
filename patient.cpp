#include "patient.h"
#include "ui_patient.h"
#include "mngpatient.h"

CPatient::CPatient(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CPatient)
{
    ui->setupUi(this);
    this->setWindowTitle("Manage Patients");

    // manage quit button
    QObject::connect(ui->quitBtn, SIGNAL(clicked()), SLOT(quitWin()));

    // manage new button
    QObject::connect(ui->newPatientBtn, SIGNAL(clicked()), SLOT(newPatient()));
}

CPatient::~CPatient()
{
    delete ui;
}

void CPatient::quitWin()
{
    this->close();
}

void CPatient::newPatient()
{
    CMngPatient mngpatient(this, 0);
    mngpatient.setModal(true);
    mngpatient.show();
    mngpatient.exec();

}
