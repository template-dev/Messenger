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
    qint64 Send(QTcpSocket *socket, const QString &str);


signals:
    void gotPackage(QString username, int code);
    void gotNewMessage(QString msg);
    void smbDisconnected();

private:
    quint16 m_nNextBlockSize;
    QList<QTcpSocket*> clients;
    int code = 0;
};

#endif // SERVERSTUFF_H
