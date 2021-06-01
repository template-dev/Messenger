#include "authandregistration.h"
#include "businesslogic.h"

#include <QMessageBox>

BusinessLogic::BusinessLogic(ClientStuff *client, QObject *parent) : QObject(parent), client(client)
{
  connect(client,&ClientStuff::hasReadSome,this,&BusinessLogic::IncomingPacket);
}

void BusinessLogic::CreateNewUser(const QString &username, const QString &password)
{
  QJsonObject json;

  json["login"] = username;
  json["password"] = password;
  json["cmd"] = 0;

  QJsonDocument saveDoc(json);

  client->Send(saveDoc.toJson());
  //1. Create parameters map json["mmmm"] for command new_user
  //2. Serialize to JSON into dto
  //QString dto; //...
  //client->Send(dto);
}

void BusinessLogic::LoginUser(const QString &username, const QString &password)
{

}

void BusinessLogic::SendMessage(const QString &to, const QString &body)
{
  //1. Create parameters map json["mmmm"] for command send_msg
  //2. Serialize to JSON into dto
  //QString dto; //...
  //client->Send(dto);
}

void BusinessLogic::IncomingPacket(QByteArray msg)
{
  QByteArray arrayPackage = msg;//decrypt arrayBlock to QByteArray packageArray

  QJsonDocument doc = QJsonDocument::fromJson(arrayPackage);
  QJsonObject package = doc.object();
  int code = package["code"].toInt();
  switch(code)
  {
  case 200:
  {
    qDebug() << "Code: " << code;
  }
  break;
  }

  /*authAndRegistration auth;

  if(msg == "200")
  {
    auth.SetCode(200);
  }
  if(msg == "404")
  {
    auth.SetCode(404);
  }
  if(msg == "403")
  {
    auth.SetCode(403);
  }
  if(msg == "500")
  {
    auth.SetCode(500);
  }*/
}

void BusinessLogic::PollMessages()
{
   //Request new meaages for your user
  QJsonObject json;



  json["cmd"] = 12;
  QJsonDocument saveDoc(json);

  //client->Send(saveDoc.toJson());

  qDebug() << "PollMessage";
}

