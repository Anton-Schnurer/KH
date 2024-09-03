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
    void quitWin();
    void newCase();
    void editCase(const QModelIndex &index);
    void search();


private:
    Ui::CCases *ui;
    QSqlQueryModel *sql;
    void sqlquery(bool filter);
    const int _CaseID = 0;
    QString _casestr = "select CaseID, CPatientFK, CaseStart, CaseEnd, CaseDesc \
                            from Case";


};

#endif // CASES_H
