#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QSqlQueryModel>


QT_BEGIN_NAMESPACE
namespace Ui {
class CMainWindow;
}
QT_END_NAMESPACE

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();

public slots:
    void manageStaff();
    void managePatients();
    void manageCases();
    void manageRoles();
    void managePerm();
    void quitWin();
    void changeUser();
    void search();

private:
    Ui::CMainWindow *ui;
    QSqlQueryModel *sql;
    void sqlquery(bool filter);
    QString _casetreestr = "select PatientLastName, PatientFirstName, CaseID, CaseStart, CaseEnd, CaseDesc \
        from 'Case' \
        join Patient on CPatientFK = PatientID";

};
#endif // MAINWINDOW_H
