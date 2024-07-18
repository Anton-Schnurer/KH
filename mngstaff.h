#ifndef MNGSTAFF_H
#define MNGSTAFF_H

#include <QDialog>

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

private:
    Ui::CMngStaff *ui;
    int _staffId;
};

#endif // MNGSTAFF_H
