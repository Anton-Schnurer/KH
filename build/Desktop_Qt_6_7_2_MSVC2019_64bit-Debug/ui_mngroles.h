/********************************************************************************
** Form generated from reading UI file 'mngroles.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MNGROLES_H
#define UI_MNGROLES_H

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

class Ui_CMngRoles
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *roleNlabel;
    QLineEdit *roleNlineEdit;
    QLabel *roleDtext;
    QTextEdit *roleDtextEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *saveBtn;
    QPushButton *delBtn;
    QPushButton *quitBtn;

    void setupUi(QDialog *CMngRoles)
    {
        if (CMngRoles->objectName().isEmpty())
            CMngRoles->setObjectName("CMngRoles");
        CMngRoles->resize(487, 239);
        verticalLayout = new QVBoxLayout(CMngRoles);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        roleNlabel = new QLabel(CMngRoles);
        roleNlabel->setObjectName("roleNlabel");

        formLayout->setWidget(0, QFormLayout::LabelRole, roleNlabel);

        roleNlineEdit = new QLineEdit(CMngRoles);
        roleNlineEdit->setObjectName("roleNlineEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, roleNlineEdit);

        roleDtext = new QLabel(CMngRoles);
        roleDtext->setObjectName("roleDtext");

        formLayout->setWidget(1, QFormLayout::LabelRole, roleDtext);

        roleDtextEdit = new QTextEdit(CMngRoles);
        roleDtextEdit->setObjectName("roleDtextEdit");

        formLayout->setWidget(1, QFormLayout::FieldRole, roleDtextEdit);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        saveBtn = new QPushButton(CMngRoles);
        saveBtn->setObjectName("saveBtn");

        horizontalLayout->addWidget(saveBtn);

        delBtn = new QPushButton(CMngRoles);
        delBtn->setObjectName("delBtn");

        horizontalLayout->addWidget(delBtn);

        quitBtn = new QPushButton(CMngRoles);
        quitBtn->setObjectName("quitBtn");

        horizontalLayout->addWidget(quitBtn);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(CMngRoles);

        QMetaObject::connectSlotsByName(CMngRoles);
    } // setupUi

    void retranslateUi(QDialog *CMngRoles)
    {
        CMngRoles->setWindowTitle(QCoreApplication::translate("CMngRoles", "Dialog", nullptr));
        roleNlabel->setText(QCoreApplication::translate("CMngRoles", "Name:", nullptr));
        roleDtext->setText(QCoreApplication::translate("CMngRoles", "Description:", nullptr));
        saveBtn->setText(QCoreApplication::translate("CMngRoles", "Save", nullptr));
        delBtn->setText(QCoreApplication::translate("CMngRoles", "Delete", nullptr));
        quitBtn->setText(QCoreApplication::translate("CMngRoles", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CMngRoles: public Ui_CMngRoles {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MNGROLES_H
