/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CMainWindow
{
public:
    QAction *actionNew_Patient;
    QAction *actionManage_Staff;
    QAction *actionManage_Patients;
    QAction *actionManage_Cases;
    QAction *actionQuit;
    QAction *actionChange_User;
    QAction *actionManage_Roles;
    QAction *actionManage_Permissions;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *manageStaff;
    QPushButton *managePatients;
    QPushButton *manageCases;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *searchText;
    QPushButton *searchBtn;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *changeUser;
    QSpacerItem *horizontalSpacer;
    QPushButton *quitBtn;
    QMenuBar *menubar;
    QMenu *menuHospital;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CMainWindow)
    {
        if (CMainWindow->objectName().isEmpty())
            CMainWindow->setObjectName("CMainWindow");
        CMainWindow->resize(795, 590);
        actionNew_Patient = new QAction(CMainWindow);
        actionNew_Patient->setObjectName("actionNew_Patient");
        actionManage_Staff = new QAction(CMainWindow);
        actionManage_Staff->setObjectName("actionManage_Staff");
        actionManage_Patients = new QAction(CMainWindow);
        actionManage_Patients->setObjectName("actionManage_Patients");
        actionManage_Cases = new QAction(CMainWindow);
        actionManage_Cases->setObjectName("actionManage_Cases");
        actionQuit = new QAction(CMainWindow);
        actionQuit->setObjectName("actionQuit");
        actionChange_User = new QAction(CMainWindow);
        actionChange_User->setObjectName("actionChange_User");
        actionManage_Roles = new QAction(CMainWindow);
        actionManage_Roles->setObjectName("actionManage_Roles");
        actionManage_Permissions = new QAction(CMainWindow);
        actionManage_Permissions->setObjectName("actionManage_Permissions");
        centralwidget = new QWidget(CMainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        manageStaff = new QPushButton(centralwidget);
        manageStaff->setObjectName("manageStaff");

        horizontalLayout->addWidget(manageStaff);

        managePatients = new QPushButton(centralwidget);
        managePatients->setObjectName("managePatients");

        horizontalLayout->addWidget(managePatients);

        manageCases = new QPushButton(centralwidget);
        manageCases->setObjectName("manageCases");

        horizontalLayout->addWidget(manageCases);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        searchText = new QLineEdit(centralwidget);
        searchText->setObjectName("searchText");

        horizontalLayout_2->addWidget(searchText);

        searchBtn = new QPushButton(centralwidget);
        searchBtn->setObjectName("searchBtn");

        horizontalLayout_2->addWidget(searchBtn);


        verticalLayout->addLayout(horizontalLayout_2);

        tableView = new QTableView(centralwidget);
        tableView->setObjectName("tableView");

        verticalLayout->addWidget(tableView);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        changeUser = new QPushButton(centralwidget);
        changeUser->setObjectName("changeUser");

        horizontalLayout_3->addWidget(changeUser);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        quitBtn = new QPushButton(centralwidget);
        quitBtn->setObjectName("quitBtn");

        horizontalLayout_3->addWidget(quitBtn);


        verticalLayout->addLayout(horizontalLayout_3);

        CMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CMainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 795, 21));
        menuHospital = new QMenu(menubar);
        menuHospital->setObjectName("menuHospital");
        CMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(CMainWindow);
        statusbar->setObjectName("statusbar");
        CMainWindow->setStatusBar(statusbar);

        menubar->addAction(menuHospital->menuAction());
        menuHospital->addAction(actionChange_User);
        menuHospital->addAction(actionManage_Staff);
        menuHospital->addAction(actionManage_Patients);
        menuHospital->addAction(actionManage_Cases);
        menuHospital->addAction(actionManage_Roles);
        menuHospital->addAction(actionManage_Permissions);
        menuHospital->addAction(actionQuit);

        retranslateUi(CMainWindow);

        QMetaObject::connectSlotsByName(CMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CMainWindow)
    {
        CMainWindow->setWindowTitle(QCoreApplication::translate("CMainWindow", "CMainWindow", nullptr));
        actionNew_Patient->setText(QCoreApplication::translate("CMainWindow", "New Patient", nullptr));
        actionManage_Staff->setText(QCoreApplication::translate("CMainWindow", "Manage Staff", nullptr));
        actionManage_Patients->setText(QCoreApplication::translate("CMainWindow", "Manage Patients", nullptr));
        actionManage_Cases->setText(QCoreApplication::translate("CMainWindow", "Manage Cases", nullptr));
        actionQuit->setText(QCoreApplication::translate("CMainWindow", "Quit", nullptr));
        actionChange_User->setText(QCoreApplication::translate("CMainWindow", "Change User", nullptr));
        actionManage_Roles->setText(QCoreApplication::translate("CMainWindow", "Manage Roles", nullptr));
        actionManage_Permissions->setText(QCoreApplication::translate("CMainWindow", "Manage Permissions", nullptr));
        manageStaff->setText(QCoreApplication::translate("CMainWindow", "Manage Staff", nullptr));
        managePatients->setText(QCoreApplication::translate("CMainWindow", "Manage Patients", nullptr));
        manageCases->setText(QCoreApplication::translate("CMainWindow", "Manage Cases", nullptr));
        searchBtn->setText(QCoreApplication::translate("CMainWindow", "Search", nullptr));
        changeUser->setText(QCoreApplication::translate("CMainWindow", "Change User", nullptr));
        quitBtn->setText(QCoreApplication::translate("CMainWindow", "Quit", nullptr));
        menuHospital->setTitle(QCoreApplication::translate("CMainWindow", "Hospital", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CMainWindow: public Ui_CMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
