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
    void quitWin();                                         // closes the window
    void newPerm();                                         // new button opens mngperm window to create new permission
    void editPerm(const QModelIndex &index);                // opens mngperm window with selected permission to edit
    void search();                                          // search field for permission list is filled
    void checkPerm();                                       // check if current user is allowed to create new permission


private:
    Ui::CPerm *ui;
    QSqlQueryModel *sql;
    void sqlquery(bool filter);                             // constructs sqlstmnt for permission list
    const int _PermID = 0;
    QString _permissionstr = "select PermID, PermName, PermDesc \
                                     from Permissions";


};

#endif // PERM_H
