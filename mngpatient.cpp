#include "mngpatient.h"
#include "ui_mngpatient.h"

CMngPatient::CMngPatient(QWidget *parent, int patientId)
    : QDialog(parent)
    , ui(new Ui::CMngPatient)
{
    _patientId = patientId;
    ui->setupUi(this);
    this->setWindowTitle("Manage Patient");

    // manage quit button
    QObject::connect(ui->quitBtn, SIGNAL(clicked()), SLOT(quitWin()));
}

CMngPatient::~CMngPatient()
{
    delete ui;
}

void CMngPatient::quitWin()
{
    this->close();
}
