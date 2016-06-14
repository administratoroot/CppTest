#include "GTJSqliteCommon.h"

int loadOrSaveDB(sqlite3* pInMemory, const QString& sFilename, bool bSave)
{
    int rc = 0;                   //��������ֵ
    sqlite3* pFile = nullptr;           //�򿪵�Ӳ�����ݿ�ָ��
    sqlite3_backup* pBackup = nullptr;  //����������ʱ������
    sqlite3* pTo = nullptr;             //Ŀ�����ݿ�
    sqlite3* pFrom = nullptr;           //Դ���ݿ�

    /************************************************************************/
    /*
    SQLite�ṩ������3��APIs����������ɴ˲�������������������ǵĻ����÷���
    ����ʹ��ϸ�ڿ��Բο�SQLite�ٷ���վ"APIs Reference"(http://www.sqlite.org/c3ref/backup_finish.html)��
    1). ����sqlite3_backup_init()���ڴ���sqlite3_backup���󣬸ö�����Ϊ���ο��������ľ��������������������
    2). ����sqlite3_backup_step()�������ݿ���������ú����ĵڶ�������Ϊ-1����ô�����������̶����ڸú�����һ�ε�������ɡ�
    3). ����sqlite3_backup_finish()�����ͷ�sqlite3_backup_init()�����������Դ���Ա�����Դй¶��
    ������������������������κδ������Ƕ�����ͨ������Ŀ�����ݿ����ӵ�sqlite3_errcode()��������ȡ����Ĵ����롣
    ���⣬���sqlite3_backup_step()����ʧ�ܣ�����sqlite3_backup_finish()�����������޸ĵ�ǰ���ӵĴ����룬��
    �����ǿ����ڵ���sqlite3_backup_finish()֮���ٻ�ȡ�����룬�Ӷ��ڴ����м�����һ�δ�����
    */
    /************************************************************************/
    //�򿪱����ļ�
    std::string sStdFilename = sFilename.toStdString();
    const char* pFilename = sStdFilename.c_str();
    rc = sqlite3_open(pFilename, &pFile);
    if (rc == SQLITE_OK)
    {
        //����Ǳ��棬���ǽ��ڴ����ݿ�д��Ӳ�̡�
        //��֮���ǽ�Ӳ�����ݿ�д���ڴ�
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

