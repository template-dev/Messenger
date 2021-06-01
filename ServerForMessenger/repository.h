#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include "QVariant"
#include <QDir>
#include <QDebug>

class Repository
{
public:
  Repository();
  void Create_User(const QString& username, const QString& password);

private:
  QSqlDatabase db;
};

#endif // REPOSITORY_H
