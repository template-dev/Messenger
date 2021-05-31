#ifndef BUSINESSLOGIC_H
#define BUSINESSLOGIC_H

#include "clientStuff.h"

#include <QObject>
#include <QString>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDir>
#include <QDataStream>
#include <QTcpSocket>

class BusinessLogic : public QObject
{
  Q_OBJECT
public:
  explicit BusinessLogic(ClientStuff* client, QObject *parent = nullptr);
  void CreateNewUser(const QString& username, const QString& password);
  void LoginUser(const QString& username, const QString& password);
  void SendMessage(const QString& to, const QString& body);

signals:


private:
  QString login;
  ClientStuff *client;

public slots:
  void IncomingPacket(QByteArray msg);
};

#endif // BUSINESSLOGIC_H
