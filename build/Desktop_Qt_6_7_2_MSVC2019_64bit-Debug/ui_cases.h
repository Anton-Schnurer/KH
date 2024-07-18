/********************************************************************************
** Form generated from reading UI file 'cases.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CASES_H
#define UI_CASES_H

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

class Ui_CCases
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *searchPlineEdit;
    QPushButton *searchPBtn;
    QTableView *casesTableView;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *newCaseBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *quitBtn;

    void setupUi(QDialog *CCases)
    {
        if (CCases->objectName().isEmpty())
            CCases->setObjectName("CCases");
        CCases->resize(560, 544);
        verticalLayout = new QVBoxLayout(CCases);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        searchPlineEdit = new QLineEdit(CCases);
        searchPlineEdit->setObjectName("searchPlineEdit");

        horizontalLayout->addWidget(searchPlineEdit);

        searchPBtn = new QPushButton(CCases);
        searchPBtn->setObjectName("searchPBtn");

        horizontalLayout->addWidget(searchPBtn);


        verticalLayout->addLayout(horizontalLayout);

        casesTableView = new QTableView(CCases);
        casesTableView->setObjectName("casesTableView");

        verticalLayout->addWidget(casesTableView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        newCaseBtn = new QPushButton(CCases);
        newCaseBtn->setObjectName("newCaseBtn");

        horizontalLayout_2->addWidget(newCaseBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        quitBtn = new QPushButton(CCases);
        quitBtn->setObjectName("quitBtn");

        horizontalLayout_2->addWidget(quitBtn);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(CCases);

        QMetaObject::connectSlotsByName(CCases);
    } // setupUi

    void retranslateUi(QDialog *CCases)
    {
        CCases->setWindowTitle(QCoreApplication::translate("CCases", "Dialog", nullptr));
        searchPBtn->setText(QCoreApplication::translate("CCases", "Search", nullptr));
        newCaseBtn->setText(QCoreApplication::translate("CCases", "New Case", nullptr));
        quitBtn->setText(QCoreApplication::translate("CCases", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CCases: public Ui_CCases {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CASES_H
