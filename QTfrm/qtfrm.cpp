#include "qtfrm.h"
#include <QPushButton>
#include "gtjcloudcheckresultfrm.h"
QTfrm::QTfrm(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QPushButton* pBtnOpenCheckResult = new QPushButton(QString::fromLocal8Bit("¼ì²é½á¹û"), this);
    pBtnOpenCheckResult->setGeometry(QRect(100, 150, 100, 20));
    QObject::connect(pBtnOpenCheckResult, SIGNAL(clicked(bool)), this, SLOT(openResultFrm()));
}

QTfrm::~QTfrm()
{

}

void QTfrm::openResultFrm()
{
    GTJCloudCheckResultFrm *pFrm = new GTJCloudCheckResultFrm(this);
    pFrm->show();
}
