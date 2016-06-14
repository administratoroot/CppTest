#ifndef GTJRESULTSDBMANAGER
#define GTJRESULTSDBMANAGER
#include <vector>
#include "sqlite3.h"

class GTJCheckResultItem;
/************************************************************************/
/*
为检查结果管理类,每次打开云检查，只允许创建一个此类的对象。
类构造时，如果有上次检查历史记录文件，则将历史记录装载到内存。
类析构是，将这次云检查的结果写入硬盘本地文件。
*/
/************************************************************************/
class GTJResultsDBManager
{
public:

    /*!
    * @brief  构造函数，负责内存数据库的创建和初始化
    * @author zhangx-y
    * @date 2016/06/13
    * @return
    * Copyright (c) 1998-2016 Glodon Corporation
    */
    GTJResultsDBManager();
    /*!
    * @brief  析构函数，负责将内存数据库里的内容写入硬盘并且关闭内存数据库连接
    * @author zhangx-y
    * @date 2016/06/13
    * @return
    * Copyright (c) 1998-2016 Glodon Corporation
    */
    ~GTJResultsDBManager();

    /*!
    * @brief  将结果集写到数据库中
    * @author zhangx-y
    * @date 2016/06/12
    * @param[in]  const std::vector<GTJCheckResultItem> & vecResults
    * @return     void
    * Copyright (c) 1998-2016 Glodon Corporation
    */
    void writeResultsToDB(const std::vector<GTJCheckResultItem>& vecResults);


private:
    /*!
    * @brief  初始化检查结果表
    * @author zhangx-y
    * @date 2016/06/12
    * @return     bool 是否成功
    * Copyright (c) 1998-2016 Glodon Corporation
    */
    bool initCheckResultsTable();

private:
    sqlite3* m_pDB;//数据库指针
};

#endif