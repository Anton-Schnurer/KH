#ifndef PATIENT_H
#define PATIENT_H

#include <QDialog>

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

private:
    Ui::CPatient *ui;

};

#endif // PATIENT_H
