#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  ui->stop->setStyleSheet("#stop{ background: #cc0000; }");

  ui->start->setEnabled(true);
  ui->stop->setEnabled(false);
  ui->checkConnection->setEnabled(false);

  server = new ServerStuff(this);
   bl = new BusinessLogic(server);
  //connect(server, &ServerStuff::gotNewMessage,
  //        this, &MainWindow::gotNewMessage);
  connect(server->tcpServer, &QTcpServer::newConnection,
          this, &MainWindow::smbConnectedToServer);
  connect(server, &ServerStuff::smbDisconnected,
          this, &MainWindow::smbDisconnectedFromServer);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_start_clicked()
{
  ui->start->setStyleSheet("#start{ background: #009973; }");
  ui->start->setEnabled(false);
  ui->stop->setStyleSheet("#stop{ background: #212121; } #stop:hover{ background: #111111; }");
  ui->stop->setEnabled(true);
  ui->checkConnection->setStyleSheet("#checkConnection{ background: #212121; } #checkConnection:hover{ background: #111111; }");
  ui->checkConnection->setEnabled(true);

  if(!server->tcpServer->listen(QHostAddress::Any, 6547))
  {
    ui->textEdit->append(tr("<font color=\"red\"><b>Error!</b> The port is taken by some other service.</font>"));
    return;
  }
  connect(server->tcpServer, &QTcpServer::newConnection, server, &ServerStuff::newConnection);
  ui->textEdit->append(tr("<font color=\"#009973\"><b>Server started</b>, port is openned.</font>"));
}

void MainWindow::on_stop_clicked()
{
  ui->start->setStyleSheet("#start{ background: #212121; } #start:hover{ background: #111111; }");
  ui->start->setEnabled(true);
  ui->stop->setStyleSheet("#stop{ background: #cc0000; }");
  ui->stop->setEnabled(false);
  ui->checkConnection->setStyleSheet("#checkConnection{ background: #212121; } #checkConnection:hover{ background: #111111; }");
  ui->checkConnection->setEnabled(false);

  if(server->tcpServer->isListening())
  {
    disconnect(server->tcpServer, &QTcpServer::newConnection, server, &ServerStuff::newConnection);

    SendBroadcastShutdownToClients();

    server->tcpServer->close();
    ui->textEdit->append(tr("<font color=\"#cccc00\"><b>Server stopped</b>, port is closed.</font>"));
  }
  else
  {
    ui->textEdit->append(tr("<b>Error!</b> Server was not running"));
  }
}

void MainWindow::smbConnectedToServer()
{
  ui->textEdit->append(tr("Somebody has connected"));
}

void MainWindow::smbDisconnectedFromServer()
{
  ui->textEdit->append(tr("Somebody has disconnected"));
}

void MainWindow::gotNewMessage(QString msg)
{
  ui->textEdit->append(QString("New message: %1").arg(msg));
}

void MainWindow::gotPackage(QString user, int command)
{
  ui->textEdit->append(QString("User: %1\nCommand: %2").arg(user, command));
}

void MainWindow::SendBroadcastShutdownToClients()
{
  QList<QTcpSocket *> clients = server->getClients();
  for(int i = 0; i < clients.count(); i++)
  {
    //server->sendToClient(clients.at(i), "Connection closed");
    server->Send(clients.at(i), "Connection closed!");
  }
}

void MainWindow::on_checkConnection_clicked()
{
  if(server->tcpServer->isListening())
  {
    ui->textEdit->append(
                  QString("%1 %2")
                  .arg("Server is listening, number of connected clients:")
                  .arg(QString::number(server->getClients().count()))
                  );
  }
  else
  {
    ui->textEdit->append(
                  QString("%1 %2")
                  .arg("Server is not listening, number of connected clients:")
                  .arg(QString::number(server->getClients().count()))
                  );
  }
}
