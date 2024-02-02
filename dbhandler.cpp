#include "dbhandler.h"


DbHandler::DbHandler(QString dbPath, QString dbConnectionName)
{  
    try
    {

        mydb=QSqlDatabase::addDatabase(dbConnectionName);
        mydb.setDatabaseName(dbPath);

    } catch (...)
    {
        msgBox.setText(FAILED_MESSAGE_DATABASE_CONNECTION);
        msgBox.exec();
    }
}

 bool DbHandler:: open()
 {
     try
     {
         if(mydb.open())
         {
             return true;
         }
         else
         {
             return false;
         }


     } catch (...)
     {
         msgBox.setText(FAILED_MESSAGE_DATABASE_OPENING);
         msgBox.exec();
     }

 }

 void DbHandler:: close()
 {
     try
     {
         mydb.close();

     } catch (...)
     {
         msgBox.setText(FAILED_MESSAGE_DATABASE_CLOSING);
         msgBox.exec();
     }
 }
