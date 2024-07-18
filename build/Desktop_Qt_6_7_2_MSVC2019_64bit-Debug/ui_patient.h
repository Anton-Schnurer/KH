/********************************************************************************
** Form generated from reading UI file 'patient.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATIENT_H
#define UI_PATIENT_H

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

class Ui_CPatient
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *searchPlineEdit;
    QPushButton *searchPBtn;
    QTableView *patientTableView;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *newPatientBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *quitBtn;

    void setupUi(QDialog *CPatient)
    {
        if (CPatient->objectName().isEmpty())
            CPatient->setObjectName("CPatient");
        CPatient->resize(811, 661);
        verticalLayout = new QVBoxLayout(CPatient);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        searchPlineEdit = new QLineEdit(CPatient);
        searchPlineEdit->setObjectName("searchPlineEdit");

        horizontalLayout->addWidget(searchPlineEdit);

        searchPBtn = new QPushButton(CPatient);
        searchPBtn->setObjectName("searchPBtn");

        horizontalLayout->addWidget(searchPBtn);


        verticalLayout->addLayout(horizontalLayout);

        patientTableView = new QTableView(CPatient);
        patientTableView->setObjectName("patientTableView");

        verticalLayout->addWidget(patientTableView);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        newPatientBtn = new QPushButton(CPatient);
        newPatientBtn->setObjectName("newPatientBtn");

        horizontalLayout_2->addWidget(newPatientBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        quitBtn = new QPushButton(CPatient);
        quitBtn->setObjectName("quitBtn");

        horizontalLayout_2->addWidget(quitBtn);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(CPatient);

        QMetaObject::connectSlotsByName(CPatient);
    } // setupUi

    void retranslateUi(QDialog *CPatient)
    {
        CPatient->setWindowTitle(QCoreApplication::translate("CPatient", "Dialog", nullptr));
        searchPBtn->setText(QCoreApplication::translate("CPatient", "Search", nullptr));
        newPatientBtn->setText(QCoreApplication::translate("CPatient", "New Patient", nullptr));
        quitBtn->setText(QCoreApplication::translate("CPatient", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CPatient: public Ui_CPatient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATIENT_H
