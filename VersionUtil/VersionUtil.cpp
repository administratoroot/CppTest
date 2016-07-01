#include "VersionUtil.h"
#include <QStringList>
GTJCouldVersionUtil::EnResult GTJCouldVersionUtil::compareVersion(const QString& sVer1, const QString& sVer2)
{
    //校验版本号的正则表达式   
    QString pattern("^(\\d\\.)*\\d$");
    QRegExp regExp(pattern);

    bool match = true;
    if (match)
    {
        match = regExp.exactMatch(sVer1);//校验sVer1
    }

    if (match)
    {
        match = regExp.exactMatch(sVer2);//校验sVer2
    }

    if (!match)
    {
        //两个版本号中至少有一个不合法
        return ertUnknow;
    }

    //拆分字串
    QStringList sVer1List = sVer1.split(".");
    QStringList sVer2List = sVer2.split(".");
    if (sVer1List.count() != sVer2List.count())
    {
        //长度不相同
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
