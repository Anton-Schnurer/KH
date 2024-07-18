#include "mngstaff.h"
#include "ui_mngstaff.h"

CMngStaff::CMngStaff(QWidget *parent, int staffId)
    : QDialog(parent)
    , ui(new Ui::CMngStaff)
{
    _staffId = staffId;
    ui->setupUi(this);
    this->setWindowTitle("Staff Window");

    // manage quit Btn
    QObject::connect(ui->quitBtn, SIGNAL(clicked()),SLOT(quitWin()));
}

CMngStaff::~CMngStaff()
{
    delete ui;
}

void CMngStaff::quitWin()
{
    this->close();
}
