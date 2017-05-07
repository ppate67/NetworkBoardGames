#include "database.h"
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
using namespace std;

//Resources:
//http://doc.qt.io/qt-5/qsqldatabase.html for more database commands from QSQLDatabase
//http://blog.davidecoppola.com/2016/11/howto-embed-database-in-application-with-sqlite-and-qt/

int main1() {
//Connect to a Database
    const QString DRIVER("QSQLITE");

    if(QSqlDatabase::isDriverAvailable(DRIVER)) { //Check if SQLite driver is available

        QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);
        db.setDatabaseName(":memory:");     //Creates temprary database that exists until connection is closed

        if (!db.open()) {
           // qWarning() << "ERROR:" << db.lastError();
        }
    }

//Create a Table
    QSqlQuery query("CREATE TABLE player (id INTEGER PRIMARY KEY, name TEXT");
    if(!query.isActive()) {   //Check if table was created
        //qWarning() << "ERROR: " << query.lastError().text();
    }

//Insert Data
    if(!query.exec("INSERT INTO player(name) VALUES('Tom Cruz')"));
      //  qWarning() << "ERROR: " << query.lastError().text();

//Query Table
        /*
    query.prepare("SELECT name FROM people WHERE id = ?");
    query.addBindValue(mInputText->test().toInt());
    if(!query.exec())
       // qWarning << "ERROR: " << query.lastError().text();
    if(query.first())      //Retreive result of executed query
        mOutputText->setText(query.value(0).toString());
    else
       mOutputText->setText("Player not found");*/

}

//--------OLD CODE-------------------

//class DbManager
//{
//private:
//    QSqlDatabase m_db;
//public:
//    DbManager(const QString& path);
//    bool addPerson(const QString& name);
//};

//DbManager::DbManager(const QString& path)
//{
//   m_db = QSqlDatabase::addDatabase("QSQLITE");
//   m_db.setDatabaseName(path);
 
//   if (!m_db.open())
//   {
//      //qDebug() << "Error: connection with database fail";
//   }
//   else
//   {
//      //qDebug() << "Database: connection ok";
//   }
//}

//bool DbManager::addPerson(const QString& name) //Refers to new Player
//{
//   bool success = false;
//   //Check if args are ok first...
//   QSqlQuery query;
//   query.prepare("INSERT INTO people (name) VALUES (:name)");
//   query.bindValue(":name", name);
//   if(query.exec())
//   {
//       success = true;
//   }
//   else
//   {
//        //qDebug() << "addPerson error:  "
//                 //<< query.lastError();
//   }
 
//   return success;
//}

//http://www.informit.com/articles/article.aspx?p=1405550

//int main(int argc, char *argv[])
//{
//    QApplication app(argc, argv);
//    if (!createConnection())
//        return 1;
//    ...
//    return app.exec();
//}

//katecpp.wordpress.com/2015/08/28/sqlite-with-qt/
/* Keep in case revert back to this in future
Database::Database()
{

}
*/

