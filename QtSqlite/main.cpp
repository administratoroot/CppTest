#include "qtsqlite.h"
#include <QtWidgets/QApplication>

#include <QtCore/QCoreApplication>
#include <QtSql>
#include <QDebug>
#include "sqlite3.h"
#include "GTJResultsDBManager.h"
#pragma comment(lib,"sqlite3.lib")


bool sqliteDBMemFile(const QSqlDatabase& memDB,const QString& sFilename, bool bSave)
{
    bool bSuccess = false;
    QVariant v = memDB.driver()->handle();
    if (v.isValid() && qstrcmp(v.typeName(), "sqlite3*") == 0)
    {
        // v.data() returns a pointer to the handle
        sqlite3 * handle = static_cast<sqlite3 *>(v.data());
        if (handle != 0) // check that it is not NULL
        {
            sqlite3 * pInMemory = handle;
            const char * zFilename = "testdb.db"/*sFilename.toLocal8Bit().data()*/;
            int rc = -1; /* Function return code */
            sqlite3 *pFile; /* Database connection opened on zFilename */
            sqlite3_backup *pBackup; /* Backup object used to copy data */
            sqlite3 *pTo; /* Database to copy to (pFile or pInMemory) */
            sqlite3 *pFrom; /* Database to copy from (pFile or pInMemory) */

            rc = sqlite3_open(zFilename, &pFile);
            if (rc == SQLITE_OK)
            {
                pFrom = (bSave ? pInMemory : pFile);
                pTo = (bSave ? pFile : pInMemory);

                pBackup = sqlite3_backup_init(pTo, "main", pFrom, "main");
                if (pBackup)
                {
                    (void)sqlite3_backup_step(pBackup, -1);
                    (void)sqlite3_backup_finish(pBackup);
                }
                rc = sqlite3_errcode(pTo);
            }

            (void)sqlite3_close(pFile);

            if (rc == SQLITE_OK)
            {
                bSuccess = true;
            }
        }
    }
    return bSuccess;
}

void QTSqliteTest()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    //db.setDatabaseName("testDB.db");
    if (!db.open())
    {
        qDebug() << "open database failed ---" << db.lastError().text() << "/n";
        return;
    }

    QSqlQuery query;
    bool ok = query.exec("CREATE TABLE IF NOT EXISTS  people (id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name VARCHAR(20) NOT NULL,"
        "age INTEGER NULL)");
    if (ok)
    {
        qDebug() << "create table partition success/n";
    }
    else
    {
        qDebug() << "create table partition failed/n";
    }

    //写数据
    QTime    tmpTime;
    tmpTime.start();
    db.transaction();
    for (int i = 0; i < 1000; ++i)
    {
        query.prepare("INSERT INTO people (id, name, age) VALUES (:id, :name, :age)");
        query.bindValue(":name", QString("smith_%1").arg(i + 1));
        query.bindValue(":age", i);
        query.exec();
    }
    db.commit();
    qDebug() << QString::fromLocal8Bit("写数据耗时:") << tmpTime.elapsed() << "ms" << endl;
    
    //读数据
    //query.exec("SELECT id, name, age FROM people");
    //while (query.next())
    //{
    //    qDebug() << "people(" << query.value(0).toInt() << ")  name:" << query.value(1).toString() << "  age:" << query.value(2).toInt();
    //}  
    //db.close();

    sqliteDBMemFile(db, "testdb.db", true);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QTSqliteTest();
    GTJResultsDBManager manager;

    QtSqlite w;
    w.show();
    return a.exec();
}
