#include "repository.h"

Repository::Repository()
{
  db = QSqlDatabase::addDatabase("QSQLITE");
  QString pathToDB = QDir::currentPath()+QString("/MessengerDB.db");
  db.setDatabaseName(pathToDB);
}

void Repository::Create_User(const QString &username, const QString &password)
{
  QString pathToDB = QDir::currentPath()+QString("/MessengerDB.db");
  qDebug() << pathToDB;
  db.open();

  QSqlQuery my_query;
  my_query.prepare("INSERT INTO Users (Username, Password)"
                               "VALUES (:username, :password);");
  my_query.bindValue(":username", username);
  my_query.bindValue(":password", password);

  my_query.exec();

  db.close();
}
