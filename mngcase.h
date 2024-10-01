#ifndef MNGCASE_H
#define MNGCASE_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>
#include <QStandardItemModel>



namespace Ui {
class CMngCase;
}

class CMngCase : public QDialog
{
    Q_OBJECT

public:
    explicit CMngCase(QWidget *parent = nullptr, int caseId = 0);
    ~CMngCase();

public slots:
    void quitWin();                                             // closes the window
    void save();                                                // saves the currently displayed case in the db
    void delCase();                                             // deletes the currently displayed case in the db
    void newSup();                                              // adds a supervisor to the case
    void delSup();                                              // removes a supervisor from the case




private:
    Ui::CMngCase *ui;
    int _CaseId;
    void checkRole();                                           // check which roles the current user has to limit functionality
    QStandardItemModel *supmodel;
    QList<int> supervisors;

    void fillSup(int caseid);                                   // fills supervisor QList
    void fillTableFromSup();                                    // populates entries for the supervisor table view
    bool saveSupervisors(int caseid);                           // saves new list of supervisors for current case in the db

};

#endif // MNGCASE_H
