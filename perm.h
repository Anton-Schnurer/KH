#ifndef PERM_H
#define PERM_H

#include <QDialog>

namespace Ui {
class CPerm;
}

class CPerm : public QDialog
{
    Q_OBJECT

public:
    explicit CPerm(QWidget *parent = nullptr);
    ~CPerm();

public slots:
    void quitWin();
    void newPerm();

private:
    Ui::CPerm *ui;
};

#endif // PERM_H
