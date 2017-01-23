#include "sqlite3.h"
#include <iostream>
#include <sstream>
#pragma comment(lib,"sqlite3.lib")
using namespace std;

sqlite3 * pDB = NULL;

int loadOrSaveDb(sqlite3 *pInMemory, const char *zFilename, bool bSave);

bool CreateUserTable();
//增加用户
bool AddUser(const string& sName, const int& nAge);
//删除用户
bool DeleteUser(const string& sName);
//修改用户
bool ModifyUser(const string& sName, const int& nAge);
//查找用户
bool SelectAllUser();

int main()
{
    //打开路径采用utf-8编码
    //如果路径中包含中文，需要进行编码转换
    //int nRes = sqlite3_open(":memory:", &pDB);
    int nRes = sqlite3_open("myDB.db", &pDB);

    if (nRes != SQLITE_OK)
    {
        cout << "Open database fail: " << sqlite3_errmsg(pDB);
        sqlite3_close(pDB);
        return 0;
    }
    if (!CreateUserTable())
    {
        sqlite3_close(pDB);
        return 0;
    }

    int ret;
    char* cErrMsg;
    ret = sqlite3_exec(pDB, "begin transaction", 0, 0, &cErrMsg); // 开始一个事务 
    for (int i = 0; i < 10000; i++)
    {
        stringstream s;
        s << "user";
        s << i;
        AddUser(s.str(), i);
    }
    ret = sqlite3_exec(pDB, "commit transaction", 0, 0, &cErrMsg); // 提交事务 

    ////删除“user100”
    //DeleteUser("user100");

    ////修改“user200”
    //ModifyUser("user200", 0);

    //查找所有用户
    SelectAllUser();

    loadOrSaveDb(pDB, "newdb.db", false);

    SelectAllUser();
    
    sqlite3_close(pDB);
    return 0;
}
bool CreateUserTable()
{
    string strSql = "";
    strSql += "CREATE TABLE IF NOT EXISTS  user(id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name VARCHAR(20) NOT NULL,"
        "age INTEGER NULL)";

    char* cErrMsg;
    int nRes = sqlite3_exec(pDB, strSql.c_str(), 0, 0, &cErrMsg);
    if (nRes != SQLITE_OK)
    {
        cout << "create user table fail: " << cErrMsg << endl;
        return false;
    }
    else
    {
        cout << "create user table success: " << endl;
    }

    return true;
}

bool AddUser(const string& sName, const int& nAge)
{
    stringstream ssSql;
    ssSql << "insert into user(name,age)";
    ssSql << "values('";
    ssSql << sName;
    ssSql << "',";
    ssSql << nAge;
    ssSql << ");";
    string strSql = ssSql.str();
    char* cErrMsg;
    int nRes = sqlite3_exec(pDB, strSql.c_str(), 0, 0, &cErrMsg);
    if (nRes != SQLITE_OK)
    {
        //cout << "add user fail: " << cErrMsg << endl;
        return false;
    }
    else
    {
        //cout << "add user success: " << sName.c_str() << "\t" << nAge<< endl;
    }

    return true;
}

bool DeleteUser(const string& sName)
{
    string strSql = "";
    strSql += "delete from user where name='";
    strSql += sName;
    strSql += "';";

    char* cErrMsg;
    int nRes = sqlite3_exec(pDB, strSql.c_str(), 0, 0, &cErrMsg);
    if (nRes != SQLITE_OK)
    {
        //cout << "delete user fail: " << cErrMsg << endl;
        return false;
    }
    else
    {
        //cout << "delete user success: " << sName.c_str() << endl;
    }

    return true;
}

bool ModifyUser(const string& sName, const int& nAge)
{
    stringstream ssSql;

    ssSql << "update user set age =";
    ssSql << nAge;
    ssSql << " where name='";
    ssSql << sName;
    ssSql << "';";
    string strSql=ssSql.str();
    char* cErrMsg;
    int nRes = sqlite3_exec(pDB, strSql.c_str(), 0, 0, &cErrMsg);
    if (nRes != SQLITE_OK)
    {
        //cout << "modify user fail: " << cErrMsg << endl;
        return false;
    }
    else
    {
        //cout << "modify user success: " << sName.c_str() << "\t" << nAge << endl;
    }

    return true;
}

static int UserResult(void *NotUsed, int argc, char **argv, char **azColName)
{
    for (int i = 0; i < argc; i++)
    {
        cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << ", ";
    }
    cout << endl;

    return 0;
}

bool SelectAllUser()
{
    char* cErrMsg;
    int res = sqlite3_exec(pDB, "select * from user;", UserResult, 0, &cErrMsg);

    if (res != SQLITE_OK)
    {
        //cout << "select fail: " << cErrMsg << endl;
        return false;
    }

    return true;
}

int loadOrSaveDb(sqlite3 *pInMemory, const char *zFilename, bool bSave)
{
    int rc;                   /* Function return code */
    sqlite3 *pFile;           /* Database connection opened on zFilename */
    sqlite3_backup *pBackup;  /* Backup object used to copy data */
    sqlite3 *pTo;             /* Database to copy to (pFile or pInMemory) */
    sqlite3 *pFrom;           /* Database to copy from (pFile or pInMemory) */

    rc = sqlite3_open(zFilename, &pFile);
    if (rc == SQLITE_OK)
    {
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