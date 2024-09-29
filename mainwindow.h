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
    void manageStaff();                                                 // button and menue-entry opens the staff list window
    void managePatients();                                              // button and menue-entry opens the patient list window
    void manageCases();                                                 // button and menue-entry opens the case list window
    void manageRoles();                                                 // menue-entry opens the roles list window
    void managePerm();                                                  // menue-entry opens the permissions list window
    void quitWin();                                                     // closes the mainwindow and in turn the program
    void changeUser();                                                  // change the current user - opens up the loginwindow
    void search();                                                      // search in the treeview for all patients that have active cases this week

private:
    Ui::CMainWindow *ui;
    QSqlQueryModel *sql;
    void sqlquery(bool filter);                                         // construct correct sqlstmnt depending on search-field
    QString _casetreestr = "select PatientID, PatientLastName, PatientFirstName, CaseStart, CaseEnd, \
        group_concat(StaffUser) as supervisor, CaseDesc \
        from 'Case' \
        join Patient on CPatientFK = PatientID \
        join StaffCase on SCCaseFK = CaseID \
        join Staff on SCStaffFK = StaffID";

};
#endif // MAINWINDOW_H
