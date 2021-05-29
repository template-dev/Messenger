#ifndef SERIALIZETOJSON_H
#define SERIALIZETOJSON_H

#include <QObject>

class SerializeToJSON
{
  Q_PROPERTY(QString name MEMBER name USER true)
  Q_PROPERTY(int age MEMBER age USER true)
  Q_PROPERTY(QString email MEMBER email USER true)
  Q_PROPERTY(std::vector<QString> phone MEMBER phone USER true)
  Q_PROPERTY(bool vacation MEMBER vacation USER true)

public:
  SerializeToJSON();
  QString login;
  QString email;
  QString password;
};

#endif // SERIALIZETOJSON_H
