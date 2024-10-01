#ifndef CASES_H
#define CASES_H

#include <QDialog>
#include <QModelIndex>
#include <QSqlQueryModel>


namespace Ui {
class CCases;
}

class CCases : public QDialog
{
    Q_OBJECT

public:
    explicit CCases(QWidget *parent = nullptr);
    ~CCases();

public slots:
    void quitWin();                                 // closes the window
    void newCase();                                 // connected to new button, opens the mngcase window to create a new case
    void editCase(const QModelIndex &index);        // connected to entry in tableview, opens mngcase window to edit an existing case
    void search();                                  // connected to search-field for the list of existing cases



private:
    Ui::CCases *ui;
    QSqlQueryModel *sql;
    void sqlquery(bool filter);                     // constructs the correct select-stmnt depending on if search-function is being used
    void checkRole();                               // checks user role if allowed to create a new case
    const int _CaseID = 0;
    QString _casestr = "select CaseID, PatientLastName, PatientFirstName, CaseStart, CaseEnd, CaseDesc \
                            from 'Case' \
                            join Patient on CPatientFK = PatientID";


};

#endif // CASES_H
