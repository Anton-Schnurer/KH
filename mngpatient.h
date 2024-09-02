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
    void quitWin();
    void save();
    void delPatient();


private:
    Ui::CMngPatient *ui;
    int _PatientId;
};

#endif // MNGPATIENT_H
