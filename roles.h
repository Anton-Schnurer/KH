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
    void quitWin();
    void newRole();
    void editRole(const QModelIndex &index);
    void search();


private:
    Ui::CRoles *ui;
    QSqlQueryModel *sql;
    void sqlquery(bool filter);
    const int _RoleID = 0;
    QString _rolestr = "select RoleID, RoleName, RoleDesc \
        from Roles";


};

#endif // ROLES_H
