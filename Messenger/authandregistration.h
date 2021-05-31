#ifndef AUTHANDREGISTRATION_H
#define AUTHANDREGISTRATION_H

#include "clientStuff.h"
#include "businesslogic.h"

#include <QMainWindow>
#include <QDesktopWidget>
#include <QRect>
#include <QMouseEvent>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTcpSocket>

namespace Ui {
class authAndRegistration;
}

class authAndRegistration : public QMainWindow
{
  Q_OBJECT

public:
  explicit authAndRegistration(QWidget *parent = nullptr);
  ~authAndRegistration();

  bool eventFilter(QObject *object, QEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

  void SetCode(int Code) { this->Code = Code; }
  int GetCode() { return this->Code; }

  QPoint current;
  bool pressed;

public slots:
  void setStatus(bool newStatus);
  void receivedSomething(QString msg);
  void gotError(QAbstractSocket::SocketError err);

private slots:
  void on_pushButton_2_clicked();

  void on_signUpBtn_clicked();

  void on_pushButton_clicked();

  void on_signInBtn_clicked();

  void on_loginBtn_clicked();

  void on_closeApp_clicked();

  void on_label_8_linkActivated(const QString &link);

  void on_loginBtn_2_clicked();

  void HasDataHandler(QString message);

private:
  Ui::authAndRegistration *ui;
  QJsonObject json;
  QString login;
  QString password;
  ClientStuff *client;
  BusinessLogic *bl;
  int Code = 0;

};

#endif // AUTHANDREGISTRATION_H
