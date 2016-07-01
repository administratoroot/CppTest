#include "VersionUtil.h"
#include <QStringList>
GTJCouldVersionUtil::EnResult GTJCouldVersionUtil::compareVersion(const QString& sVer1, const QString& sVer2)
{
    //У��汾�ŵ�������ʽ   
    QString pattern("^(\\d\\.)*\\d$");
    QRegExp regExp(pattern);

    bool match = true;
    if (match)
    {
        match = regExp.exactMatch(sVer1);//У��sVer1
    }

    if (match)
    {
        match = regExp.exactMatch(sVer2);//У��sVer2
    }

    if (!match)
    {
        //�����汾����������һ�����Ϸ�
        return ertUnknow;
    }

    //����ִ�
    QStringList sVer1List = sVer1.split(".");
    QStringList sVer2List = sVer2.split(".");
    if (sVer1List.count() != sVer2List.count())
    {
        //���Ȳ���ͬ
        return ertUnknow;
    }
        
    int nCount = sVer1List.count();
    EnResult result = ertEqual;
    for (int i = 0; i < nCount; ++i)
    {
        int nVer1 = sVer1List[i].toInt();
        int nVer2 = sVer2List[i].toInt();
        if (nVer1 > nVer2)
        {
            return ertGreat;
        }
        else if (nVer1 < nVer2)
        {
            return ertLess;
        }
    }
    return result;
}
