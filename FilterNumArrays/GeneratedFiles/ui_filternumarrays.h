/********************************************************************************
** Form generated from reading UI file 'filternumarrays.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTERNUMARRAYS_H
#define UI_FILTERNUMARRAYS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FilterNumArraysClass
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QPlainTextEdit *plainTextEdit30;
    QPlainTextEdit *plainTextEdit_02;
    QPlainTextEdit *plainTextEdit_31;
    QPlainTextEdit *plainTextEdit_21;
    QPlainTextEdit *plainTextEdit_32;
    QPlainTextEdit *plainTextEdit_20;
    QPlainTextEdit *plainTextEdit_00;
    QPlainTextEdit *plainTextEdit_14;
    QPlainTextEdit *plainTextEdit_13;
    QPlainTextEdit *plainTextEdit_15;
    QPlainTextEdit *plainTextEdit_01;
    QPlainTextEdit *plainTextEdit_22;
    QPushButton *pushButton;
    QPlainTextEdit *plainTextEdit_Result;

    void setupUi(QDialog *FilterNumArraysClass)
    {
        if (FilterNumArraysClass->objectName().isEmpty())
            FilterNumArraysClass->setObjectName(QStringLiteral("FilterNumArraysClass"));
        FilterNumArraysClass->resize(659, 534);
        QIcon icon;
        icon.addFile(QStringLiteral(":/FilterNumArrays/Resources/logo.ico"), QSize(), QIcon::Normal, QIcon::Off);
        FilterNumArraysClass->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(FilterNumArraysClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        plainTextEdit30 = new QPlainTextEdit(FilterNumArraysClass);
        plainTextEdit30->setObjectName(QStringLiteral("plainTextEdit30"));

        gridLayout->addWidget(plainTextEdit30, 3, 0, 1, 1);

        plainTextEdit_02 = new QPlainTextEdit(FilterNumArraysClass);
        plainTextEdit_02->setObjectName(QStringLiteral("plainTextEdit_02"));

        gridLayout->addWidget(plainTextEdit_02, 0, 2, 1, 1);

        plainTextEdit_31 = new QPlainTextEdit(FilterNumArraysClass);
        plainTextEdit_31->setObjectName(QStringLiteral("plainTextEdit_31"));

        gridLayout->addWidget(plainTextEdit_31, 3, 1, 1, 1);

        plainTextEdit_21 = new QPlainTextEdit(FilterNumArraysClass);
        plainTextEdit_21->setObjectName(QStringLiteral("plainTextEdit_21"));

        gridLayout->addWidget(plainTextEdit_21, 2, 1, 1, 1);

        plainTextEdit_32 = new QPlainTextEdit(FilterNumArraysClass);
        plainTextEdit_32->setObjectName(QStringLiteral("plainTextEdit_32"));

        gridLayout->addWidget(plainTextEdit_32, 3, 2, 1, 1);

        plainTextEdit_20 = new QPlainTextEdit(FilterNumArraysClass);
        plainTextEdit_20->setObjectName(QStringLiteral("plainTextEdit_20"));

        gridLayout->addWidget(plainTextEdit_20, 2, 0, 1, 1);

        plainTextEdit_00 = new QPlainTextEdit(FilterNumArraysClass);
        plainTextEdit_00->setObjectName(QStringLiteral("plainTextEdit_00"));

        gridLayout->addWidget(plainTextEdit_00, 0, 0, 1, 1);

        plainTextEdit_14 = new QPlainTextEdit(FilterNumArraysClass);
        plainTextEdit_14->setObjectName(QStringLiteral("plainTextEdit_14"));

        gridLayout->addWidget(plainTextEdit_14, 1, 1, 1, 1);

        plainTextEdit_13 = new QPlainTextEdit(FilterNumArraysClass);
        plainTextEdit_13->setObjectName(QStringLiteral("plainTextEdit_13"));

        gridLayout->addWidget(plainTextEdit_13, 1, 0, 1, 1);

        plainTextEdit_15 = new QPlainTextEdit(FilterNumArraysClass);
        plainTextEdit_15->setObjectName(QStringLiteral("plainTextEdit_15"));

        gridLayout->addWidget(plainTextEdit_15, 1, 2, 1, 1);

        plainTextEdit_01 = new QPlainTextEdit(FilterNumArraysClass);
        plainTextEdit_01->setObjectName(QStringLiteral("plainTextEdit_01"));

        gridLayout->addWidget(plainTextEdit_01, 0, 1, 1, 1);

        plainTextEdit_22 = new QPlainTextEdit(FilterNumArraysClass);
        plainTextEdit_22->setObjectName(QStringLiteral("plainTextEdit_22"));

        gridLayout->addWidget(plainTextEdit_22, 2, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        pushButton = new QPushButton(FilterNumArraysClass);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        plainTextEdit_Result = new QPlainTextEdit(FilterNumArraysClass);
        plainTextEdit_Result->setObjectName(QStringLiteral("plainTextEdit_Result"));

        verticalLayout->addWidget(plainTextEdit_Result);


        retranslateUi(FilterNumArraysClass);

        QMetaObject::connectSlotsByName(FilterNumArraysClass);
    } // setupUi

    void retranslateUi(QDialog *FilterNumArraysClass)
    {
        FilterNumArraysClass->setWindowTitle(QApplication::translate("FilterNumArraysClass", "\346\216\222\345\210\227\344\270\211\347\224\237\346\210\220\345\231\250", 0));
        pushButton->setText(QApplication::translate("FilterNumArraysClass", "\347\273\223\347\256\227\347\273\223\346\236\234", 0));
    } // retranslateUi

};

namespace Ui {
    class FilterNumArraysClass: public Ui_FilterNumArraysClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTERNUMARRAYS_H
