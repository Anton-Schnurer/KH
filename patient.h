#ifndef PATIENT_H
#define PATIENT_H

#include <QDialog>
#include <QModelIndex>
#include <QSqlQueryModel>


namespace Ui {
class CPatient;
}

class CPatient : public QDialog
{
    Q_OBJECT

public:
    explicit CPatient(QWidget *parent = nullptr);
    ~CPatient();

public slots:
    void quitWin();                                             // close the window
    void newPatient();                                          // new button opens mngpatient window to create new patient
    void editPatient(const QModelIndex &index);                 // opens mngpatient window to edit select patient from patientlist
    void search();                                              // search list of patients by name




private:
    Ui::CPatient *ui;
    QSqlQueryModel *sql;
    void sqlquery(bool filter);                                 // construct sqlstmnt to query patients if search-field is filled or not
    const int _PatientID = 0;
    void checkRole();                                           // check role of current user if allowed to create new patient
    QString _patientstr = "select PatientID, PatientLastName, PatientFirstName, PatientSSN, PatientPhoneNr \
                           from Patient";

};

#endif // PATIENT_H
