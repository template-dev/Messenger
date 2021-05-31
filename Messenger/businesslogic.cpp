#include "authandregistration.h"
#include "businesslogic.h"

#include <QMessageBox>

BusinessLogic::BusinessLogic(ClientStuff *client, QObject *parent) : QObject(parent), client(client)
{
  connect(client,&ClientStuff::hasReadSome,this,&BusinessLogic::IncomingPacket);
}

void BusinessLogic::CreateNewUser(const QString &username, const QString &password)
{
  QDir().mkdir("Users");

  QFile saveFile("Users/" + username + ".json");
  if (!saveFile.open(QIODevice::WriteOnly))
  {
    qWarning("Couldn't open save file.");
  }

  QJsonObject json;

  json["login"] = username;
  json["password"] = password;

  QJsonDocument saveDoc(json);
  saveFile.write(saveDoc.toJson());
  saveFile.close();

  client->Send(username, "new_user");
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

void BusinessLogic::IncomingPacket(QString msg)
{
  authAndRegistration auth;

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
  }
}

