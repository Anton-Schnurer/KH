#ifndef STAFF_H
#define STAFF_H

#include <QDialog>
#include <QModelIndex>
#include <QSqlQueryModel>

namespace Ui {
class CStaff;
}

class CStaff : public QDialog
{
    Q_OBJECT

public:
    explicit CStaff(QWidget *parent = nullptr);
    ~CStaff();

public slots:
    void quitWin();
    void newStaff();
    void editStaff(const QModelIndex &index);
    void search();
    void checkRole();

private:
    Ui::CStaff *ui;
    QSqlQueryModel *sql;
    void sqlquery(bool filter);
    const int _StaffID = 0;
    QString _staffstr = "select StaffID, StaffUser, StaffPWD, StaffFirstName, StaffLastName, StaffPhoneNr, \
                                GROUP_CONCAT(DISTINCT(Permissions.PermName)), \
                                GROUP_CONCAT(DISTINCT(Roles.RoleName)) from Staff \
                        join StaffRoles on SRStaffFK = StaffID \
                        join StaffPerm on SPStaffFK = StaffID \
                        join Permissions on SPPermFK = PermID \
                        join Roles on SRRolesFK = RoleID";
};

#endif // STAFF_H
