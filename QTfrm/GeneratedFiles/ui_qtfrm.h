/********************************************************************************
** Form generated from reading UI file 'qtfrm.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTFRM_H
#define UI_QTFRM_H

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

class Ui_QTfrmClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QTfrmClass)
    {
        if (QTfrmClass->objectName().isEmpty())
            QTfrmClass->setObjectName(QStringLiteral("QTfrmClass"));
        QTfrmClass->resize(600, 400);
        menuBar = new QMenuBar(QTfrmClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        QTfrmClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QTfrmClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QTfrmClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QTfrmClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QTfrmClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QTfrmClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QTfrmClass->setStatusBar(statusBar);

        retranslateUi(QTfrmClass);

        QMetaObject::connectSlotsByName(QTfrmClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTfrmClass)
    {
        QTfrmClass->setWindowTitle(QApplication::translate("QTfrmClass", "QTfrm", 0));
    } // retranslateUi

};

namespace Ui {
    class QTfrmClass: public Ui_QTfrmClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTFRM_H
