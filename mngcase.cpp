#include "mngcase.h"
#include "ui_mngcase.h"
#include "user.h"

CMngCase::CMngCase(QWidget *parent, int caseId)
    : QDialog(parent)
    , ui(new Ui::CMngCase)
{
    _CaseId = caseId;
    ui->setupUi(this);
    this->setWindowTitle("Manage Case --- user: "+CUserHandling::_current_user);

    // save Btn
    QObject::connect(ui->saveBtn, SIGNAL(clicked()), SLOT(save()));
    // delete Btn
    QObject::connect(ui->delBtn, SIGNAL(clicked()), SLOT(delCase()));
    // add supervisors to case
    QObject::connect(ui->addStaffBtn, SIGNAL(clicked()), SLOT(newSup()));
    // remove supervisors from case
    QObject::connect(ui->delStaffBtn, SIGNAL(clicked()), SLOT(delSup()));
    // manage quit Btn
    QObject::connect(ui->quitBtn, SIGNAL(clicked()),SLOT(quitWin()));

    supmodel = new QStandardItemModel();

    // fill the combo boxes
    // where-clause shows only staff that is allowed to supervise cases

    QSqlQuery querysup("select StaffID, StaffLastName, StaffFirstName from Staff \
                        join StaffRoles on SRStaffFK=StaffID \
                        join Roles on SRRolesFK=RoleID \
                        where RoleName in ('doctor', 'nurse')");
    while(querysup.next())
    {
        // entry for combo box
        // 1st param is visible text in combo box
        // 2nd param is invisible but can be checked if user selects it
        // in this case: value(0) is StaffID, value(1) is StaffLastName, value(2) is StaffFirstName
        ui->staffIdComboBox->addItem(querysup.value(1).toString() + " - " + querysup.value(2).toString(), querysup.value(0));

    }

    QSqlQuery querypat("select PatientID, PatientLastName, PatientFirstName, PatientSSN from Patient");
    while(querypat.next())
    {
        // entry for combo box
        // 1st param is visible text in combo box
        // 2nd param is invisible but can be checked if user selects it
        // in this case: value(0) is PatientID, value(1) is PatientLastName, value(2) is PatientFirstName, value(3) is PatientSSN
        ui->patientIdComboBox->addItem(querypat.value(1).toString() + " - " + querypat.value(2).toString() +
                                         " - " + querypat.value(3).toString(), querypat.value(0));
    }

    // check if edit or create new
    if (_CaseId != 0)
    {
        // put data into the form
        QSqlQuery queryone("select * from 'Case' where CaseID="+ QString::number(_CaseId));
        if (queryone.next())
        {
            // put data from db into the form

            // position patient on correct entry
            int fk = queryone.value(1).toInt();
            int entry = ui->patientIdComboBox->findData(fk);      // findData searches in key value column of the comboBox
            ui->patientIdComboBox->setCurrentIndex(entry);

            // String from Database needs to be converted to QDateTime dd: day(1-31), MM month (1-12), yyyy year, HH hours (24h), mm minutes
            ui->start_dateTimeEdit->setDateTime(QDateTime::fromString(queryone.value(2).toString(),"dd/MM/yyyy HH:mm"));
            ui->end_dateTimeEdit->setDateTime(QDateTime::fromString(queryone.value(3).toString(),"dd/MM/yyyy HH:mm"));
            ui->caseDtextEdit->setText(queryone.value(4).toString());
        }
        // fill out QList and table view of current supervisors
        fillSup(_CaseId);
        fillTableFromSup();

    }
    else
    {
        // fill startdatetime field with current time and enddatetime field with current time + 1 hour
        ui->start_dateTimeEdit->setDateTime(QDateTime::currentDateTime());
        ui->end_dateTimeEdit->setDateTime(QDateTime::currentDateTime().addSecs(3600));


        // disable the delete button for new entry
        ui->delBtn->setEnabled(false);
    }

    // depending on the role of the current user certain buttons will be disabled
    checkRole();
}

CMngCase::~CMngCase()
{
    delete ui;
    delete supmodel;
}

void CMngCase::quitWin()
{
    this->close();
}

void CMngCase::save()
{

    // insert or update

    // check combobox patient
    int currentindex = ui->patientIdComboBox->currentIndex();
    QVariant variant = ui->patientIdComboBox->itemData(currentindex);
    int patientid = variant.toInt();

    // check if all fields are filled
    if (patientid == 0 ||
        ui->start_dateTimeEdit->text().isEmpty() ||
        ui->end_dateTimeEdit->text().isEmpty() ||
        ui->caseDtextEdit->toPlainText().isEmpty() ||
        supervisors.isEmpty())
    {
        QMessageBox msg;
        msg.setText("All fields must be filled");
        msg.setWindowTitle("Warning");
        msg.addButton("Ok", QMessageBox::YesRole);
        msg.exec();
        return;
    }
    // check if the dates make sense (start before end)
    //
    if (ui->start_dateTimeEdit->dateTime() > ui->end_dateTimeEdit->dateTime())
    {
        // start date not allowed to be after end date
        QMessageBox msg;
        msg.setText("End Date not allowed to be before Start Date");
        msg.setWindowTitle("Warning");
        msg.addButton("Ok", QMessageBox::YesRole);
        msg.exec();
        return;
    }

    // transaction logic for insert/update since it covers multiple tables
    // bool transaction decides if commit or rollback
    bool transaction=true;
    QSqlQuery trans;
    trans.prepare("begin transaction");
    trans.exec();

    // save the changes

    if (_CaseId == 0)
    {
        // insert new case

        // check if end date makes sense
        if (ui->end_dateTimeEdit->dateTime() < QDateTime::currentDateTime())
        {
            QMessageBox msg;
            msg.setText("End Date not allowed to be in the past");
            msg.setWindowTitle("Warning");
            msg.addButton("Ok", QMessageBox::YesRole);
            msg.exec();
            return;
        }

        QSqlQuery queryinsert;
        queryinsert.prepare("insert into 'Case' (CPatientFK, CaseStart, CaseEnd, CaseDesc) \
                                        values (:patientid, :cstart, :cend, :cdesc)");

        queryinsert.bindValue(":patientid", patientid);
        queryinsert.bindValue(":cstart", ui->start_dateTimeEdit->text());
        queryinsert.bindValue(":cend", ui->end_dateTimeEdit->text());
        queryinsert.bindValue(":cdesc", ui->caseDtextEdit->toPlainText());

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
        if (transaction) _CaseId = queryinsert.lastInsertId().toInt();
    }
    else
    {
        // update existing case
        QSqlQuery queryupdate;
        queryupdate.prepare("update 'Case' set  CPatientFK = :patientid, \
                                                CaseStart = :cstart, \
                                                CaseEnd = :cend, \
                                                CaseDesc = :cdesc \
                                    where CaseID = :caseid");

        queryupdate.bindValue(":patientid", patientid);
        queryupdate.bindValue(":cstart", ui->start_dateTimeEdit->text());
        queryupdate.bindValue(":cend", ui->end_dateTimeEdit->text());
        queryupdate.bindValue(":cdesc", ui->caseDtextEdit->toPlainText());
        queryupdate.bindValue(":caseid", _CaseId);

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
    // fill the supervisors in intermediate table StaffCase
    if (transaction)
    {
        if (!saveSupervisors(_CaseId))
        {
            transaction=false;
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

void CMngCase::delCase()
{

    // delete the selected Case (only under certain conditions) and data in intermediate table StaffCase

    if (ui->end_dateTimeEdit->dateTime() < QDateTime::currentDateTime())
    {
        // case has end date in the past -> prevent deletion
        QMessageBox msg;
        msg.setText("Cannot delete Case that already ended");
        msg.setWindowTitle("Error");
        msg.addButton("Ok", QMessageBox::YesRole);
        msg.exec();
        return;
    }

    // ask if deletion is really intended
    QMessageBox msg;
    msg.setText("ARE YOU SURE?");
    msg.setWindowTitle("Delete Case");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::Yes);
    QAbstractButton *but = msg.button(QMessageBox::Yes);
    but->setText("Ok");

    if (msg.exec() == QMessageBox::Yes)
    {
        // delete data in intermediate table StaffCase
        // transaction logic since delete covers multiple tables in db
        // bool transaction decides if commit or rollback
        bool transaction=true;
        QSqlQuery trans;
        trans.prepare("begin transaction");
        trans.exec();

        QSqlQuery delStaffCase;
        delStaffCase.prepare("delete from StaffCase where SCCaseFK="+QString::number(_CaseId));
        if (!delStaffCase.exec())
        {
            // something went wrong with delete
            transaction=false;
        }

        if (transaction) {
            // delete the specific staff member in table Case
            QSqlQuery delCase;
            delCase.prepare("delete from 'Case' where CaseID="+QString::number(_CaseId));
            if (!delCase.exec())
            {
                // something went wrong with delete
                transaction=false;
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

            QMessageBox msg;
            msg.setText("Error during delete");
            msg.setWindowTitle("Error");
            msg.addButton("Ok", QMessageBox::YesRole);
            msg.exec();
        }
    }
    this->close();
}

void CMngCase::newSup()
{

    // adds a supervisor to the selected case (combo box)
    // get combobox value

    int currentindex = ui->staffIdComboBox->currentIndex();
    QVariant variant = ui->staffIdComboBox->itemData(currentindex);
    int staffid = variant.toInt();
    // Add staffid to supervisors list
    if (!supervisors.contains(staffid))
    {
        supervisors.append(staffid);
        // update table view
        fillTableFromSup();
    }

}

void CMngCase::delSup()
{

    // removes a supervisor from the selected case (combo box)
    // get marked line
    int rowid = ui->supTableView->selectionModel()->currentIndex().row();
    // access model with line and row
    int staffid = ui->supTableView->model()->index(rowid, 0).data().toInt();

    // remove entry from roles list
    int index = supervisors.indexOf(staffid);
    if (index != -1)
    {
        supervisors.removeAt(index);

        // update view
        fillTableFromSup();
    }

}

void CMngCase::checkRole()
{
    // check user if allowed to create/edit/delete case and assign supervisors
    QString search_string="admin";
    if (CUserHandling::search_role_list(search_string))
    {
        // allowed
        return;
    }
    search_string="doctor";
    if (CUserHandling::search_role_list(search_string))
    {
        // allowed
        return;
    }
    search_string="nurse";
    if (CUserHandling::search_role_list(search_string))
    {
        // not allowed to delete
        ui->delBtn->setDisabled(true);
        return;
    }
    // only allowed to view data
    ui->delBtn->setDisabled(true);
    ui->saveBtn->setDisabled(true);
    ui->patientIdComboBox->setDisabled(true);
    ui->start_dateTimeEdit->setDisabled(true);
    ui->end_dateTimeEdit->setDisabled(true);
    ui->caseDtextEdit->setDisabled(true);
    ui->addStaffBtn->setDisabled(true);
    ui->delStaffBtn->setDisabled(true);
}

void CMngCase::fillSup(int caseid)
{
    // fill list of supervisors
    // fills list of integers with PK staffid for this case
    QSqlQuery querysup("select SCStaffFK from StaffCase where SCCaseFK=" + QString::number(caseid));

    while (querysup.next())
    {
        int staffid = querysup.value(0).toInt();
        supervisors.append(staffid);
    }

}

void CMngCase::fillTableFromSup()
{
    // display in tableview

    // fill out tableview for permissions
    supmodel->clear();
    // loop over all supervisors
    foreach(int supid, supervisors)
    {
        QStandardItem *iditem = new QStandardItem(QString::number(supid));
        QStandardItem *fitem;
        QStandardItem *litem;
        QSqlQuery querystaff("select * from Staff where StaffID=" + QString::number(supid));
        while (querystaff.next())
        {
            QString fname = querystaff.value(3).toString();
            fitem = new QStandardItem(fname);
            QString lname = querystaff.value(4).toString();
            litem = new QStandardItem(lname);
        }
        // add select to model
        supmodel->appendRow(QList<QStandardItem*>() << iditem << litem << fitem);
    }
    supmodel->setHeaderData(1, Qt::Horizontal, "Last Name");
    supmodel->setHeaderData(2, Qt::Horizontal, "First Name");
    // connect model to view
    ui->supTableView->setModel(supmodel);
    ui->supTableView->horizontalHeader()->setStretchLastSection(true);
    ui->supTableView->hideColumn(0);

}

bool CMngCase::saveSupervisors(int caseid)
{
    // save supervisors in intermediate table StaffCase
    //
    // query the supervisors list and only insert the missing entries
    foreach(int staffid, supervisors)
    {
        // check for existence
        QSqlQuery querysup("select * from StaffCase where SCStaffFK = " +
                            QString::number(staffid) +
                            " and SCCaseFK = " +
                            QString::number(caseid));
        if (!querysup.next())
        {
            // does not exist
            QSqlQuery insert;
            insert.prepare("insert into StaffCase (SCCaseFK, SCStaffFK) values (:caseid,:staffid)");
            insert.bindValue(":staffid", staffid);
            insert.bindValue(":caseid", caseid);
            if (!insert.exec())
            {
                return false;
            }
        }
    }

    // delete entries in db that are not present in supervisors list
    QSqlQuery querysup("select SCStaffFK from StaffCase where SCCaseFK = " +
                        QString::number(caseid));
    while (querysup.next())
    {
        // get StaffID
        int staffid = querysup.value(0).toInt();

        // search in supervisors list
        if (supervisors.indexOf(staffid) == -1)
        {
            // not present in supervisors list
            QSqlQuery del;
            del.prepare("delete from StaffCase where SCStaffFK = :staffid and SCCaseFK = :caseid");
            del.bindValue(":staffid", staffid);
            del.bindValue(":caseid", caseid);
            if (!del.exec())
            {
                return false;
            }

        }
    }
    return true;

}
