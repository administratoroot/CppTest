#ifndef GTJCouldVersionUtil_H
#define GTJCouldVersionUtil_H
#include <QString>
class GTJCouldVersionUtil
{
public:
    GTJCouldVersionUtil(){};
    ~GTJCouldVersionUtil(){};

    enum EnResult
    {
        ertUnknow = -1,
        ertLess = 0,
        ertEqual = 1,
        ertGreat = 2
    };

    /*!
    * @brief  �жϰ汾��sVer1�Ƿ����sVer2
    * @author zhangx-y
    * @date 2016/07/01
    * @param[in]  const QString & sVer1
    * @param[in]  const QString & sVer2
    * @return     bool
    * Copyright (c) 1998-2016 Glodon Corporation
    */
    static EnResult compareVersion(const QString& sVer1, const QString& sVer2);

};

#endif // !GTJCouldVersionUtil_H


