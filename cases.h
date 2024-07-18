#ifndef CASES_H
#define CASES_H

#include <QDialog>

namespace Ui {
class CCases;
}

class CCases : public QDialog
{
    Q_OBJECT

public:
    explicit CCases(QWidget *parent = nullptr);
    ~CCases();

public slots:
    void quitWin();
    void newCase();

private:
    Ui::CCases *ui;
};

#endif // CASES_H
