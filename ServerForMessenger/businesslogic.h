#ifndef BUSINESSLOGIC_H
#define BUSINESSLOGIC_H

#include "serverStuff.h"

#include <QObject>

class BusinessLogic : public QObject
{
  Q_OBJECT
public:
  explicit BusinessLogic(ServerStuff *server,QObject *parent = nullptr);

signals:
  void onCreateUser(QString user);
  void OnNewMessage(QString msg);
  //...
  void OnLoginUser(QString user);

private:
  ServerStuff *server;
private slots:
  void gotMessageHandler(QString msg);

};

#endif // BUSINESSLOGIC_H
