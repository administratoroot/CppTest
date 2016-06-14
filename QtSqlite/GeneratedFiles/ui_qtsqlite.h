/********************************************************************************
** Form generated from reading UI file 'qtsqlite.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTSQLITE_H
#define UI_QTSQLITE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtSqliteClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtSqliteClass)
    {
        if (QtSqliteClass->objectName().isEmpty())
            QtSqliteClass->setObjectName(QStringLiteral("QtSqliteClass"));
        QtSqliteClass->resize(600, 400);
        menuBar = new QMenuBar(QtSqliteClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        QtSqliteClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtSqliteClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtSqliteClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QtSqliteClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QtSqliteClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtSqliteClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtSqliteClass->setStatusBar(statusBar);

        retranslateUi(QtSqliteClass);

        QMetaObject::connectSlotsByName(QtSqliteClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtSqliteClass)
    {
        QtSqliteClass->setWindowTitle(QApplication::translate("QtSqliteClass", "QtSqlite", 0));
    } // retranslateUi

};

namespace Ui {
    class QtSqliteClass: public Ui_QtSqliteClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTSQLITE_H
