#ifndef REQUEST_H
#define REQUEST_H

#include <QString>
#include <QMap>

class Request
{
public:
  Request();
  void GetCMDAndParams();

private:
  QString cmd;
  QMap<QString, QString> params;
};

#endif // REQUEST_H
