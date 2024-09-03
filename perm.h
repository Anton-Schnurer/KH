#ifndef PERM_H
#define PERM_H

#include <QDialog>
#include <QModelIndex>
#include <QSqlQueryModel>


namespace Ui {
class CPerm;
}

class CPerm : public QDialog
{
    Q_OBJECT

public:
    explicit CPerm(QWidget *parent = nullptr);
    ~CPerm();

public slots:
    void quitWin();
    void newPerm();
    void editPerm(const QModelIndex &index);
    void search();



private:
    Ui::CPerm *ui;
    QSqlQueryModel *sql;
    void sqlquery(bool filter);
    const int _PermID = 0;
    QString _permissionstr = "select PermID, PermName, PermDesc \
                                     from Permissions";


};

#endif // PERM_H
