#include "businesslogic.h"

#include <QMessageBox>

BusinessLogic::BusinessLogic(ServerStuff *server,QObject *parent) : QObject(parent), server(server)
{
  connect(server,&ServerStuff::gotPackage,this,&BusinessLogic::gotMessageHandler);
}

void BusinessLogic::CreateUser(const QString &username, const QString &password)
{
  // Create user in database
  //server->Send(socket, "200");
}

void BusinessLogic::NewMsg(QString msg)
{

}

void BusinessLogic::LoginUser(const QString &username, const QString &password)
{
  // Check user in database
  // Take him datas
  // Send datas to client
  //server->Send(socket, code);
}

void BusinessLogic::FindUser(const QString &username)
{
  //server->Send(socket, username);
}

void BusinessLogic::gotMessageHandler(QTcpSocket* socket, QByteArray arrayBlock)
{
  qDebug() << arrayBlock;

  QByteArray arrayPackage = arrayBlock;//decrypt arrayBlock to QByteArray packageArray

  QJsonDocument doc = QJsonDocument::fromJson(arrayPackage);
  QJsonObject package = doc.object();
  int code = package["cmd"].toInt();
  switch(code)
  {
  case 0:
  {
    QMessageBox msg;
    QString login = package["login"].toString();
    QString password = package["password"].toString();
    msg.setText("login: " + login + "\n password: " + password);
    msg.exec();

    CreateUser(login, password);
    QJsonObject json;

    json["code"] = 200;

    QJsonDocument saveDoc(json);
    QByteArray rawPacket = saveDoc.toJson();

    QByteArray chiperPackage = rawPacket;//crypt rawPacket to QByteArray
    server->Send(socket, chiperPackage);
  }
  break;
  }

  //1. Deserialize from JSON
  //2. Read json["command"]
  /*
   *  switch(command)
   *  {
   *   case new_user:
   *    ...
   *    break;
   *    case login_user:
   *    ...
   *    break
   *    ...
   *
   *  }
*/
  //If need show to UI:
  // emit onXXX(msg)
  //3. If need :
  //Create dto as QString
  //Serialize into JSON
  //and send to client:
  //QString dto;
  //server->Send(dto);
}
