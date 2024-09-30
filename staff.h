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
    void quitWin();                                     // closes the window
    void newStaff();                                    // opens mngstaff window to create new staff
    void editStaff(const QModelIndex &index);           // opens mngstaff window to edit selected staff
    void search();                                      // search-field for staff table view is filled
    void checkPerm();                                   // check if current user allowed to create new staff

private:
    Ui::CStaff *ui;
    QSqlQueryModel *sql;
    void sqlquery(bool filter);                         // construct sql stmnt for table view of staff
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
