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
    void quitWin();                                                 // closes the window
    void save();                                                    // insert or update permission in db
    void delPerm();                                                 // delete permission in db
    void checkPerm();                                               // check if user is allowed to insert/update/delete permissions

private:
    Ui::CMngPerm *ui;
    int _PermId;
};

#endif // MNGPERM_H
