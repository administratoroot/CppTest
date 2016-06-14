#include "GTJResultsDBManager.h"
#include <QString>
#include <QFile>
#include <QDebug>
#include "GTJSqliteCommon.h"
const QString sLocalDBName = "CloudCheckResults.db";

GTJResultsDBManager::GTJResultsDBManager()
{
    sqlite3* pLocalDB = nullptr;
    int nRes = -1;//打开结果标志
    //在内存中创建m_pDB数据库
    nRes = sqlite3_open(":memory:", &m_pDB);
    if (nRes != SQLITE_OK)
    {
        qDebug() << "Open database fail: " << sqlite3_errmsg(m_pDB) << endl;
        sqlite3_close(m_pDB);
    }

    //第一次打开时，将检查历史记录装载到内存
    QFile file(sLocalDBName);//存在本地保存的数据库文件
    if (file.exists())
    {
        //将检查历史记录装载到内存
        int nLoadRes = loadOrSaveDB(m_pDB, sLocalDBName, false);
        qDebug() << "Open LocalDatabase fail" << endl;
    }

    initCheckResultsTable();
}

GTJResultsDBManager::~GTJResultsDBManager()
{
    QFile file(sLocalDBName);//存在本地保存的数据库文件
    if (file.exists())
    {
        file.remove();
    }
    loadOrSaveDB(m_pDB, sLocalDBName, true);
    sqlite3_close(m_pDB);
}

void GTJResultsDBManager::writeResultsToDB(const std::vector<GTJCheckResultItem>& vecResults)
{

}

bool GTJResultsDBManager::initCheckResultsTable()
{
    char* cErrMsg = nullptr;
    //1.开始数据库事务 
    int nResTransaction = sqlite3_exec(m_pDB, "begin transaction", 0, 0, &cErrMsg);
    if (nResTransaction != SQLITE_OK)
    {
        qDebug() << "start transaction fail: " << cErrMsg << endl;
        return false;
    }
    //2.CheckResults表不存在则创建一个表
    QString sCreateTableSql = "CREATE TABLE IF NOT EXISTS CheckResults(ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "EDOID INTEGER NULL, "
        "RuleID INTEGER NULL, "
        "EntTypeID INTEGER NULL, "
        "FloorID INTEGER NULL, "
        "StrategyID INTEGER NULL, "
        "ErrType INTEGER NULL, "
        "ErrorPrompt VARCHAR(20) NOT NULL,"
        "RegionID INTEGER NULL, "
        "Ignored INTEGER NULL)";
    int nResCreateTable = sqlite3_exec(m_pDB, sCreateTableSql.toStdString().c_str(), 0, 0, &cErrMsg);
    if (nResCreateTable != SQLITE_OK)
    {
        qDebug() << "create CheckResults table fail: " << cErrMsg << endl;
        return false;
    }

    //3.清空CheckResults表内容
    QString sClearTableSql = "DELETE FROM CheckResults";
    int nResClearTable = sqlite3_exec(m_pDB, sCreateTableSql.toStdString().c_str(), 0, 0, &cErrMsg);
    if (nResClearTable != SQLITE_OK)
    {
        qDebug() << "clear CheckResults table fail: " << cErrMsg << endl;
        return false;
    }

    //4.自增长ID置0
    QString sResetIDSql = "UPDATE SQLITE_SEQUENCE SET SEQ = 0 WHERE NAME = 'CheckResults'";
    int nResResetID = sqlite3_exec(m_pDB, sResetIDSql.toStdString().c_str(), 0, 0, &cErrMsg);
    if (nResResetID != SQLITE_OK)
    {
        qDebug() << "clear Reset ID fail: " << cErrMsg << endl;
        return false;
    }

    //5.提交事务
    nResTransaction = sqlite3_exec(m_pDB, "commit transaction", 0, 0, &cErrMsg); // 提交事务
    if (nResTransaction != SQLITE_OK)
    {
        qDebug() << "commit transaction fail: " << cErrMsg << endl;
        return false;
    }

    //6.释放错误信息内存
    sqlite3_free(cErrMsg);

    return true;
}
