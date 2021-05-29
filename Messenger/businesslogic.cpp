#include "businesslogic.h"

BusinessLogic::BusinessLogic(ClientStuff *client,QObject *parent) : QObject(parent),client(client)
{
   connect(client,&ClientStuff::hasReadSome,this,&BusinessLogic::IncomingPacket);
}

void BusinessLogic::SetPackageForRegistration(QList<QString> datas)
{
  for(const auto& d : datas)
  {
    this->datas << d;
  }
}

void BusinessLogic::CreateDataEncryptJSONFile()
{
  QDir().mkdir("Users");

  QFile saveFile("Users/" + this->datas.at(0) + ".json");
  if (!saveFile.open(QIODevice::WriteOnly))
  {
    qWarning("Couldn't open save file.");
  }

  QJsonObject json;

  json["login"] = this->datas.at(0);
  json["password"] = this->datas.at(2);
  json["mail"] = this->datas.at(1);
  json["command"] = "new_user";

  QJsonDocument saveDoc(json);
  saveFile.write(saveDoc.toJson());
  saveFile.close();
}

void BusinessLogic::IncomingPacket(QString msg)
{
  //1. deseriaize from JSON
  //2. read answer (code and message...)
  //3. If need show to UI:
  emit HasData(msg);

}

void BusinessLogic::CreateNewUser(QString username, QString password)
{
   //1. Create parameters map json["mmmm"] for command new_user
   //2. Serialize to JSON into dto
   QString dto; //...
   client->Send(dto);

}

void BusinessLogic::LoginUser(QString username, QString password)
{
  //1. Create parameters map json["mmmm"] for command login_user
  //2. Serialize to JSON into dto
  QString dto; //...
  client->Send(dto);
}

void BusinessLogic::SendMessage(QString to, QString body)
{
  //1. Create parameters map json["mmmm"] for command send_msg
  //2. Serialize to JSON into dto
  QString dto; //...
  client->Send(dto);
}
