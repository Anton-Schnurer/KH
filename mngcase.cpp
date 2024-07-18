#include "mngcase.h"
#include "ui_mngcase.h"

CMngCase::CMngCase(QWidget *parent, int caseId)
    : QDialog(parent)
    , ui(new Ui::CMngCase)
{
    _caseId = caseId;
    ui->setupUi(this);
    this->setWindowTitle("Manage Case");

    // manage quit button
    QObject::connect(ui->quitBtn, SIGNAL(clicked()), SLOT(quitWin()));

}

CMngCase::~CMngCase()
{
    delete ui;
}

void CMngCase::quitWin()
{
    this->close();
}
