#ifndef MNGSTAFF_H
#define MNGSTAFF_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QCryptographicHash>



namespace Ui {
class CMngStaff;
}

class CMngStaff : public QDialog
{
    Q_OBJECT

public:
    explicit CMngStaff(QWidget *parent = nullptr, int staffId = 0);
    ~CMngStaff();

public slots:
    void quitWin();                                     // close the window
    void save();                                        // insert new staff member or update existing one
    void delStaff();                                    // delete selected staff member
    void newRole();                                     // add new role to staff member
    void delRole();                                     // remove role from staff member
    void newPerm();                                     // add new permission to staff member
    void delPerm();                                     // remove permission from staff member

private:
    Ui::CMngStaff *ui;
    int _StaffId;
    QString _orig_pwd;
    QStandardItemModel *permmodel;
    QStandardItemModel *rolemodel;
    QList<int> permissions;
    QList<int> roles;

    void fillPerm(int staffid);                         // fill QList permissions
    void fillRole(int staffid);                         // fill QList roles
    void fillTableFromPerm();                           // list permissions for staff member in table view
    void fillTableFromRole();                           // list roles for staff member in table view
    bool savePermissions(int staffid);                  // save permissions for staff member in db
    bool saveRoles(int staffid);                        // save roles for staff member in db
    void checkPerm();                                   // check permissions of current user if allowed to change username/pwd
    void checkRole();                                   // check role of current user if allowed to edit/create/delete staff or change pwd

};

#endif // MNGSTAFF_H
