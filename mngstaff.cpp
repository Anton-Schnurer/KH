#include "mngstaff.h"
#include "ui_mngstaff.h"
#include "user.h"

CMngStaff::CMngStaff(QWidget *parent, int staffId)
    : QDialog(parent)
    , ui(new Ui::CMngStaff)
{
    _StaffId = staffId;
    _orig_pwd=NULL;
    ui->setupUi(this);
    this->setWindowTitle("Edit/Create Staff");

    // mask the password entry field
    ui->pwdLineEdit->setEchoMode(QLineEdit::Password);

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


    permmodel = new QStandardItemModel();
    rolemodel = new QStandardItemModel();

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

            // save current pwd in encrypted form to check if altered later
            _orig_pwd=queryone.value(2).toString();

            ui->firstnLineEdit->setText(queryone.value(3).toString());
            ui->lastnLineEdit->setText(queryone.value(4).toString());
            ui->phonenLineEdit->setText(queryone.value(5).toString());
        }
        // fill out current permissions and roles
        fillPerm(_StaffId);
        fillTableFromPerm();

        fillRole(_StaffId);
        fillTableFromRole();
    }
    else
    {
        // disable the delete button for new entry
        ui->delBtn->setEnabled(false);
    }

    checkPerm();        // check permissions, affects (password/username)
    checkRole();        // check roles, affects all other fields
}

CMngStaff::~CMngStaff()
{
    delete ui;
    delete permmodel;
    delete rolemodel;
}

void CMngStaff::quitWin()
{
    this->close();
}

void CMngStaff::save()
{
    // save the changes

    // check if all the required fields have been filled
    if ((ui->usernLineEdit->text().isEmpty()) ||
        ui->pwdLineEdit->text().isEmpty() ||
        ui->firstnLineEdit->text().isEmpty() ||
        ui->lastnLineEdit->text().isEmpty() ||
        ui->phonenLineEdit->text().isEmpty() ||
        permissions.isEmpty() ||
        roles.isEmpty())
    {
        // error message to fill out the data
        QMessageBox msg;
        msg.setText("All fields must be filled");
        msg.setWindowTitle("Warning");
        msg.addButton("Ok", QMessageBox::YesRole);
        msg.exec();
        return;
    }

    bool transaction=true;
    QSqlQuery trans;
    trans.prepare("begin transaction");
    trans.exec();

    if (_StaffId == 0)
    {

        // insert new staff member
        QSqlQuery queryinsert;
        queryinsert.prepare("insert into Staff (StaffUser, StaffPWD, StaffFirstName, StaffLastName, StaffPhoneNr) \
                                        values (:user, :pwd, :fname, :lname, :pnr)");
        queryinsert.bindValue(":user", ui->usernLineEdit->text());

        // encrypt password before insert
        QString pwd = ui->pwdLineEdit->text();
        QByteArray bytea = pwd.toUtf8();
        QString passhash = QCryptographicHash::hash(bytea,QCryptographicHash::Sha256).toHex();

        queryinsert.bindValue(":pwd", passhash);
        queryinsert.bindValue(":fname", ui->firstnLineEdit->text());
        queryinsert.bindValue(":lname", ui->lastnLineEdit->text());
        queryinsert.bindValue(":pnr", ui->phonenLineEdit->text());

        if (!queryinsert.exec())
        {
            QMessageBox msg;
            msg.setText("Error during Insert");
            msg.setWindowTitle("Error");
            msg.addButton("Ok", QMessageBox::YesRole);
            msg.exec();
            transaction=false;

        }
        // lastInsertId gets the generated primary key from the database
        if (transaction) _StaffId = queryinsert.lastInsertId().toInt();
    }
    else
    {
        // update existing staff member
        QSqlQuery queryupdate;
        queryupdate.prepare("update Staff set   StaffUser = :user, \
                                                StaffPWD = :pwd, \
                                                StaffFirstName = :fname, \
                                                StaffLastName = :lname, \
                                                StaffPhoneNr = :pnr \
                                    where StaffID = :staffid");

        queryupdate.bindValue(":user", ui->usernLineEdit->text());

        // check if password has been changed
        // encrypt password before update IF it has been changed

        QString pwd = ui->pwdLineEdit->text();
        QString passhash;

        if (_orig_pwd != pwd)
        {
            QByteArray bytea = pwd.toUtf8();
            passhash = QCryptographicHash::hash(bytea,QCryptographicHash::Sha256).toHex();
        }
        else
        {
            passhash = ui->pwdLineEdit->text();
        }

        queryupdate.bindValue(":pwd", passhash);
        queryupdate.bindValue(":fname", ui->firstnLineEdit->text());
        queryupdate.bindValue(":lname", ui->lastnLineEdit->text());
        queryupdate.bindValue(":pnr", ui->phonenLineEdit->text());
        queryupdate.bindValue(":staffid", _StaffId);

        if (!queryupdate.exec())
        {
            QMessageBox msg;
            msg.setText("Error during update");
            msg.setWindowTitle("Error");
            msg.addButton("Ok", QMessageBox::YesRole);
            msg.exec();
            transaction=false;
        }
    }
    // fill the permissions/roles intermediate tables StaffPerm/StaffRole

    if (transaction)
    {
        if (!savePermissions(_StaffId))
        {
            transaction=false;
        }
        else
        {
            if (!saveRoles(_StaffId))
            {
                transaction=false;
            }
        }
    }

    if (transaction)
    {
        trans.prepare("commit");
        trans.exec();
    }
    else
    {
        trans.prepare("rollback");
        trans.exec();
    }
    this->close();
}

void CMngStaff::delStaff()
{
    // delete the selected staff member (only under certain conditions) and data in intermediate tables StaffPerm, StaffRoles
    QSqlQuery queryone("select * from StaffCase where StaffID="+ QString::number(_StaffId));
    if (queryone.next())
    {
        // this staff member is connected to at least one case
        QMessageBox msg;
        msg.setText("This Staff member is connected to Cases, Deletion not possible");
        msg.setWindowTitle("Warning");
        msg.addButton("Ok", QMessageBox::YesRole);
        msg.exec();
    }
    else {
        // ask if deletion is really intended
        QMessageBox msg;
        msg.setText("ARE YOU SURE?");
        msg.setWindowTitle("Delete Staff");
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msg.setDefaultButton(QMessageBox::Yes);
        QAbstractButton *but = msg.button(QMessageBox::Yes);
        but->setText("Ok");
        if (msg.exec() == QMessageBox::Yes)
        {

            // delete data in intermediate tables StaffPerm, StaffRoles
            bool transaction=true;

            QSqlQuery trans;
            trans.prepare("begin transaction");
            trans.exec();

            QSqlQuery delStaffPerm;
            delStaffPerm.prepare("delete from StaffPerm where SPStaffFK="+QString::number(_StaffId));
            if (!delStaffPerm.exec())
            {
                // something went wrong with delete
                transaction=false;
            }
            QSqlQuery delStaffRole;
            delStaffRole.prepare("delete from StaffRoles where SRStaffFK="+QString::number(_StaffId));
            if (!delStaffRole.exec())
            {
                // something went wrong with delete
                transaction=false;
            }
            // delete the specific staff member
            QSqlQuery delStaff;
            delStaff.prepare("delete from Staff where StaffID="+QString::number(_StaffId));
            if (!delStaff.exec())
            {
                // something went wrong with delete
                transaction=false;
            }

            if (transaction)
              {
                trans.prepare("commit");
                trans.exec();
            }
            else
            {
                trans.prepare("rollback");
                trans.exec();

                QMessageBox msg;
                msg.setText("Error during delete");
                msg.setWindowTitle("Error");
                msg.addButton("Ok", QMessageBox::YesRole);
                msg.exec();

            }
        }
    }
    this->close();
}

void CMngStaff::newRole()
{
    // adds a role to the selected staff member (combo box)
    // get combobox value
    int currentindex = ui->rolesComboBox->currentIndex();
    QVariant variant = ui->rolesComboBox->itemData(currentindex);
    int roleid = variant.toInt();
    // Add roleid to roles list
    if (!roles.contains(roleid))
    {
        roles.append(roleid);
        fillTableFromRole();
    }
}

void CMngStaff::delRole()
{
    // removes a role from the selected staff member (combo box)
    // get marked line
    int rowid = ui->rolesTableView->selectionModel()->currentIndex().row();
    // access model with line and row
    int rolepk = ui->rolesTableView->model()->index(rowid, 0).data().toInt();

    // remove entry from roles list
    int index = roles.indexOf(rolepk);
    if (index != -1)
    {
        roles.removeAt(index);
        fillTableFromRole();
    }
}

void CMngStaff::newPerm()
{
    // adds a permission to the selected staff member (combo box)
    // implement check if current user is allowed to give new

    // get combobox value
    int currentindex = ui->permComboBox->currentIndex();
    QVariant variant = ui->permComboBox->itemData(currentindex);
    int permid = variant.toInt();
    // Add permid to permissions list
    if (!permissions.contains(permid))
    {
        permissions.append(permid);
        fillTableFromPerm();
    }

}

void CMngStaff::delPerm()
{
    // removes a permission from the selected staff member (combo box)
    // implement check if current user is allowed to remove permissions and that 1 permission must be granted at

    // get marked line
    int rowid = ui->permTableView->selectionModel()->currentIndex().row();
    // access model with line and row
    int permpk = ui->permTableView->model()->index(rowid, 0).data().toInt();

    // remove entry from roles list
    int index = permissions.indexOf(permpk);
    if (index != -1)
    {
        permissions.removeAt(index);
        fillTableFromPerm();
    }

}

void CMngStaff::fillPerm(int staffid)
{
    // fills list of integers with PK permissions for this staffmember
    QSqlQuery queryperm("select SPPermFK from StaffPerm where SPStaffFK=" + QString::number(staffid));

    while (queryperm.next())
    {
        int permid = queryperm.value(0).toInt();
        permissions.append(permid);
    }
}

void CMngStaff::fillRole(int staffid)
{
    // fills list of integers with PK roles for this staffmember
    QSqlQuery queryrole("select SRRolesFK from StaffRoles where SRStaffFK=" + QString::number(staffid));

    while (queryrole.next())
    {
        int roleid = queryrole.value(0).toInt();
        roles.append(roleid);
    }

}

void CMngStaff::fillTableFromPerm()
{
    // fill out tableview for permissions
    permmodel->clear();
    // loop over all permissions
    foreach(int permid, permissions)
    {
        QStandardItem *iditem = new QStandardItem(QString::number(permid));
        QStandardItem *textitem;
        QStandardItem *descitem;
        QSqlQuery queryperm("select * from Permissions where PermID=" + QString::number(permid));
        while (queryperm.next())
        {
            QString text = queryperm.value(1).toString();
            textitem = new QStandardItem(text);
            QString desc = queryperm.value(2).toString();
            descitem = new QStandardItem(desc);
        }
        // add select to model
        permmodel->appendRow(QList<QStandardItem*>() << iditem << textitem << descitem);
    }
    permmodel->setHeaderData(1, Qt::Horizontal, "Permission");
    permmodel->setHeaderData(2, Qt::Horizontal, "Description");
    // connect model to view
    ui->permTableView->setModel(permmodel);
    ui->permTableView->horizontalHeader()->setStretchLastSection(true);
    ui->permTableView->hideColumn(0);
}

void CMngStaff::fillTableFromRole()
{
    // fill out tableview for permissions
    rolemodel->clear();
    // loop over all permissions
    foreach(int roleid, roles)
    {
        QStandardItem *iditem = new QStandardItem(QString::number(roleid));
        QStandardItem *textitem;
        QStandardItem *descitem;
        QSqlQuery queryrole("select * from Roles where RoleID=" + QString::number(roleid));
        while (queryrole.next())
        {
            QString text = queryrole.value(1).toString();
            textitem = new QStandardItem(text);
            QString desc = queryrole.value(2).toString();
            descitem = new QStandardItem(desc);
        }
        // add select to model
        rolemodel->appendRow(QList<QStandardItem*>() << iditem << textitem << descitem);
    }
    rolemodel->setHeaderData(1, Qt::Horizontal, "Role");
    rolemodel->setHeaderData(2, Qt::Horizontal, "Description");
    // connect model to view
    ui->rolesTableView->setModel(rolemodel);
    ui->rolesTableView->horizontalHeader()->setStretchLastSection(true);
    ui->rolesTableView->hideColumn(0);

}

bool CMngStaff::savePermissions(int staffid)
{
    //
    // query the permissions list and only insert the missing entires
    foreach(int permid, permissions)
    {
        // check for existence
        QSqlQuery queryperm("select SPPermFK from StaffPerm where SPStaffFK = " +
                           QString::number(staffid) +
                           " and SPPermFK = " +
                           QString::number(permid));
        if (!queryperm.next())
        {
            // does not exist
            QSqlQuery insert;
            insert.prepare("insert into StaffPerm (SPStaffFK, SPPermFK) values (:staffid,:permid)");
            insert.bindValue(":staffid", staffid);
            insert.bindValue(":permid", permid);
            if (!insert.exec())
            {
                return false;
            }
        }
    }

    // delete entries in db that are not present in permissions list
    QSqlQuery queryperm("select SPPermFK from StaffPerm where SPStaffFK = " +
                       QString::number(staffid));
    while (queryperm.next())
    {
        // get PermID
        int permid = queryperm.value(0).toInt();

        // search in permissions list
        if (permissions.indexOf(permid) == -1)
        {
            // not present in permissions list
            QSqlQuery del;
            del.prepare("delete from StaffPerm where SPStaffFK = :staffid and SPPermFK = :permid");
            del.bindValue(":staffid", staffid);
            del.bindValue(":permid", permid);
            if (!del.exec())
            {
                return false;
            }

        }
    }
    return true;
}

bool CMngStaff::saveRoles(int staffid)
{
    //
    // query the roles list and only insert the missing entires
    foreach(int roleid, roles)
    {
        // check for existence
        QSqlQuery queryrole("select SRRolesFK from StaffRoles where SRStaffFK = " +
                            QString::number(staffid) +
                            " and SRRolesFK = " +
                            QString::number(roleid));
        if (!queryrole.next())
        {
            // does not exist
            QSqlQuery insert;
            insert.prepare("insert into StaffRoles (SRStaffFK, SRRolesFK) values (:staffid,:roleid)");
            insert.bindValue(":staffid", staffid);
            insert.bindValue(":roleid", roleid);
            if (!insert.exec())
            {
                return false;
            }
        }
    }

    // delete entries in db that are not present in roles list
    QSqlQuery queryrole("select SRRolesFK from StaffRoles where SRStaffFK = " +
                        QString::number(staffid));
    while (queryrole.next())
    {
        // get RoleID
        int roleid = queryrole.value(0).toInt();

        // search in roles list
        if (roles.indexOf(roleid) == -1)
        {
            // not present in roles list
            QSqlQuery del;
            del.prepare("delete from StaffRoles where SRStaffFK = :staffid and SRRolesFK = :roleid");
            del.bindValue(":staffid", staffid);
            del.bindValue(":roleid", roleid);
            if (!del.exec())
            {
                return false;
            }

        }
    }
    return true;
}

void CMngStaff::checkPerm()
{
    // depending on the permissions of the user certain elements of the UI will be disabled

    // sysadmin can change username and password
    QString search_string="sysadmin";
    if (CUserHandling::search_perm_list(search_string))
    {
        ui->pwdLineEdit->setEnabled(true);
        ui->usernLineEdit->setEnabled(true);
        return;
    }
    // standard permission allowed to change own password
    search_string="standard";
    if ((CUserHandling::search_perm_list(search_string)) && (CUserHandling::_current_staffid == _StaffId))
    {
        ui->usernLineEdit->setDisabled(true);
        ui->pwdLineEdit->setEnabled(true);
        return;
    }
    // disable the password entry field + username
    ui->pwdLineEdit->setDisabled(true);
    ui->usernLineEdit->setDisabled(true);
}

void CMngStaff::checkRole()
{
    // depending on the role of the user certain elements of the UI will be disabled
    QString search_string="admin";
    if (CUserHandling::search_role_list(search_string))
    {
        // admin is allowed everything in staffmember
        return;
    }
    search_string="default";
    if ((CUserHandling::search_role_list(search_string)) && (CUserHandling::_current_staffid == _StaffId))
    {
        // default is allowed to change own data except add/remove permissions/roles
        ui->addPermBtn->setDisabled(true);
        ui->delPermBtn->setDisabled(true);
        ui->addRoleBtn->setDisabled(true);
        ui->delRoleBtn->setDisabled(true);
        ui->delBtn->setDisabled(true);
        return;
    }
    // everyone else only allowed to view data
    ui->firstnLineEdit->setDisabled(true);
    ui->lastnLineEdit->setDisabled(true);
    ui->phonenLineEdit->setDisabled(true);
    ui->addPermBtn->setDisabled(true);
    ui->delPermBtn->setDisabled(true);
    ui->addRoleBtn->setDisabled(true);
    ui->delRoleBtn->setDisabled(true);
    ui->delBtn->setDisabled(true);
    ui->saveBtn->setDisabled(true);

}
