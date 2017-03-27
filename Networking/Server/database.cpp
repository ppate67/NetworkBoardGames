#include "database.h"
#include <QSqlDatabase>
using namespace std;
//Use http://doc.qt.io/qt-5/qsqldatabase.html for more database commands 
//from QSQLDatabase

//https://katecpp.wordpress.com/2015/08/28/sqlite-with-qt/

QT += sql

class DbManager
{
private:
    QSqlDatabase m_db;
public:
    DbManager(const QString& path);
};

DbManager::DbManager(const QString& path)
{
   m_db = QSqlDatabase::addDatabase("QSQLITE");
   m_db.setDatabaseName(path);
 
   if (!m_db.open())
   {
      qDebug() << "Error: connection with database fail";
   }
   else
   {
      qDebug() << "Database: connection ok";
   }
}

bool DbManager::addPerson(const QString& name) //Refers to new Player
{
   bool success = false;
   //Check if args are ok first...
   QSqlQuery query;
   query.prepare("INSERT INTO people (name) VALUES (:name)");
   query.bindValue(":name", name);
   if(query.exec())
   {
       success = true;
   }
   else
   {
        qDebug() << "addPerson error:  "
                 << query.lastError();
   }
 
   return success;
}

//http://www.informit.com/articles/article.aspx?p=1405550

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    if (!createConnection())
        return 1;
    ...
    return app.exec();
}

//katecpp.wordpress.com/2015/08/28/sqlite-with-qt/
/* Keep in case revert back to this in future
Database::Database()
{

}
*/
