#include "businesslogic.h"

#include <QMessageBox>

BusinessLogic::BusinessLogic(ServerStuff *server,QObject *parent) : QObject(parent), server(server)
{
  connect(server,&ServerStuff::gotPackage,this,&BusinessLogic::gotMessageHandler);
}

void BusinessLogic::gotMessageHandler(QString username, int code)
{
  QFile file_obj("Users/" + username + ".json");
  if(!file_obj.open(QIODevice::ReadOnly)){
      qDebug()<<"Failed to open "<< username << ".json";
  }

  QTextStream file_text(&file_obj);
  QString json_string;
  json_string = file_text.readAll();
  file_obj.close();
  QByteArray json_bytes = json_string.toLocal8Bit();

  auto json_doc = QJsonDocument::fromJson(json_bytes);

  if(json_doc.isNull()){
      qDebug()<<"Failed to create JSON doc.";
  }
  if(!json_doc.isObject()){
      qDebug()<<"JSON is not an object.";
  }

  QJsonObject json_obj = json_doc.object();

  if(json_obj.isEmpty()){
      qDebug()<<"JSON object is empty.";
  }

  QVariantMap json_map = json_obj.toVariantMap();

  qDebug() << json_map["login"].toString();
  qDebug() << json_map["password"].toString();

  QString login = json_map["login"].toString();
  QString password = json_map["password"].toString();

  QMessageBox msg;

  switch(code)
  {
  case 0:
    msg.setText("login: " + login + "\n password: " + password);
    msg.exec();
    break;
  case 1:
    /* Read user datas from database */
    break;
  case 2:
    /* Get user datas from database */
    break;
  default:
    /* Failure code! */
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
