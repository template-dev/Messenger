#ifndef BUSINESSLOGIC_H
#define BUSINESSLOGIC_H

#include <QString>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDir>
#include <QDataStream>
#include <QTcpSocket>

#include "clientStuff.h"

class BusinessLogic : public QObject
{
  Q_OBJECT
public:
  BusinessLogic(ClientStuff* client, QObject *parent = nullptr);
  BusinessLogic(const QString& login) : login(login) {}
  void SetPackageForRegistration(QList<QString> datas);
  void CreateDataEncryptJSONFile();

  QString GetLogin() { return this->login; }
signals:
  void HasData(QString message);


private:
  QList<QString> datas;
  QString login;
  ClientStuff *client;
public slots:
  void IncomingPacket(QString msg);


public:
   void CreateNewUser(QString username,QString password);
   void LoginUser(QString username, QString password);
   void SendMessage(QString to, QString body);
};

#endif // BUSINESSLOGIC_H
