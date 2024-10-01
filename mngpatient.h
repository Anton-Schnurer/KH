#ifndef MNGPATIENT_H
#define MNGPATIENT_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>


namespace Ui {
class CMngPatient;
}

class CMngPatient : public QDialog
{
    Q_OBJECT

public:
    explicit CMngPatient(QWidget *parent = nullptr, int patientId = 0);
    ~CMngPatient();

public slots:
    void quitWin();                                     // closes the window
    void save();                                        // saves new patient or updates current patient in the db
    void delPatient();                                  // deletes patient from db



private:
    Ui::CMngPatient *ui;
    int _PatientId;
    void checkRole();                                   // check role of current user if allowed to save/edit/delete
};

#endif // MNGPATIENT_H
