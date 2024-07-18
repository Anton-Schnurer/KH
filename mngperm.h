#ifndef MNGPERM_H
#define MNGPERM_H

#include <QDialog>

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

private:
    Ui::CMngPerm *ui;
    int _permId;
};

#endif // MNGPERM_H
