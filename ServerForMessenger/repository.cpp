#include "repository.h"

Repository::Repository()
{
  db = QSqlDatabase::addDatabase("QSQLITE");
  QString pathToDB = QDir::currentPath()+QString("/MessengerDB.db");
  db.setDatabaseName(pathToDB);
}

void Repository::Create_User(const QString &username, const QString &password)
{
  db.open();

  QSqlQuery my_query;
  my_query.prepare("INSERT INTO Users (Username, Password)"
                               "VALUES (:username, :password);");
  my_query.bindValue(":username", username);
  my_query.bindValue(":password", password);

  my_query.exec();

  db.close();
}

void Repository::Login_User(const QString &username, const QString &password, int& code)
{
  db.open();

  QSqlQuery my_query;
  my_query.prepare("SELECT Username, Password FROM Users"
                               "WHERE Username = :username and Password = :password;");
  my_query.bindValue(":username", username);
  my_query.bindValue(":password", password);

  if((my_query.value(0) != "") && (my_query.value(1) != ""))
    code = 1;

  my_query.exec();

  db.close();
}
