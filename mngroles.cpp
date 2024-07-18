#include "mngroles.h"
#include "ui_mngroles.h"

CMngRoles::CMngRoles(QWidget *parent, int roleId)
    : QDialog(parent)
    , ui(new Ui::CMngRoles)
{
    _roleId = roleId;
    ui->setupUi(this);
    this->setWindowTitle("Manage Role");

    // manage quit button
    QObject::connect(ui->quitBtn, SIGNAL(clicked()), SLOT(quitWin()));

}

CMngRoles::~CMngRoles()
{
    delete ui;
}

void CMngRoles::quitWin()
{
    this->close();
}
