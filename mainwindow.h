#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QModelIndex>
#include <QSqlQueryModel>
#include <QStandardItemModel>


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
    QStandardItemModel *treesql;
    void sqlquery(bool filter);
    QString _casetreestr = "select PatientID, PatientLastName, PatientFirstName, CaseStart, CaseEnd, \
        group_concat(StaffUser) as supervisor, CaseDesc \
        from 'Case' \
        join Patient on CPatientFK = PatientID \
        join StaffCase on SCCaseFK = CaseID \
        join Staff on SCStaffFK = StaffID";

};
#endif // MAINWINDOW_H
