#ifndef MNGROLES_H
#define MNGROLES_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>


namespace Ui {
class CMngRoles;
}

class CMngRoles : public QDialog
{
    Q_OBJECT

public:
    explicit CMngRoles(QWidget *parent = nullptr, int roleId = 0);
    ~CMngRoles();

public slots:
    void quitWin();
    void save();
    void delRole();


private:
    Ui::CMngRoles *ui;
    int _RoleId;
};

#endif // MNGROLES_H
