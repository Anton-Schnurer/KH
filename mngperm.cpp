#include "mngperm.h"
#include "ui_mngperm.h"

CMngPerm::CMngPerm(QWidget *parent, int permId)
    : QDialog(parent)
    , ui(new Ui::CMngPerm)
{
    _permId = permId;
    ui->setupUi(this);

    // manage quit button
    QObject::connect(ui->quitBtn, SIGNAL(clicked()), SLOT(quitWin()));

}

CMngPerm::~CMngPerm()
{
    delete ui;
}

void CMngPerm::quitWin()
{
    this->close();
}
