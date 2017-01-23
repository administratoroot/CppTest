#ifndef GTJSQLITECOMMON
#define GTJSQLITECOMMON
#include "sqlite3.h"
#include <QString>
/*!
* @brief  将硬盘中的数据库文件载入到内存，或者将内存数据库回写到硬盘
* @author zhangx-y
* @date 2016/06/12
* @param[in]  sqlite3 * pInMemory 内存中的sqlite数据库指针
* @param[in]  const char * pFilename 硬盘中的数据库文件
* @param[in]  bool bSave 是否保存，如果为true则是将内存数据库写到硬盘，否则则是将硬盘数据库载入到内存
* @return     int 返回值 0表示成功，其他数值含义见sqlite错误码定义
* Copyright (c) 1998-2016 Glodon Corporation
*/
int loadOrSaveDB(sqlite3* pInMemory, const QString& sFilename, bool bSave);

#endif