/********************************************************************************
** Form generated from reading UI file 'staff.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STAFF_H
#define UI_STAFF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CStaff
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *searchSlineEdit;
    QPushButton *searchBtn;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *newStaffBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *quitBtn;

    void setupUi(QDialog *CStaff)
    {
        if (CStaff->objectName().isEmpty())
            CStaff->setObjectName("CStaff");
        CStaff->resize(864, 663);
        verticalLayout = new QVBoxLayout(CStaff);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        searchSlineEdit = new QLineEdit(CStaff);
        searchSlineEdit->setObjectName("searchSlineEdit");

        horizontalLayout->addWidget(searchSlineEdit);

        searchBtn = new QPushButton(CStaff);
        searchBtn->setObjectName("searchBtn");

        horizontalLayout->addWidget(searchBtn);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(CStaff);
        tableView->setObjectName("tableView");

        verticalLayout->addWidget(tableView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        newStaffBtn = new QPushButton(CStaff);
        newStaffBtn->setObjectName("newStaffBtn");

        horizontalLayout_2->addWidget(newStaffBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        quitBtn = new QPushButton(CStaff);
        quitBtn->setObjectName("quitBtn");

        horizontalLayout_2->addWidget(quitBtn);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(CStaff);

        QMetaObject::connectSlotsByName(CStaff);
    } // setupUi

    void retranslateUi(QDialog *CStaff)
    {
        CStaff->setWindowTitle(QCoreApplication::translate("CStaff", "Dialog", nullptr));
        searchBtn->setText(QCoreApplication::translate("CStaff", "Search", nullptr));
        newStaffBtn->setText(QCoreApplication::translate("CStaff", "New Staff", nullptr));
        quitBtn->setText(QCoreApplication::translate("CStaff", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CStaff: public Ui_CStaff {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STAFF_H
