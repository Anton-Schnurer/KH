/********************************************************************************
** Form generated from reading UI file 'mngpatient.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MNGPATIENT_H
#define UI_MNGPATIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CMngPatient
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *firstnLabel;
    QLineEdit *firstnLineEdit;
    QLabel *lastnLabel;
    QLineEdit *lastnLineEdit;
    QLabel *phonenLabel;
    QLineEdit *phonenLineEdit;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *saveBtn;
    QPushButton *delBtn;
    QPushButton *quitBtn;

    void setupUi(QDialog *CMngPatient)
    {
        if (CMngPatient->objectName().isEmpty())
            CMngPatient->setObjectName("CMngPatient");
        CMngPatient->resize(531, 221);
        verticalLayout = new QVBoxLayout(CMngPatient);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        firstnLabel = new QLabel(CMngPatient);
        firstnLabel->setObjectName("firstnLabel");

        formLayout->setWidget(0, QFormLayout::LabelRole, firstnLabel);

        firstnLineEdit = new QLineEdit(CMngPatient);
        firstnLineEdit->setObjectName("firstnLineEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, firstnLineEdit);

        lastnLabel = new QLabel(CMngPatient);
        lastnLabel->setObjectName("lastnLabel");

        formLayout->setWidget(1, QFormLayout::LabelRole, lastnLabel);

        lastnLineEdit = new QLineEdit(CMngPatient);
        lastnLineEdit->setObjectName("lastnLineEdit");

        formLayout->setWidget(1, QFormLayout::FieldRole, lastnLineEdit);

        phonenLabel = new QLabel(CMngPatient);
        phonenLabel->setObjectName("phonenLabel");

        formLayout->setWidget(2, QFormLayout::LabelRole, phonenLabel);

        phonenLineEdit = new QLineEdit(CMngPatient);
        phonenLineEdit->setObjectName("phonenLineEdit");

        formLayout->setWidget(2, QFormLayout::FieldRole, phonenLineEdit);

        label = new QLabel(CMngPatient);
        label->setObjectName("label");

        formLayout->setWidget(3, QFormLayout::LabelRole, label);

        lineEdit = new QLineEdit(CMngPatient);
        lineEdit->setObjectName("lineEdit");

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEdit);

        label_2 = new QLabel(CMngPatient);
        label_2->setObjectName("label_2");

        formLayout->setWidget(4, QFormLayout::LabelRole, label_2);

        lineEdit_2 = new QLineEdit(CMngPatient);
        lineEdit_2->setObjectName("lineEdit_2");

        formLayout->setWidget(4, QFormLayout::FieldRole, lineEdit_2);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        saveBtn = new QPushButton(CMngPatient);
        saveBtn->setObjectName("saveBtn");

        horizontalLayout->addWidget(saveBtn);

        delBtn = new QPushButton(CMngPatient);
        delBtn->setObjectName("delBtn");

        horizontalLayout->addWidget(delBtn);

        quitBtn = new QPushButton(CMngPatient);
        quitBtn->setObjectName("quitBtn");

        horizontalLayout->addWidget(quitBtn);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(CMngPatient);

        QMetaObject::connectSlotsByName(CMngPatient);
    } // setupUi

    void retranslateUi(QDialog *CMngPatient)
    {
        CMngPatient->setWindowTitle(QCoreApplication::translate("CMngPatient", "Dialog", nullptr));
        firstnLabel->setText(QCoreApplication::translate("CMngPatient", "First name: ", nullptr));
        lastnLabel->setText(QCoreApplication::translate("CMngPatient", "Last name:", nullptr));
        phonenLabel->setText(QCoreApplication::translate("CMngPatient", "Phone number:", nullptr));
        label->setText(QCoreApplication::translate("CMngPatient", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("CMngPatient", "TextLabel", nullptr));
        saveBtn->setText(QCoreApplication::translate("CMngPatient", "Save", nullptr));
        delBtn->setText(QCoreApplication::translate("CMngPatient", "Delete", nullptr));
        quitBtn->setText(QCoreApplication::translate("CMngPatient", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CMngPatient: public Ui_CMngPatient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MNGPATIENT_H
