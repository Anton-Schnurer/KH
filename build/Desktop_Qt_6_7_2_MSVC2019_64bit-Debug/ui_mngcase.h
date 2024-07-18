/********************************************************************************
** Form generated from reading UI file 'mngcase.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MNGCASE_H
#define UI_MNGCASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CMngCase
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *patientIdLabel;
    QComboBox *patientIdComboBox;
    QLabel *caseSlabel;
    QDateTimeEdit *start_dateTimeEdit;
    QLabel *caseElabel;
    QDateTimeEdit *end_dateTimeEdit;
    QLabel *caseDlabel;
    QTextEdit *caseDtextEdit;
    QTableView *staffTableView;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QComboBox *staffIdComboBox;
    QPushButton *addStaffBtn;
    QPushButton *delStaffBtn;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *saveBtn;
    QPushButton *delBtn;
    QPushButton *quitBtn;

    void setupUi(QDialog *CMngCase)
    {
        if (CMngCase->objectName().isEmpty())
            CMngCase->setObjectName("CMngCase");
        CMngCase->resize(594, 463);
        formLayoutWidget = new QWidget(CMngCase);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(9, 9, 571, 311));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        patientIdLabel = new QLabel(formLayoutWidget);
        patientIdLabel->setObjectName("patientIdLabel");

        formLayout->setWidget(0, QFormLayout::LabelRole, patientIdLabel);

        patientIdComboBox = new QComboBox(formLayoutWidget);
        patientIdComboBox->setObjectName("patientIdComboBox");

        formLayout->setWidget(0, QFormLayout::FieldRole, patientIdComboBox);

        caseSlabel = new QLabel(formLayoutWidget);
        caseSlabel->setObjectName("caseSlabel");

        formLayout->setWidget(1, QFormLayout::LabelRole, caseSlabel);

        start_dateTimeEdit = new QDateTimeEdit(formLayoutWidget);
        start_dateTimeEdit->setObjectName("start_dateTimeEdit");

        formLayout->setWidget(1, QFormLayout::FieldRole, start_dateTimeEdit);

        caseElabel = new QLabel(formLayoutWidget);
        caseElabel->setObjectName("caseElabel");

        formLayout->setWidget(2, QFormLayout::LabelRole, caseElabel);

        end_dateTimeEdit = new QDateTimeEdit(formLayoutWidget);
        end_dateTimeEdit->setObjectName("end_dateTimeEdit");

        formLayout->setWidget(2, QFormLayout::FieldRole, end_dateTimeEdit);

        caseDlabel = new QLabel(formLayoutWidget);
        caseDlabel->setObjectName("caseDlabel");

        formLayout->setWidget(3, QFormLayout::LabelRole, caseDlabel);

        caseDtextEdit = new QTextEdit(formLayoutWidget);
        caseDtextEdit->setObjectName("caseDtextEdit");

        formLayout->setWidget(3, QFormLayout::FieldRole, caseDtextEdit);

        staffTableView = new QTableView(CMngCase);
        staffTableView->setObjectName("staffTableView");
        staffTableView->setGeometry(QRect(10, 330, 571, 51));
        horizontalLayoutWidget = new QWidget(CMngCase);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(10, 390, 571, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        staffIdComboBox = new QComboBox(horizontalLayoutWidget);
        staffIdComboBox->setObjectName("staffIdComboBox");

        horizontalLayout->addWidget(staffIdComboBox);

        addStaffBtn = new QPushButton(horizontalLayoutWidget);
        addStaffBtn->setObjectName("addStaffBtn");

        horizontalLayout->addWidget(addStaffBtn);

        delStaffBtn = new QPushButton(horizontalLayoutWidget);
        delStaffBtn->setObjectName("delStaffBtn");

        horizontalLayout->addWidget(delStaffBtn);

        horizontalLayoutWidget_2 = new QWidget(CMngCase);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(10, 420, 571, 31));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        saveBtn = new QPushButton(horizontalLayoutWidget_2);
        saveBtn->setObjectName("saveBtn");

        horizontalLayout_2->addWidget(saveBtn);

        delBtn = new QPushButton(horizontalLayoutWidget_2);
        delBtn->setObjectName("delBtn");

        horizontalLayout_2->addWidget(delBtn);

        quitBtn = new QPushButton(horizontalLayoutWidget_2);
        quitBtn->setObjectName("quitBtn");

        horizontalLayout_2->addWidget(quitBtn);


        retranslateUi(CMngCase);

        QMetaObject::connectSlotsByName(CMngCase);
    } // setupUi

    void retranslateUi(QDialog *CMngCase)
    {
        CMngCase->setWindowTitle(QCoreApplication::translate("CMngCase", "Dialog", nullptr));
        patientIdLabel->setText(QCoreApplication::translate("CMngCase", "Patient: ", nullptr));
        caseSlabel->setText(QCoreApplication::translate("CMngCase", "Start: ", nullptr));
        caseElabel->setText(QCoreApplication::translate("CMngCase", "End:", nullptr));
        caseDlabel->setText(QCoreApplication::translate("CMngCase", "Description: ", nullptr));
        addStaffBtn->setText(QCoreApplication::translate("CMngCase", "Add", nullptr));
        delStaffBtn->setText(QCoreApplication::translate("CMngCase", "Remove", nullptr));
        saveBtn->setText(QCoreApplication::translate("CMngCase", "Save", nullptr));
        delBtn->setText(QCoreApplication::translate("CMngCase", "Delete", nullptr));
        quitBtn->setText(QCoreApplication::translate("CMngCase", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CMngCase: public Ui_CMngCase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MNGCASE_H
