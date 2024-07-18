#include "cases.h"
#include "ui_cases.h"
#include "mngcase.h"

CCases::CCases(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CCases)
{
    ui->setupUi(this);
    this->setWindowTitle("Manage Cases");

    // manage quit Button
    QObject::connect(ui->quitBtn, SIGNAL(clicked()), SLOT(quitWin()));

    // connect new Button
    QObject::connect(ui->newCaseBtn, SIGNAL(clicked()), SLOT(newCase()));
}

CCases::~CCases()
{
    delete ui;
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
}
