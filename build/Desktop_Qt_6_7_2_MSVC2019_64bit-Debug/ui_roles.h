/********************************************************************************
** Form generated from reading UI file 'roles.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROLES_H
#define UI_ROLES_H

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

class Ui_CRoles
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *searchRlineEdit;
    QPushButton *searchRBtn;
    QTableView *rolesTableView;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *newRBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *quitBtn;

    void setupUi(QDialog *CRoles)
    {
        if (CRoles->objectName().isEmpty())
            CRoles->setObjectName("CRoles");
        CRoles->resize(502, 312);
        verticalLayout = new QVBoxLayout(CRoles);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        searchRlineEdit = new QLineEdit(CRoles);
        searchRlineEdit->setObjectName("searchRlineEdit");

        horizontalLayout->addWidget(searchRlineEdit);

        searchRBtn = new QPushButton(CRoles);
        searchRBtn->setObjectName("searchRBtn");

        horizontalLayout->addWidget(searchRBtn);


        verticalLayout->addLayout(horizontalLayout);

        rolesTableView = new QTableView(CRoles);
        rolesTableView->setObjectName("rolesTableView");

        verticalLayout->addWidget(rolesTableView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        newRBtn = new QPushButton(CRoles);
        newRBtn->setObjectName("newRBtn");

        horizontalLayout_2->addWidget(newRBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        quitBtn = new QPushButton(CRoles);
        quitBtn->setObjectName("quitBtn");

        horizontalLayout_2->addWidget(quitBtn);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(CRoles);

        QMetaObject::connectSlotsByName(CRoles);
    } // setupUi

    void retranslateUi(QDialog *CRoles)
    {
        CRoles->setWindowTitle(QCoreApplication::translate("CRoles", "Dialog", nullptr));
        searchRBtn->setText(QCoreApplication::translate("CRoles", "Search", nullptr));
        newRBtn->setText(QCoreApplication::translate("CRoles", "New Role", nullptr));
        quitBtn->setText(QCoreApplication::translate("CRoles", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CRoles: public Ui_CRoles {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROLES_H
