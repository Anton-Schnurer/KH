#ifndef STAFF_H
#define STAFF_H

#include <QDialog>
#include <QModelIndex>
#include <QSqlQueryModel>

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
    void editStaff(const QModelIndex &);
    void search();

private:
    Ui::CStaff *ui;
    QSqlQueryModel *sql;
    void sqlquery(bool filter);
};

#endif // STAFF_H
