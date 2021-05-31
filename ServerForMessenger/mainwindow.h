#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include "serverStuff.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_start_clicked();

  void on_stop_clicked();
  void smbConnectedToServer();
  void smbDisconnectedFromServer();
  void gotNewMessage(QString msg);
  void gotPackage(QString user, int command);

  void on_checkConnection_clicked();

private:
  Ui::MainWindow *ui;
  ServerStuff *server = nullptr;
  void SendBroadcastShutdownToClients();

};
#endif // MAINWINDOW_H
