#include "gtjcloudcheckresultfrm.h"
#include <QTabWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QIcon>

GTJCloudCheckResultFrm::GTJCloudCheckResultFrm(QWidget *parent)
    : QDialog(parent)
{
    setWindowFlags(Qt::Window /*| Qt::FramelessWindowHint*/);
    setFixedSize(400, 800);

    QTabWidget* pTabWidget = new QTabWidget(this);

    //�½���һ��ҳ��Ĳ���
    QWidget *widget1 = new QWidget();
    QVBoxLayout *vLayout = new QVBoxLayout();
    QLabel* lable = new QLabel();
    lable->setText("aaa");
    vLayout->addWidget(lable);
    widget1->setLayout(vLayout);
    //��QTabWidget����ӵ�һ��ҳ��
    pTabWidget->addTab(widget1, QString::fromLocal8Bit("����б�"));

    //�½��ڶ���ҳ��Ĳ���
    QWidget *widget2 = new QWidget();
    QVBoxLayout *vLayout2 = new QVBoxLayout();
    widget2->setLayout(vLayout2);
    //��QTabWidget����ӵڶ���ҳ��
    pTabWidget->addTab(widget2, QString::fromLocal8Bit("�����б�"));

    //�½�������ҳ��Ĳ���
    QWidget *widget3 = new QWidget();
    QVBoxLayout *vLayout3 = new QVBoxLayout();
    widget3->setLayout(vLayout3);
    //��QTabWidget����ӵ�����ҳ��
    pTabWidget->addTab(widget3, QString::fromLocal8Bit("�޸��б�"));

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(pTabWidget);

    this->setLayout(layout);
    this->resize(300, 100);
    this->setWindowTitle(QString::fromLocal8Bit("�����"));
}

GTJCloudCheckResultFrm::~GTJCloudCheckResultFrm()
{

}

void GTJCloudCheckResultFrm::showResultList()
{

}