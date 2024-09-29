#ifndef ROLES_H
#define ROLES_H

#include <QDialog>
#include <QModelIndex>
#include <QSqlQueryModel>


namespace Ui {
class CRoles;
}

class CRoles : public QDialog
{
    Q_OBJECT

public:
    explicit CRoles(QWidget *parent = nullptr);
    ~CRoles();

public slots:
    void quitWin();                                         // closes the window
    void newRole();                                         // new button opens mngrole window to create new role
    void editRole(const QModelIndex &index);                // opens mngrole window to edit selected role
    void search();                                          // search-field for roles has been filled
    void checkPerm();                                       // check if current user is allowed to create new role


private:
    Ui::CRoles *ui;
    QSqlQueryModel *sql;
    void sqlquery(bool filter);                             // construct sql-stmnt for role table view
    const int _RoleID = 0;
    QString _rolestr = "select RoleID, RoleName, RoleDesc \
        from Roles";


};

#endif // ROLES_H
