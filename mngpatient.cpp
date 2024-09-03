#include "mngpatient.h"
#include "ui_mngpatient.h"

CMngPatient::CMngPatient(QWidget *parent, int patientId)
    : QDialog(parent)
    , ui(new Ui::CMngPatient)
{
    _PatientId = patientId;
    ui->setupUi(this);
    this->setWindowTitle("Manage Patient");

    // save Btn
    QObject::connect(ui->saveBtn, SIGNAL(clicked()), SLOT(save()));
    // delete Btn
    QObject::connect(ui->delBtn, SIGNAL(clicked()), SLOT(delPatient()));
    // manage quit button
    QObject::connect(ui->quitBtn, SIGNAL(clicked()), SLOT(quitWin()));

    // check if edit or create new
    if (_PatientId != 0)
    {
        // put data into the form
        QSqlQuery queryone("select * from Patient where PatientID="+ QString::number(_PatientId));
        if (queryone.next())
        {
            // put data from db into the form
            ui->firstnLineEdit->setText(queryone.value(1).toString());
            ui->lastnLineEdit->setText(queryone.value(2).toString());
            ui->phonenLineEdit->setText(queryone.value(3).toString());
            ui->SSNLineEdit->setText(queryone.value(4).toString());
        }
    }
    else
    {
        // disable the delete button for new entry
        ui->delBtn->setEnabled(false);
    }

}

CMngPatient::~CMngPatient()
{
    delete ui;
}

void CMngPatient::quitWin()
{
    this->close();
}

void CMngPatient::save()
{
    // save the changes

    if (_PatientId == 0)
    {
        // insert new patient
        QSqlQuery queryinsert;
        queryinsert.prepare("insert into Patient (PatientFirstName, PatientLastName, PatientSSN, PatientPhoneNr) \
                                        values (:fname, :lname, :ssn, :pnr)");
        queryinsert.bindValue(":fname", ui->firstnLineEdit->text());
        queryinsert.bindValue(":lname", ui->lastnLineEdit->text());
        queryinsert.bindValue(":ssn", ui->SSNLineEdit->text());
        queryinsert.bindValue(":pnr", ui->phonenLineEdit->text());

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
        _PatientId = queryinsert.lastInsertId().toInt();
    }
    else
    {
        // update existing patient
        QSqlQuery queryupdate;
        queryupdate.prepare("update Patient set PatientFirstName = :fname, \
                                                PatientLastName = :lname, \
                                                PatientSSN = :ssn, \
                                                PatientPhoneNr = :pnr \
                                    where PatientID = :patientid");

        queryupdate.bindValue(":fname", ui->firstnLineEdit->text());
        queryupdate.bindValue(":lname", ui->lastnLineEdit->text());
        queryupdate.bindValue(":ssn", ui->SSNLineEdit->text());
        queryupdate.bindValue(":pnr", ui->phonenLineEdit->text());
        queryupdate.bindValue(":patientid", _PatientId);

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

void CMngPatient::delPatient()
{
    // delete only patients that are not connected to cases
    // check role if permitted to delete

    if (_PatientId == 0)
    {
        // should not be possible because delete button only available in case of an edit
        QMessageBox msg;
        msg.setText("Delete with no patient selected");
        msg.setWindowTitle("Error");
        msg.addButton("Ok", QMessageBox::YesRole);
        msg.exec();
        return;
    }
    // delete the selected patient (only under certain conditions)
    // implement check if patient is connected to any cases (Case-CPatientFK) and prevent deletion in that case
    QSqlQuery queryone("select * from Case where CPatientFK="+ QString::number(_PatientId));
    if (queryone.next())
    {
        // this patient is connected to at least one case
        QMessageBox msg;
        msg.setText("This Patient is connected to Cases, Deletion not possible");
        msg.setWindowTitle("Warning");
        msg.addButton("Ok", QMessageBox::YesRole);
        msg.exec();
    }
    else {
        // ask if deletion is really intended
        QMessageBox msg;
        msg.setText("ARE YOU SURE?");
        msg.setWindowTitle("Delete Patient");
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msg.setDefaultButton(QMessageBox::Yes);
        QAbstractButton *but = msg.button(QMessageBox::Yes);
        but->setText("Ok");
        if (msg.exec() == QMessageBox::Yes)
        {
            // delete the specific patient
            QSqlQuery delPatient("delete from Patient where PatientID="+QString::number(_PatientId));
            if (!delPatient.next())
            {
                // something went wrong with delete
            }
        }
    }
    this->close();

}
