#ifndef QTFRM_H
#define QTFRM_H

#include <QtWidgets/QMainWindow>
#include "ui_qtfrm.h"

class QTfrm : public QMainWindow
{
    Q_OBJECT

public:
    QTfrm(QWidget *parent = 0);
    ~QTfrm();

private slots:
  void openResultFrm();
private:
    Ui::QTfrmClass ui;
};

#endif // QTFRM_H
