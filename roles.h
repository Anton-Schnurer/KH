#ifndef ROLES_H
#define ROLES_H

#include <QDialog>

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

private:
    Ui::CRoles *ui;

};

#endif // ROLES_H
