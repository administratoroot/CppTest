#include "gtjcloudcheckresultfrm.h"
#include <QTabWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QIcon>
const QString sButtonStyleSheet = "QPushButton{font: 75 12px Microsoft YaHei; color: #333333; background:transparent; border:none;}" \
"QPushButton:hover{font: 75 12px Microsoft YaHei; color: #00b4ff; background:transparent; border:none;}";

GTJCloudCheckResultFrm::GTJCloudCheckResultFrm(QWidget *parent)
    : QDialog(parent)
{
    setWindowFlags(Qt::Window /*| Qt::FramelessWindowHint*/);
    setFixedSize(300, 800);

    QPushButton * m_pRefreshResultBtn = new QPushButton();
    //m_pRefreshResultBtn->setMinimumWidth(0);
    m_pRefreshResultBtn->adjustSize();
    m_pRefreshResultBtn->setText(QString::fromLocal8Bit("刷新"));
    m_pRefreshResultBtn->setIcon(QIcon("F:/GitRepos/CppTest/Win32/Debug/images/CheckResult/Refresh.png"));
    m_pRefreshResultBtn->setCursor(Qt::PointingHandCursor);
    m_pRefreshResultBtn->setStyleSheet(sButtonStyleSheet);

    QPushButton* m_pReviewRuleBtn = new QPushButton();
    //m_pRefreshResultBtn->setMinimumWidth(0);
    m_pReviewRuleBtn->setText(QString::fromLocal8Bit("规则设置"));
    m_pReviewRuleBtn->setIcon(QIcon("F:/GitRepos/CppTest/Win32/Debug/images/CheckResult/FindRule.png"));
    m_pReviewRuleBtn->setCursor(Qt::PointingHandCursor);
    m_pReviewRuleBtn->setStyleSheet(sButtonStyleSheet);

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


    QHBoxLayout *HLayout1 = new QHBoxLayout();
    HLayout1->addWidget(m_pRefreshResultBtn);
    HLayout1->addWidget(m_pReviewRuleBtn);
    HLayout1->addSpacing(8);
    HLayout1->addStretch();  // 添加伸缩

    QHBoxLayout *HLayout2 = new QHBoxLayout();
    HLayout2->addWidget(pTabWidget);

    QVBoxLayout *VLayout = new QVBoxLayout();
    VLayout->addLayout(HLayout1);
    VLayout->addLayout(HLayout2);
    VLayout->setContentsMargins(8, 9, 8, 9);
    this->setLayout(VLayout);
    this->resize(300, 100);
    this->setWindowTitle(QString::fromLocal8Bit("检查结果"));

}

GTJCloudCheckResultFrm::~GTJCloudCheckResultFrm()
{

}

void GTJCloudCheckResultFrm::showResultList()
{

}