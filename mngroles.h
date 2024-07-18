#ifndef MNGROLES_H
#define MNGROLES_H

#include <QDialog>

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

private:
    Ui::CMngRoles *ui;
    int _roleId;
};

#endif // MNGROLES_H
