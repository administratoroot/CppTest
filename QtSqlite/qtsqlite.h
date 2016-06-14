#ifndef QTSQLITE_H
#define QTSQLITE_H

#include <QtWidgets/QMainWindow>
#include "ui_qtsqlite.h"

class QtSqlite : public QMainWindow
{
    Q_OBJECT

public:
    QtSqlite(QWidget *parent = 0);
    ~QtSqlite();

private:
    Ui::QtSqliteClass ui;
};

#endif // QTSQLITE_H
