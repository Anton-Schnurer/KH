#include "mngstaff.h"
#include "ui_mngstaff.h"

CMngStaff::CMngStaff(QWidget *parent, int staffId)
    : QDialog(parent)
    , ui(new Ui::CMngStaff)
{
    _StaffId = staffId;
    ui->setupUi(this);
    this->setWindowTitle("Edit/Create Staff");

    // save Btn
    QObject::connect(ui->saveBtn, SIGNAL(clicked()), SLOT(save()));
    // delete Btn
    QObject::connect(ui->delBtn, SIGNAL(clicked()), SLOT(delStaff()));
    // add roles to staff member
    QObject::connect(ui->addRoleBtn, SIGNAL(clicked()), SLOT(newRole()));
    // remove roles from staff member
    QObject::connect(ui->delRoleBtn, SIGNAL(clicked()), SLOT(delRole()));
    // add permissions to staff member
    QObject::connect(ui->addPermBtn, SIGNAL(clicked()), SLOT(newPerm()));
    // remove permissions from staff member
    QObject::connect(ui->delPermBtn, SIGNAL(clicked()), SLOT(delPerm()));
    // manage quit Btn
    QObject::connect(ui->quitBtn, SIGNAL(clicked()),SLOT(quitWin()));


    model = new QStandardItemModel();

    // fill the combo boxes
    QSqlQuery queryroles("select * from Roles");
    while(queryroles.next())
    {
        // entry for combo box
        // 1st param is visible text in combo box
        // 2nd param is invisible but can be checked if user selects it
        // in this case: value(0) is RoleID, value(1) is RoleName, value(2) is RoleDesc
        ui->rolesComboBox->addItem(queryroles.value(1).toString() + " - " + queryroles.value(2).toString(), queryroles.value(0));

    }
    QSqlQuery queryperms("select * from Permissions");
    while(queryperms.next())
    {
        // entry for combo box
        // 1st param is visible text in combo box
        // 2nd param is invisible but can be checked if user selects it
        // in this case: value(0) is PermID, value(1) is PermName, value(2) is PermDesc
        ui->permComboBox->addItem(queryperms.value(1).toString() + " - " + queryperms.value(2).toString(), queryperms.value(0));

    }
    // check if edit or create new
    if (_StaffId != 0)
    {
        // put data into the form
        QSqlQuery queryone("select * from Staff where StaffID="+ QString::number(_StaffId));
        if (queryone.next())
        {
            // put data from db into the form
            ui->usernLineEdit->setText(queryone.value(1).toString());
            ui->pwdLineEdit->setText(queryone.value(2).toString());
            ui->firstnLineEdit->setText(queryone.value(3).toString());
            ui->lastnLineEdit->setText(queryone.value(4).toString());
            ui->phonenLineEdit->setText(queryone.value(5).toString());
        }
    }
    else
    {
        // new entry
        ui->delBtn->setEnabled(false);
    }

    // insert logic for permissions/roles insert/delete into rolestableview+permtableview

}

CMngStaff::~CMngStaff()
{
    delete ui;
    delete model;
}

void CMngStaff::quitWin()
{
    this->close();
}

void CMngStaff::save()
{
    // save the changes/new staff
}

void CMngStaff::delStaff()
{
    // delete the selected staff member (only under certain conditions)
    // implement check for roles and if staff member is not connected to any cases/roles/permissions
}

void CMngStaff::newRole()
{
    // adds a role to the selected staff member (combo box)
    // implement check if user is allowed to give new roles
}

void CMngStaff::delRole()
{
    // removes a role from the selected staff member (combo box)
    // implement check if user is allowed to remove a role and that 1 role must be granted at least
}

void CMngStaff::newPerm()
{
    // adds a permission to the selected staff member (combo box)
    // implement check if user is allowed to give new permissions
}

void CMngStaff::delPerm()
{
    // removes a permission from the selected staff member (combo box)
    // implement check if user is allowed to remove permissions and that 1 permission must be granted at least
}
