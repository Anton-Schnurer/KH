/********************************************************************************
** Form generated from reading UI file 'mngstaff.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MNGSTAFF_H
#define UI_MNGSTAFF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CMngStaff
{
public:
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout;
    QLabel *usernLabel;
    QLineEdit *usernLineEdit;
    QLabel *firstnLabel;
    QLineEdit *firstnLineEdit;
    QLabel *lastNlabel;
    QLineEdit *lastnLineEdit;
    QLabel *phonenLabel;
    QLineEdit *phonenLineEdit;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QLineEdit *lineEdit_3;
    QTableView *rolesTableView;
    QHBoxLayout *horizontalLayout;
    QLabel *rolesLabel;
    QComboBox *rolesComboBox;
    QPushButton *addRoleBtn;
    QPushButton *delRoleBtn;
    QTableView *permTableView;
    QHBoxLayout *horizontalLayout_2;
    QLabel *userPermLabel;
    QComboBox *permComboBox;
    QPushButton *addPermBtn;
    QPushButton *delPermBtn;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *saveBtn;
    QPushButton *delBtn;
    QPushButton *quitBtn;

    void setupUi(QDialog *CMngStaff)
    {
        if (CMngStaff->objectName().isEmpty())
            CMngStaff->setObjectName("CMngStaff");
        CMngStaff->resize(821, 517);
        verticalLayout_2 = new QVBoxLayout(CMngStaff);
        verticalLayout_2->setObjectName("verticalLayout_2");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setHorizontalSpacing(6);
        formLayout->setVerticalSpacing(6);
        usernLabel = new QLabel(CMngStaff);
        usernLabel->setObjectName("usernLabel");

        formLayout->setWidget(0, QFormLayout::LabelRole, usernLabel);

        usernLineEdit = new QLineEdit(CMngStaff);
        usernLineEdit->setObjectName("usernLineEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, usernLineEdit);

        firstnLabel = new QLabel(CMngStaff);
        firstnLabel->setObjectName("firstnLabel");

        formLayout->setWidget(1, QFormLayout::LabelRole, firstnLabel);

        firstnLineEdit = new QLineEdit(CMngStaff);
        firstnLineEdit->setObjectName("firstnLineEdit");

        formLayout->setWidget(1, QFormLayout::FieldRole, firstnLineEdit);

        lastNlabel = new QLabel(CMngStaff);
        lastNlabel->setObjectName("lastNlabel");

        formLayout->setWidget(2, QFormLayout::LabelRole, lastNlabel);

        lastnLineEdit = new QLineEdit(CMngStaff);
        lastnLineEdit->setObjectName("lastnLineEdit");

        formLayout->setWidget(2, QFormLayout::FieldRole, lastnLineEdit);

        phonenLabel = new QLabel(CMngStaff);
        phonenLabel->setObjectName("phonenLabel");

        formLayout->setWidget(3, QFormLayout::LabelRole, phonenLabel);

        phonenLineEdit = new QLineEdit(CMngStaff);
        phonenLineEdit->setObjectName("phonenLineEdit");

        formLayout->setWidget(3, QFormLayout::FieldRole, phonenLineEdit);

        label = new QLabel(CMngStaff);
        label->setObjectName("label");

        formLayout->setWidget(4, QFormLayout::LabelRole, label);

        lineEdit_2 = new QLineEdit(CMngStaff);
        lineEdit_2->setObjectName("lineEdit_2");

        formLayout->setWidget(4, QFormLayout::FieldRole, lineEdit_2);

        label_2 = new QLabel(CMngStaff);
        label_2->setObjectName("label_2");

        formLayout->setWidget(5, QFormLayout::LabelRole, label_2);

        lineEdit_3 = new QLineEdit(CMngStaff);
        lineEdit_3->setObjectName("lineEdit_3");

        formLayout->setWidget(5, QFormLayout::FieldRole, lineEdit_3);


        verticalLayout_2->addLayout(formLayout);

        rolesTableView = new QTableView(CMngStaff);
        rolesTableView->setObjectName("rolesTableView");

        verticalLayout_2->addWidget(rolesTableView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        rolesLabel = new QLabel(CMngStaff);
        rolesLabel->setObjectName("rolesLabel");

        horizontalLayout->addWidget(rolesLabel);

        rolesComboBox = new QComboBox(CMngStaff);
        rolesComboBox->setObjectName("rolesComboBox");

        horizontalLayout->addWidget(rolesComboBox);

        addRoleBtn = new QPushButton(CMngStaff);
        addRoleBtn->setObjectName("addRoleBtn");

        horizontalLayout->addWidget(addRoleBtn);

        delRoleBtn = new QPushButton(CMngStaff);
        delRoleBtn->setObjectName("delRoleBtn");

        horizontalLayout->addWidget(delRoleBtn);


        verticalLayout_2->addLayout(horizontalLayout);

        permTableView = new QTableView(CMngStaff);
        permTableView->setObjectName("permTableView");

        verticalLayout_2->addWidget(permTableView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        userPermLabel = new QLabel(CMngStaff);
        userPermLabel->setObjectName("userPermLabel");

        horizontalLayout_2->addWidget(userPermLabel);

        permComboBox = new QComboBox(CMngStaff);
        permComboBox->setObjectName("permComboBox");

        horizontalLayout_2->addWidget(permComboBox);

        addPermBtn = new QPushButton(CMngStaff);
        addPermBtn->setObjectName("addPermBtn");

        horizontalLayout_2->addWidget(addPermBtn);

        delPermBtn = new QPushButton(CMngStaff);
        delPermBtn->setObjectName("delPermBtn");

        horizontalLayout_2->addWidget(delPermBtn);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        saveBtn = new QPushButton(CMngStaff);
        saveBtn->setObjectName("saveBtn");

        horizontalLayout_3->addWidget(saveBtn);

        delBtn = new QPushButton(CMngStaff);
        delBtn->setObjectName("delBtn");

        horizontalLayout_3->addWidget(delBtn);

        quitBtn = new QPushButton(CMngStaff);
        quitBtn->setObjectName("quitBtn");

        horizontalLayout_3->addWidget(quitBtn);


        verticalLayout_2->addLayout(horizontalLayout_3);


        retranslateUi(CMngStaff);

        QMetaObject::connectSlotsByName(CMngStaff);
    } // setupUi

    void retranslateUi(QDialog *CMngStaff)
    {
        CMngStaff->setWindowTitle(QCoreApplication::translate("CMngStaff", "Dialog", nullptr));
        usernLabel->setText(QCoreApplication::translate("CMngStaff", "Username:", nullptr));
        firstnLabel->setText(QCoreApplication::translate("CMngStaff", "First name:", nullptr));
        lastNlabel->setText(QCoreApplication::translate("CMngStaff", "Last name:", nullptr));
        phonenLabel->setText(QCoreApplication::translate("CMngStaff", "Phone number:", nullptr));
        label->setText(QCoreApplication::translate("CMngStaff", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("CMngStaff", "TextLabel", nullptr));
        rolesLabel->setText(QCoreApplication::translate("CMngStaff", "Roles:", nullptr));
        addRoleBtn->setText(QCoreApplication::translate("CMngStaff", "Add", nullptr));
        delRoleBtn->setText(QCoreApplication::translate("CMngStaff", "Remove", nullptr));
        userPermLabel->setText(QCoreApplication::translate("CMngStaff", "Permissions:", nullptr));
        addPermBtn->setText(QCoreApplication::translate("CMngStaff", "Add", nullptr));
        delPermBtn->setText(QCoreApplication::translate("CMngStaff", "Remove", nullptr));
        saveBtn->setText(QCoreApplication::translate("CMngStaff", "Save", nullptr));
        delBtn->setText(QCoreApplication::translate("CMngStaff", "Delete", nullptr));
        quitBtn->setText(QCoreApplication::translate("CMngStaff", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CMngStaff: public Ui_CMngStaff {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MNGSTAFF_H
