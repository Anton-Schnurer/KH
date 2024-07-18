/********************************************************************************
** Form generated from reading UI file 'perm.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERM_H
#define UI_PERM_H

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

class Ui_CPerm
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *searchPlineEdit;
    QPushButton *searchPBtn;
    QTableView *PermTableView;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *newPBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *quitBtn;

    void setupUi(QDialog *CPerm)
    {
        if (CPerm->objectName().isEmpty())
            CPerm->setObjectName("CPerm");
        CPerm->resize(404, 386);
        verticalLayout = new QVBoxLayout(CPerm);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        searchPlineEdit = new QLineEdit(CPerm);
        searchPlineEdit->setObjectName("searchPlineEdit");

        horizontalLayout->addWidget(searchPlineEdit);

        searchPBtn = new QPushButton(CPerm);
        searchPBtn->setObjectName("searchPBtn");

        horizontalLayout->addWidget(searchPBtn);


        verticalLayout->addLayout(horizontalLayout);

        PermTableView = new QTableView(CPerm);
        PermTableView->setObjectName("PermTableView");

        verticalLayout->addWidget(PermTableView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        newPBtn = new QPushButton(CPerm);
        newPBtn->setObjectName("newPBtn");

        horizontalLayout_2->addWidget(newPBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        quitBtn = new QPushButton(CPerm);
        quitBtn->setObjectName("quitBtn");

        horizontalLayout_2->addWidget(quitBtn);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(CPerm);

        QMetaObject::connectSlotsByName(CPerm);
    } // setupUi

    void retranslateUi(QDialog *CPerm)
    {
        CPerm->setWindowTitle(QCoreApplication::translate("CPerm", "Dialog", nullptr));
        searchPBtn->setText(QCoreApplication::translate("CPerm", "Search", nullptr));
        newPBtn->setText(QCoreApplication::translate("CPerm", "New Permission", nullptr));
        quitBtn->setText(QCoreApplication::translate("CPerm", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CPerm: public Ui_CPerm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERM_H
