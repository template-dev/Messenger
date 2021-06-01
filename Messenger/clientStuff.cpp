#include "clientStuff.h"

#include <QMessageBox>

ClientStuff::ClientStuff(
        const QString hostAddress,
        int portNumber,
        QObject *parent
        ) : QObject(parent), m_nNextBlockSize(0)
{
    status = false;

    host = hostAddress;
    port = portNumber;

    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &ClientStuff::closeConnection);

    timeoutTimer = new QTimer();
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, this, &ClientStuff::connectionTimeout);
}

void ClientStuff::connect2host()
{
    timeoutTimer->start(3000);

    tcpSocket->connectToHost(host, port);
    connect(tcpSocket, &QTcpSocket::connected, this, &ClientStuff::connected);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &ClientStuff::readyRead);
}

void ClientStuff::connectionTimeout()
{
    //qDebug() << tcpSocket->state();
    if(tcpSocket->state() == QAbstractSocket::ConnectingState)
    {
        tcpSocket->abort();
        emit tcpSocket->error(QAbstractSocket::SocketTimeoutError);
    }
}

void ClientStuff::connected()
{
    status = true;
    emit statusChanged(status);
}

bool ClientStuff::getStatus() {return status;}

void ClientStuff::Send(QByteArray package)
{
  QByteArray arrBlock;
  QDataStream out(&arrBlock, QIODevice::WriteOnly);

  out << package.length() << package;

  tcpSocket->write(arrBlock);
}

void ClientStuff::readyRead()
{
  QDataStream in(tcpSocket);
   if(tcpSocket->bytesAvailable() < sizeof(int))
   {
     return;
   }
   int blockSize ;
   in >> blockSize;
   if(tcpSocket->bytesAvailable() < blockSize)
   {
     return;
   }
   QByteArray arrayBlock;
   in >> arrayBlock;
   emit hasReadSome(arrayBlock);
    /*QDataStream in(tcpSocket);
    for (;;)
    {
        if (!m_nNextBlockSize)
        {
            if (tcpSocket->bytesAvailable() < sizeof(quint16)) { break; }
            in >> m_nNextBlockSize;
        }

        if (tcpSocket->bytesAvailable() < m_nNextBlockSize) { break; }

        QString str; in >> str;

        if (str == "0")
        {
            str = "Connection closed";
            closeConnection();
        }

        emit hasReadSome(str);
        m_nNextBlockSize = 0;
    }*/
}

/*void ClientStuff::gotDisconnection()
{
    status = false;
    emit statusChanged(status);
}*/

void ClientStuff::closeConnection()
{
    timeoutTimer->stop();

    //qDebug() << tcpSocket->state();
    disconnect(tcpSocket, &QTcpSocket::connected, 0, 0);
    disconnect(tcpSocket, &QTcpSocket::readyRead, 0, 0);

    bool shouldEmit = false;
    switch (tcpSocket->state())
    {
        case 0:
            tcpSocket->disconnectFromHost();
            shouldEmit = true;
            break;
        case 2:
            tcpSocket->abort();
            shouldEmit = true;
            break;
        default:
            tcpSocket->abort();
    }

    if (shouldEmit)
    {
        status = false;
        emit statusChanged(status);
    }
}

/*void ClientStuff::SendCodeAndLoginToServer(const QString &login, const QString &command)
{
  QByteArray arrBlock;
  QDataStream out(&arrBlock, QIODevice::WriteOnly);
  //out.setVersion(QDataStream::Qt_5_10);
  out << quint16(0) << login;
  out << quint16(1) << command;

  out.device()->seek(0);
  out << quint16(arrBlock.size() - sizeof(quint16));

  tcpSocket->write(arrBlock);
}*/
