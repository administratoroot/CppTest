#include "qtfrm.h"
#include <QtWidgets/QApplication>
#include <QDialog>
#include <QLabel>
#include <QLayout>
#include <QTextBrowser>
#include <QFile>
#include <QSettings>

//读文件
void readFeedbackOptions(QString sGroup, bool& bEnable, QString& sUrl)
{
    const QString sPath = "C:/test.ini";
    if (sPath.isEmpty())
    {
        bEnable = false;
        sUrl = QString();
    }
    else
    {
        //创建配置文件操作对象
        QSettings *config = new QSettings(sPath, QSettings::IniFormat);
        
        //读取用户配置信息
        if (config->contains(sGroup + "Enable") && config->contains(sGroup + "Url"))
        {
            bEnable = config->value(sGroup + "Enable").toBool();
            sUrl = config->value(sGroup + "Url").toString();
        }
        else
        {
            bEnable = false;
            sUrl = QString();
        }
    }
}

//弹框
void initCloudCheckFeedbackDlg()
{
    
    QString sGroup = QString("CloudCheckFeedbackFrm/");
    bool bEnable = false;
    QString sUrl;
    readFeedbackOptions(sGroup, bEnable, sUrl);
    if (bEnable)
    {
        const QString sFontStyleSheet = "QLabel{font: 75 16px Microsoft YaHei; color: black; background:transparent; border:transparent;}";
        const QString sFeedbackStyle = "QLabel{font: 75 16px Microsoft YaHei;}";
        QDialog dialog;
        dialog.setWindowTitle(QString::fromLocal8Bit("反馈表"));
        dialog.setFixedSize(400, 200);
        QVBoxLayout* pVBoxLayout = new QVBoxLayout;
        QHBoxLayout* pHLayout1 = new QHBoxLayout;
        QLabel *pTextLabel = new QLabel(QString::fromLocal8Bit("新产品体验完成，填写一下您的感受吧"));
        pTextLabel->setStyleSheet(sFontStyleSheet);
        pHLayout1->setContentsMargins(0, 20, 0, 0);
        pHLayout1->addStretch();
        pHLayout1->addWidget(pTextLabel);
        pHLayout1->addStretch();


        QHBoxLayout* pHLayout2 = new QHBoxLayout;
        QLabel* pLinkLabel = new QLabel();
        pLinkLabel->setOpenExternalLinks(true);
        pLinkLabel->setText("<a href =" + sUrl + " >" + QString::fromLocal8Bit("反馈表") + "</a>");
        pLinkLabel->setStyleSheet(sFeedbackStyle);
        pHLayout2->setContentsMargins(0, 20, 0, 0);
        pHLayout2->addStretch();
        pHLayout2->addWidget(pLinkLabel);
        pHLayout2->addStretch();

        pVBoxLayout->addLayout(pHLayout1);
        pVBoxLayout->addLayout(pHLayout2);

        pVBoxLayout->addStretch();
        dialog.setLayout(pVBoxLayout);
        dialog.exec();
    }
    
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QTfrm w;
    //w.show();


    initCloudCheckFeedbackDlg();
    return a.exec();
}
