#ifndef BUSINESSLOGIC_H
#define BUSINESSLOGIC_H

#include "serverStuff.h"

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>

class BusinessLogic : public QObject
{
  Q_OBJECT
public:
  explicit BusinessLogic(ServerStuff *server, QObject *parent = nullptr);

signals:
  /*void OnCreateUser(const QString& username, const QString& password);
  void OnNewMessage(QString msg);
  void OnLoginUser(const QString& username, const QString& password);*/

private:
  ServerStuff *server;

private slots:
  void gotMessageHandler(QString msg, int code);

};

#endif // BUSINESSLOGIC_H
