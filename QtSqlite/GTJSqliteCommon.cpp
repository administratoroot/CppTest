#include "GTJSqliteCommon.h"

int loadOrSaveDB(sqlite3* pInMemory, const QString& sFilename, bool bSave)
{
    int rc = 0;                   //函数返回值
    sqlite3* pFile = nullptr;           //打开的硬盘数据库指针
    sqlite3_backup* pBackup = nullptr;  //拷贝数据临时对象句柄
    sqlite3* pTo = nullptr;             //目标数据库
    sqlite3* pFrom = nullptr;           //源数据库

    /************************************************************************/
    /*
    SQLite提供了以下3个APIs函数用于完成此操作，这里仅仅给出它们的基本用法，
    至于使用细节可以参考SQLite官方网站"APIs Reference"(http://www.sqlite.org/c3ref/backup_finish.html)。
    1). 函数sqlite3_backup_init()用于创建sqlite3_backup对象，该对象将作为本次拷贝操作的句柄传给其余两个函数。
    2). 函数sqlite3_backup_step()用于数据拷贝，如果该函数的第二个参数为-1，那么整个拷贝过程都将在该函数的一次调用中完成。
    3). 函数sqlite3_backup_finish()用于释放sqlite3_backup_init()函数申请的资源，以避免资源泄露。
    在整个拷贝过程中如果出现任何错误，我们都可以通过调用目的数据库连接的sqlite3_errcode()函数来获取具体的错误码。
    此外，如果sqlite3_backup_step()调用失败，由于sqlite3_backup_finish()函数并不会修改当前连接的错误码，因
    此我们可以在调用sqlite3_backup_finish()之后再获取错误码，从而在代码中减少了一次错误处理。
    */
    /************************************************************************/
    //打开本地文件
    std::string sStdFilename = sFilename.toStdString();
    const char* pFilename = sStdFilename.c_str();
    rc = sqlite3_open(pFilename, &pFile);
    if (rc == SQLITE_OK)
    {
        //如果是保存，则是将内存数据库写入硬盘。
        //反之则是将硬盘数据库写入内存
        pFrom = (bSave ? pInMemory : pFile);
        pTo = (bSave ? pFile : pInMemory);

        pBackup = sqlite3_backup_init(pTo, "main", pFrom, "main");
        if (pBackup){
            (void)sqlite3_backup_step(pBackup, -1);
            (void)sqlite3_backup_finish(pBackup);
        }
        rc = sqlite3_errcode(pTo);
    }

    (void)sqlite3_close(pFile);
    return rc;
}

