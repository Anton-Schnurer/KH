#ifndef STAFF_H
#define STAFF_H

#include <QDialog>

namespace Ui {
class CStaff;
}

class CStaff : public QDialog
{
    Q_OBJECT

public:
    explicit CStaff(QWidget *parent = nullptr);
    ~CStaff();

public slots:
    void quitWin();
    void newStaff();

private:
    Ui::CStaff *ui;
};

#endif // STAFF_H
