#include "mngroles.h"
#include "ui_mngroles.h"

CMngRoles::CMngRoles(QWidget *parent, int roleId)
    : QDialog(parent)
    , ui(new Ui::CMngRoles)
{
    _RoleId = roleId;
    ui->setupUi(this);
    this->setWindowTitle("Manage Role");

    // save Btn
    QObject::connect(ui->saveBtn, SIGNAL(clicked()), SLOT(save()));
    // manage quit button
    QObject::connect(ui->quitBtn, SIGNAL(clicked()), SLOT(quitWin()));
    // delete Btn
    QObject::connect(ui->delBtn, SIGNAL(clicked()), SLOT(delRole()));


    // check if edit or create new
    if (_RoleId != 0)
    {
        // put data into the form
        QSqlQuery queryone("select * from Roles where RoleID="+ QString::number(_RoleId));
        if (queryone.next())
        {
            // put data from db into the form
            ui->roleNlineEdit->setText(queryone.value(1).toString());
            ui->roleDtextEdit->setText(queryone.value(2).toString());

            // this is how you can disable access to entryfields:
            // ui->permNlineEdit->setEnabled(false);
        }
    }
    else
    {
        // disable the delete button for new entry
        ui->delBtn->setEnabled(false);
    }


}

CMngRoles::~CMngRoles()
{
    delete ui;
}

void CMngRoles::quitWin()
{
    this->close();
}

void CMngRoles::save()
{
    // save the changes

    if (_RoleId == 0)
    {
        // insert new permission
        QSqlQuery queryinsert;
        queryinsert.prepare("insert into Roles (RoleName, RoleDesc) \
                                        values (:name, :desc)");
        queryinsert.bindValue(":name", ui->roleNlineEdit->text());
        queryinsert.bindValue(":desc", ui->roleDtextEdit->toPlainText());

        // qDebug() << queryinsert.boundValues();

        if (!queryinsert.exec())
        {
            // qDebug() << queryinsert.executedQuery();

            QMessageBox msg;
            msg.setText("Error during Insert");
            msg.setWindowTitle("Error");
            msg.addButton("Ok", QMessageBox::YesRole);
            msg.exec();
            this->close();
        }
        // lastInsertId gets the generated primary key from the database
        _RoleId = queryinsert.lastInsertId().toInt();
    }
    else
    {
        // update existing permission
        QSqlQuery queryupdate;
        queryupdate.prepare("update Roles set RoleName = :name, \
                                              RoleDesc = :desc \
                                    where RoleID = :roleid");

        queryupdate.bindValue(":name", ui->roleNlineEdit->text());
        queryupdate.bindValue(":desc", ui->roleDtextEdit->toPlainText());
        queryupdate.bindValue(":permid", _RoleId);

        if (!queryupdate.exec())
        {
            QMessageBox msg;
            msg.setText("Error during update");
            msg.setWindowTitle("Error");
            msg.addButton("Ok", QMessageBox::YesRole);
            msg.exec();
        }
    }

    this->close();

}

void CMngRoles::delRole()
{

    // delete only roles that are not connected to staff members
    // check user permission if permitted to delete

    if (_RoleId == 0)
    {
        // should not be possible because delete button only available in case of an edit
        QMessageBox msg;
        msg.setText("Delete with no role selected");
        msg.setWindowTitle("Error");
        msg.addButton("Ok", QMessageBox::YesRole);
        msg.exec();
        return;
    }
    // delete the selected role (only under certain conditions)
    // implement check if role is connected to any staff members (StaffRoles-SRRolesFK) and prevent deletion in that case
    QSqlQuery queryone("select * from StaffRoles where SRRolesFK="+ QString::number(_RoleId));
    if (queryone.next())
    {
        // this role is connected to at least one staff member
        QMessageBox msg;
        msg.setText("This Role is connected to Staff members, Deletion not possible");
        msg.setWindowTitle("Warning");
        msg.addButton("Ok", QMessageBox::YesRole);
        msg.exec();
    }
    else {
        // ask if deletion is really intended
        QMessageBox msg;
        msg.setText("ARE YOU SURE?");
        msg.setWindowTitle("Delete Role");
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msg.setDefaultButton(QMessageBox::Yes);
        QAbstractButton *but = msg.button(QMessageBox::Yes);
        but->setText("Ok");
        if (msg.exec() == QMessageBox::Yes)
        {
            // delete the specific permission
            QSqlQuery delRole("delete from Roles where RoleID="+QString::number(_RoleId));
            if (!delRole.next())
            {
                // something went wrong with delete
            }
        }
    }
    this->close();

}
