#ifndef GTJRESULTSDBMANAGER
#define GTJRESULTSDBMANAGER
#include <vector>
#include "sqlite3.h"

class GTJCheckResultItem;
/************************************************************************/
/*
Ϊ�����������,ÿ�δ��Ƽ�飬ֻ������һ������Ķ���
�๹��ʱ��������ϴμ����ʷ��¼�ļ�������ʷ��¼װ�ص��ڴ档
�������ǣ�������Ƽ��Ľ��д��Ӳ�̱����ļ���
*/
/************************************************************************/
class GTJResultsDBManager
{
public:

    /*!
    * @brief  ���캯���������ڴ����ݿ�Ĵ����ͳ�ʼ��
    * @author zhangx-y
    * @date 2016/06/13
    * @return
    * Copyright (c) 1998-2016 Glodon Corporation
    */
    GTJResultsDBManager();
    /*!
    * @brief  ���������������ڴ����ݿ��������д��Ӳ�̲��ҹر��ڴ����ݿ�����
    * @author zhangx-y
    * @date 2016/06/13
    * @return
    * Copyright (c) 1998-2016 Glodon Corporation
    */
    ~GTJResultsDBManager();

    /*!
    * @brief  �������д�����ݿ���
    * @author zhangx-y
    * @date 2016/06/12
    * @param[in]  const std::vector<GTJCheckResultItem> & vecResults
    * @return     void
    * Copyright (c) 1998-2016 Glodon Corporation
    */
    void writeResultsToDB(const std::vector<GTJCheckResultItem>& vecResults);


private:
    /*!
    * @brief  ��ʼ���������
    * @author zhangx-y
    * @date 2016/06/12
    * @return     bool �Ƿ�ɹ�
    * Copyright (c) 1998-2016 Glodon Corporation
    */
    bool initCheckResultsTable();

private:
    sqlite3* m_pDB;//���ݿ�ָ��
};

#endif