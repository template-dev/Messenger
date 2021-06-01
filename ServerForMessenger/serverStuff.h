#ifndef SERVERSTUFF_H
#define SERVERSTUFF_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QList>

class ServerStuff : public QObject
{
    Q_OBJECT

public:
    ServerStuff(QObject *pwgt);
    ServerStuff();
    QTcpServer *tcpServer;
    QList<QTcpSocket *> getClients();

    void SetCode(int code) { this->code = code; }
    int GetCode() { return code; }

public slots:
    virtual void newConnection();
    void readClient();
    void gotDisconnection();
    void Send(QTcpSocket *socket, QByteArray package);


signals:
    void gotPackage(QTcpSocket*, QByteArray);
    void gotNewMessage(QString msg);
    void smbDisconnected();
    void test();

private:
    quint16 m_nNextBlockSize;
    QList<QTcpSocket*> clients;
    int code = 0;
};

#endif // SERVERSTUFF_H
