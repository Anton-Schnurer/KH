#include "roles.h"
#include "ui_roles.h"
#include "mngroles.h"

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

}

CRoles::~CRoles()
{
    delete ui;
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
}
