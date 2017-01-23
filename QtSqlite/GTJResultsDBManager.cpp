#include "GTJResultsDBManager.h"
#include <QString>
#include <QFile>
#include <QDebug>
#include "GTJSqliteCommon.h"
const QString sLocalDBName = "CloudCheckResults.db";

GTJResultsDBManager::GTJResultsDBManager()
{
    sqlite3* pLocalDB = nullptr;
    int nRes = -1;//�򿪽����־
    //���ڴ��д���m_pDB���ݿ�
    nRes = sqlite3_open(":memory:", &m_pDB);
    if (nRes != SQLITE_OK)
    {
        qDebug() << "Open database fail: " << sqlite3_errmsg(m_pDB) << endl;
        sqlite3_close(m_pDB);
    }

    //��һ�δ�ʱ���������ʷ��¼װ�ص��ڴ�
    QFile file(sLocalDBName);//���ڱ��ر�������ݿ��ļ�
    if (file.exists())
    {
        //�������ʷ��¼װ�ص��ڴ�
        int nLoadRes = loadOrSaveDB(m_pDB, sLocalDBName, false);
        qDebug() << "Open LocalDatabase fail" << endl;
    }

    initCheckResultsTable();
}

GTJResultsDBManager::~GTJResultsDBManager()
{
    QFile file(sLocalDBName);//���ڱ��ر�������ݿ��ļ�
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
    //1.��ʼ���ݿ����� 
    int nResTransaction = sqlite3_exec(m_pDB, "begin transaction", 0, 0, &cErrMsg);
    if (nResTransaction != SQLITE_OK)
    {
        qDebug() << "start transaction fail: " << cErrMsg << endl;
        return false;
    }
    //2.CheckResults�������򴴽�һ����
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

    //3.���CheckResults������
    QString sClearTableSql = "DELETE FROM CheckResults";
    int nResClearTable = sqlite3_exec(m_pDB, sCreateTableSql.toStdString().c_str(), 0, 0, &cErrMsg);
    if (nResClearTable != SQLITE_OK)
    {
        qDebug() << "clear CheckResults table fail: " << cErrMsg << endl;
        return false;
    }

    //4.������ID��0
    QString sResetIDSql = "UPDATE SQLITE_SEQUENCE SET SEQ = 0 WHERE NAME = 'CheckResults'";
    int nResResetID = sqlite3_exec(m_pDB, sResetIDSql.toStdString().c_str(), 0, 0, &cErrMsg);
    if (nResResetID != SQLITE_OK)
    {
        qDebug() << "clear Reset ID fail: " << cErrMsg << endl;
        return false;
    }

    //5.�ύ����
    nResTransaction = sqlite3_exec(m_pDB, "commit transaction", 0, 0, &cErrMsg); // �ύ����
    if (nResTransaction != SQLITE_OK)
    {
        qDebug() << "commit transaction fail: " << cErrMsg << endl;
        return false;
    }

    //6.�ͷŴ�����Ϣ�ڴ�
    sqlite3_free(cErrMsg);

    return true;
}
