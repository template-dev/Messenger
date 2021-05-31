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
    /*QDataStream in(clientSocket);
    for (;;)
    {
        if (!m_nNextBlockSize) {
                if (clientSocket->bytesAvailable() < sizeof(quint16)) { break; }
            in >> m_nNextBlockSize;
        }

        if (clientSocket->bytesAvailable() < m_nNextBlockSize) { break; }
        QString username;
        QString command;
        in >> username;
        in >> command;*/

        /*if(command == "new_user") { SetCode(0); }
        else if(command == "login_user") { SetCode(1); }
        else if(command == "get_user") { SetCode(2); }*/

        /*emit gotNewMessage(username);
        //emit gotPackage(username, GetCode());

        m_nNextBlockSize = 0;

        if (Send(clientSocket, QString("Reply: received [%1]").arg(username)) == -1)
        {
            qDebug() << "Some error occured";
        }
    //}*/
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
