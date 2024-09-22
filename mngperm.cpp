#include "mngperm.h"
#include "ui_mngperm.h"
#include "user.h"

CMngPerm::CMngPerm(QWidget *parent, int permId)
    : QDialog(parent)
    , ui(new Ui::CMngPerm)
{
    _PermId = permId;
    ui->setupUi(this);
    this->setWindowTitle("Manage Permission");

    // save Btn
    QObject::connect(ui->saveBtn, SIGNAL(clicked()), SLOT(save()));
    // manage quit button
    QObject::connect(ui->quitBtn, SIGNAL(clicked()), SLOT(quitWin()));
    // delete Btn
    QObject::connect(ui->delBtn, SIGNAL(clicked()), SLOT(delPerm()));


    // check if edit or create new
    if (_PermId != 0)
    {
        // put data into the form
        QSqlQuery queryone("select * from Permissions where PermID="+ QString::number(_PermId));
        if (queryone.next())
        {
            // put data from db into the form
            ui->permNlineEdit->setText(queryone.value(1).toString());
            ui->permDtextEdit->setText(queryone.value(2).toString());

            // this is how you can disable access to entryfields:
            // ui->permNlineEdit->setEnabled(false);
        }
    }
    else
    {
        // disable the delete button for new entry
        ui->delBtn->setEnabled(false);
    }

    checkPerm();
}

CMngPerm::~CMngPerm()
{
    delete ui;
}

void CMngPerm::quitWin()
{
    this->close();
}

void CMngPerm::save()
{
    // save the changes

    if (_PermId == 0)
    {
        // insert new permission
        QSqlQuery queryinsert;
        queryinsert.prepare("insert into Permissions (PermName, PermDesc) \
                                        values (:name, :desc)");
        queryinsert.bindValue(":name", ui->permNlineEdit->text());
        queryinsert.bindValue(":desc", ui->permDtextEdit->toPlainText());

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
        _PermId = queryinsert.lastInsertId().toInt();
    }
    else
    {
        // update existing permission
        QSqlQuery queryupdate;
        queryupdate.prepare("update Permissions set PermName = :name, \
                                                PermDesc = :desc \
                                    where PermID = :permid");

        queryupdate.bindValue(":name", ui->permNlineEdit->text());
        queryupdate.bindValue(":desc", ui->permDtextEdit->toPlainText());
        queryupdate.bindValue(":permid", _PermId);

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

void CMngPerm::delPerm()
{
    // delete the selected permission (only under certain conditions)
    // implement check if permission is connected to any staffmembers (StaffPerm-SPPermFK) and prevent deletion in that case
    QSqlQuery queryone("select * from StaffPerm where SPPermFK="+ QString::number(_PermId));
    if (queryone.next())
    {
        // this permission is connected to at least one staff member
        QMessageBox msg;
        msg.setText("This Permission is connected to Staff members, Deletion not possible");
        msg.setWindowTitle("Warning");
        msg.addButton("Ok", QMessageBox::YesRole);
        msg.exec();
    }
    else {
        // ask if deletion is really intended
        QMessageBox msg;
        msg.setText("ARE YOU SURE?");
        msg.setWindowTitle("Delete Permission");
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msg.setDefaultButton(QMessageBox::Yes);
        QAbstractButton *but = msg.button(QMessageBox::Yes);
        but->setText("Ok");
        if (msg.exec() == QMessageBox::Yes)
        {
            // delete the specific permission
            QSqlQuery delPerm;
            delPerm.prepare("delete from Permissions where PermID= :permid");
            delPerm.bindValue(":permid", QString::number(_PermId));
            if (!delPerm.exec())
            {
                // something went wrong with delete
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

void CMngPerm::checkPerm()
{
    QString search_string="sysadmin";
    if (CUserHandling::search_perm_list(search_string))
    {
        // only sysadmin is allowed
        return;
    }
    // not sysadmin -> not allowed to change anything
    ui->permDtextEdit->setEnabled(false);
    ui->permNlineEdit->setEnabled(false);
    ui->saveBtn->setEnabled(false);
    ui->delBtn->setEnabled(false);
}
