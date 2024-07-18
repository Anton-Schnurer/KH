#include "perm.h"
#include "ui_perm.h"
#include "mngperm.h"

CPerm::CPerm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CPerm)
{
    ui->setupUi(this);
    this->setWindowTitle("Manage Permissions");

    // manage quit button
    QObject::connect(ui->quitBtn, SIGNAL(clicked()), SLOT(quitWin()));

    // manage new button
    QObject::connect(ui->newPBtn, SIGNAL(clicked()), SLOT(newPerm()));
}

CPerm::~CPerm()
{
    delete ui;
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
}
