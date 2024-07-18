#include "staff.h"
#include "ui_staff.h"
#include "mngstaff.h"

CStaff::CStaff(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CStaff)
{
    ui->setupUi(this);
    this->setWindowTitle("Manage Staff");

    // Manages the Quit btn
    QObject::connect(ui->quitBtn, SIGNAL(clicked()), SLOT(quitWin()));

    // Manages the new staff btn
    QObject::connect(ui->newStaffBtn, SIGNAL(clicked()), SLOT(newStaff()));
}

CStaff::~CStaff()
{
    delete ui;
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

