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
  void CreateUser(const QString& username, const QString& password);
  void NewMsg(QString msg);
  void LoginUser(const QString& username, const QString& password);
  void FindUser(const QString& username);

signals:
  void OnCreateUser(const QString& username, const QString& password);
  void OnNewMessage(QString msg);
  void OnLoginUser(const QString& username, const QString& password);
  void OnFindUser(const QString& username);

private:
  ServerStuff *server;

private slots:
  void gotMessageHandler(QTcpSocket* socket, QByteArray);

};

#endif // BUSINESSLOGIC_H
