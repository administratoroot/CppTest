#ifndef GTJSQLITECOMMON
#define GTJSQLITECOMMON
#include "sqlite3.h"
#include <QString>
/*!
* @brief  ��Ӳ���е����ݿ��ļ����뵽�ڴ棬���߽��ڴ����ݿ��д��Ӳ��
* @author zhangx-y
* @date 2016/06/12
* @param[in]  sqlite3 * pInMemory �ڴ��е�sqlite���ݿ�ָ��
* @param[in]  const char * pFilename Ӳ���е����ݿ��ļ�
* @param[in]  bool bSave �Ƿ񱣴棬���Ϊtrue���ǽ��ڴ����ݿ�д��Ӳ�̣��������ǽ�Ӳ�����ݿ����뵽�ڴ�
* @return     int ����ֵ 0��ʾ�ɹ���������ֵ�����sqlite�����붨��
* Copyright (c) 1998-2016 Glodon Corporation
*/
int loadOrSaveDB(sqlite3* pInMemory, const QString& sFilename, bool bSave);

#endif