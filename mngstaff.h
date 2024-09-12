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
    void quitWin();
    void save();
    void delStaff();
    void newRole();
    void delRole();
    void newPerm();
    void delPerm();

private:
    Ui::CMngStaff *ui;
    int _StaffId;
    QString _orig_pwd;
    QStandardItemModel *permmodel;
    QStandardItemModel *rolemodel;
    QList<int> permissions;
    QList<int> roles;

    void fillPerm(int staffid);
    void fillRole(int staffid);
    void fillTableFromPerm();
    void fillTableFromRole();
    bool savePermissions(int staffid);
    bool saveRoles(int staffid);
    void checkPerm();
    void checkRole();

};

#endif // MNGSTAFF_H
