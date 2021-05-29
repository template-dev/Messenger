#include "businesslogic.h"

BusinessLogic::BusinessLogic(ServerStuff *server,QObject *parent) : QObject(parent), server(server)
{
  connect(server,&ServerStuff::gotNewMesssage,this,&BusinessLogic::gotMessageHandler);
}

void BusinessLogic::gotMessageHandler(QString msg)
{
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
