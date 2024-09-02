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
    void quitWin();
    void newPatient();
    void editPatient(const QModelIndex &index);
    void search();



private:
    Ui::CPatient *ui;
    QSqlQueryModel *sql;
    void sqlquery(bool filter);
    const int _PatientID = 0;
    QString _patientstr = "select PatientID, PatientFirstName, PatientLastName, PatientSSN, PatientPhoneNr \
                           from Patient";

};

#endif // PATIENT_H
