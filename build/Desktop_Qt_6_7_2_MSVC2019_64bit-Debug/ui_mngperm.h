/********************************************************************************
** Form generated from reading UI file 'mngperm.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MNGPERM_H
#define UI_MNGPERM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CMngPerm
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *permNlabel;
    QLineEdit *permNlineEdit;
    QLabel *permDlabel;
    QTextEdit *permDtextEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *saveBtn;
    QPushButton *delBtn;
    QPushButton *quitBtn;

    void setupUi(QDialog *CMngPerm)
    {
        if (CMngPerm->objectName().isEmpty())
            CMngPerm->setObjectName("CMngPerm");
        CMngPerm->resize(421, 272);
        verticalLayout = new QVBoxLayout(CMngPerm);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        permNlabel = new QLabel(CMngPerm);
        permNlabel->setObjectName("permNlabel");

        formLayout->setWidget(0, QFormLayout::LabelRole, permNlabel);

        permNlineEdit = new QLineEdit(CMngPerm);
        permNlineEdit->setObjectName("permNlineEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, permNlineEdit);

        permDlabel = new QLabel(CMngPerm);
        permDlabel->setObjectName("permDlabel");

        formLayout->setWidget(1, QFormLayout::LabelRole, permDlabel);

        permDtextEdit = new QTextEdit(CMngPerm);
        permDtextEdit->setObjectName("permDtextEdit");

        formLayout->setWidget(1, QFormLayout::FieldRole, permDtextEdit);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        saveBtn = new QPushButton(CMngPerm);
        saveBtn->setObjectName("saveBtn");

        horizontalLayout->addWidget(saveBtn);

        delBtn = new QPushButton(CMngPerm);
        delBtn->setObjectName("delBtn");

        horizontalLayout->addWidget(delBtn);

        quitBtn = new QPushButton(CMngPerm);
        quitBtn->setObjectName("quitBtn");

        horizontalLayout->addWidget(quitBtn);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(CMngPerm);

        QMetaObject::connectSlotsByName(CMngPerm);
    } // setupUi

    void retranslateUi(QDialog *CMngPerm)
    {
        CMngPerm->setWindowTitle(QCoreApplication::translate("CMngPerm", "Dialog", nullptr));
        permNlabel->setText(QCoreApplication::translate("CMngPerm", "Name:", nullptr));
        permDlabel->setText(QCoreApplication::translate("CMngPerm", "Description:", nullptr));
        saveBtn->setText(QCoreApplication::translate("CMngPerm", "Save", nullptr));
        delBtn->setText(QCoreApplication::translate("CMngPerm", "Delete", nullptr));
        quitBtn->setText(QCoreApplication::translate("CMngPerm", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CMngPerm: public Ui_CMngPerm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MNGPERM_H
