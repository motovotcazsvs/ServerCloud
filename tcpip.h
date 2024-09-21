#ifndef TCPIP_H
#define TCPIP_H

#include <QObject>

#include <QTcpServer>
#include <QTcpSocket>

class Tcpip : public QTcpServer
{
    Q_OBJECT

public:
    Tcpip();
    quint64 getDescriptor();

private:
    QTcpSocket *socket;
    quint16 port;
    QVector <QTcpSocket*> Sockets;
    quint64 descriptor;

signals:
    void newConnection();

public slots:
    void incomingConnection(qintptr socketDescriptor);

private slots:


};

#endif // TCPIP_H
