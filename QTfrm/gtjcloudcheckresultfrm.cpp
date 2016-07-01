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

    //新建第一个页面的部件
    QWidget *widget1 = new QWidget();
    QVBoxLayout *vLayout = new QVBoxLayout();
    QLabel* lable = new QLabel();
    lable->setText("aaa");
    vLayout->addWidget(lable);
    widget1->setLayout(vLayout);
    //向QTabWidget中添加第一个页面
    pTabWidget->addTab(widget1, QString::fromLocal8Bit("结果列表"));

    //新建第二个页面的部件
    QWidget *widget2 = new QWidget();
    QVBoxLayout *vLayout2 = new QVBoxLayout();
    widget2->setLayout(vLayout2);
    //向QTabWidget中添加第二个页面
    pTabWidget->addTab(widget2, QString::fromLocal8Bit("忽略列表"));

    //新建第三个页面的部件
    QWidget *widget3 = new QWidget();
    QVBoxLayout *vLayout3 = new QVBoxLayout();
    widget3->setLayout(vLayout3);
    //向QTabWidget中添加第三个页面
    pTabWidget->addTab(widget3, QString::fromLocal8Bit("修复列表"));

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(pTabWidget);

    this->setLayout(layout);
    this->resize(300, 100);
    this->setWindowTitle(QString::fromLocal8Bit("检查结果"));
}

GTJCloudCheckResultFrm::~GTJCloudCheckResultFrm()
{

}

void GTJCloudCheckResultFrm::showResultList()
{

}