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
    void quitWin();
    void save();
    void delCase();
    void newSup();
    void delSup();



private:
    Ui::CMngCase *ui;
    int _CaseId;

    QStandardItemModel *supmodel;
    QList<int> supervisors;

    void fillSup(int caseid);
    void fillTableFromSup();
    void saveSupervisors(int caseid);

};

#endif // MNGCASE_H
