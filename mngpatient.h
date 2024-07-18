#ifndef MNGPATIENT_H
#define MNGPATIENT_H

#include <QDialog>

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

private:
    Ui::CMngPatient *ui;
    int _patientId;
};

#endif // MNGPATIENT_H
