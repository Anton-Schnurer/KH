#ifndef MNGPERM_H
#define MNGPERM_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>


namespace Ui {
class CMngPerm;
}

class CMngPerm : public QDialog
{
    Q_OBJECT

public:
    explicit CMngPerm(QWidget *parent = nullptr, int permId = 0);
    ~CMngPerm();

public slots:
    void quitWin();
    void save();
    void delPerm();

private:
    Ui::CMngPerm *ui;
    int _PermId;
};

#endif // MNGPERM_H
