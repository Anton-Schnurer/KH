#include "mngcase.h"
#include "ui_mngcase.h"

CMngCase::CMngCase(QWidget *parent, int caseId)
    : QDialog(parent)
    , ui(new Ui::CMngCase)
{
    _CaseId = caseId;
    ui->setupUi(this);
    this->setWindowTitle("Manage Case");

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
    // todo: where-clause so only staff that is allowed as supervisor is shown

    QSqlQuery querysup("select StaffID, StaffLastName, StaffFirstName from Staff");
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
        QSqlQuery queryone("select * from Case where CaseID="+ QString::number(_CaseId));
        if (queryone.next())
        {
            // put data from db into the form

            // position patient on correct entry
            int fk = queryone.value(1).toInt();
            int entry = ui->patientIdComboBox->findData(fk);      // findData searches in key value column of the comboBox
            ui->patientIdComboBox->setCurrentIndex(entry);

            // todo: correctly display QdateTime

            //ui->start_dateTimeEdit->setText(queryone.value(2).toString());
            //ui->end_dateTimeEdit->setText(queryone.value(3).toString());
            ui->caseDtextEdit->setText(queryone.value(4).toString());
        }
        // fill out current permissions and roles
        fillSup(_CaseId);
        fillTableFromSup();

    }
    else
    {
        // disable the delete button for new entry
        ui->delBtn->setEnabled(false);
    }


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

    // save the changes

    if (_CaseId == 0)
    {
        // insert new case
        QSqlQuery queryinsert;
        queryinsert.prepare("insert into Case (CPatientFK, CaseStart, CaseEnd, CaseDesc) \
                                        values (:patientid, :cstart, :cend, :cdesc)");

        queryinsert.bindValue(":patientid", patientid);
        queryinsert.bindValue(":cstart", ui->start_dateTimeEdit->text());
        queryinsert.bindValue(":cend", ui->end_dateTimeEdit->text());
        queryinsert.bindValue(":cdesc", ui->caseDtextEdit->toPlainText());

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
        _CaseId = queryinsert.lastInsertId().toInt();
    }
    else
    {
        // update existing case
        QSqlQuery queryupdate;
        queryupdate.prepare("update Case set    CPatientFK = :patientid, \
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
        }
    }
    // fill the supervisors intermediate tables StaffCase
    saveSupervisors(_CaseId);
    this->close();
}

void CMngCase::delCase()
{
    if (_CaseId == 0)
    {
        // should not be possible because delete button only available in case of an edit
        QMessageBox msg;
        msg.setText("Delete with no Case selected");
        msg.setWindowTitle("Error");
        msg.addButton("Ok", QMessageBox::YesRole);
        msg.exec();
        return;
    }
    // delete the selected Case (only under certain conditions) and data in intermediate tables StaffCase
    // implement check if Case has an end date in the past -> prevent deletion

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
        // delete data in intermediate table StaffCase
        QSqlQuery delStaffCase("delete from StaffCase where SCCaseFK="+QString::number(_CaseId));
        if (!delStaffCase.next())
        {
            // something went wrong with delete
            // there should always be at least one entry in StaffPerm for any Staff
        }

        // delete the specific staff member
        QSqlQuery delCase("delete from Case where CaseID="+QString::number(_CaseId));
        if (!delCase.next())
        {
            // something went wrong with delete
        }
    }
    this->close();

}

void CMngCase::newSup()
{

    // adds a supervisor to the selected case (combo box)
    // implement check if current user is allowed to add new supervisors

    // get combobox value

    int currentindex = ui->staffIdComboBox->currentIndex();
    QVariant variant = ui->staffIdComboBox->itemData(currentindex);
    int staffid = variant.toInt();
    // Add staffid to permissions list
    if (!supervisors.contains(staffid))
    {
        supervisors.append(staffid);
        // update view
        fillTableFromSup();
    }

}

void CMngCase::delSup()
{

    // removes a supervisor from the selected case (combo box)
    // implement check if current user is allowed to remove supervisors and that 1 supervisor must be present at least

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

void CMngCase::fillSup(int caseid)
{
    // fill list supervisors
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

void CMngCase::saveSupervisors(int caseid)
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
            insert.exec();
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
            del.exec();

        }
    }

}
