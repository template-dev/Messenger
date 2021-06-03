#include "serverStuff.h"

ServerStuff::ServerStuff(QObject *pwgt) : QObject(pwgt), m_nNextBlockSize(0)
{
    tcpServer = new QTcpServer(this);
}

QList<QTcpSocket *> ServerStuff::getClients()
{
    return clients;
}

void ServerStuff::newConnection()
{
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();

    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
    connect(clientSocket, &QTcpSocket::readyRead, this, &ServerStuff::readClient);
    connect(clientSocket, &QTcpSocket::disconnected, this, &ServerStuff::gotDisconnection);

    clients << clientSocket;
    // Сделать вызов сигнала и передать ему код нового соединения
    //Send(clientSocket, "Reply: connection established");
}

void ServerStuff::readClient()
{
  QTcpSocket *clientSocket = (QTcpSocket*)sender();
  QDataStream in(clientSocket);
  if(clientSocket->bytesAvailable() < sizeof(int))
  {
    return;
  }
  int blockSize ;
  in >> blockSize;
  if(clientSocket->bytesAvailable() < blockSize)
  {
    return;
  }
  QByteArray arrayBlock;
  in >> arrayBlock;
  emit gotPackage(clientSocket, arrayBlock);
}

void ServerStuff::gotDisconnection()
{
    clients.removeAt(clients.indexOf((QTcpSocket*)sender()));
    emit smbDisconnected();
}

void ServerStuff::Send(QTcpSocket* socket, QByteArray package)
{
  QByteArray arrBlock;
  QDataStream out(&arrBlock, QIODevice::WriteOnly);

  out << package.length() << package;

  socket->write(arrBlock);
}
