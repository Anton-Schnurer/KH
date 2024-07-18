#ifndef MNGCASE_H
#define MNGCASE_H

#include <QDialog>

namespace Ui {
class CMngCase;
}

class CMngCase : public QDialog
{
    Q_OBJECT

public:
    explicit CMngCase(QWidget *parent = nullptr, int caseId = 0);
    ~CMngCase();

public slots:
    void quitWin();

private:
    Ui::CMngCase *ui;
    int _caseId;
};

#endif // MNGCASE_H
