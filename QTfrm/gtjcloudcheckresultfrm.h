#ifndef GTJCLOUDCHECKRESULTFRM_H
#define GTJCLOUDCHECKRESULTFRM_H

#include <QDialog>
class QTabWidget;
class GTJCloudCheckResultFrm : public QDialog
{
    Q_OBJECT

public:
    GTJCloudCheckResultFrm(QWidget *parent);
    ~GTJCloudCheckResultFrm();
private slots :
    void showResultList();
private:
};

#endif // GTJCLOUDCHECKRESULTFRM_H
