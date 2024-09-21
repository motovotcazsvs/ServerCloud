#include "Tcpip.h"


Tcpip::Tcpip()
{
    port = 44;
    descriptor = 0;

    if(this->listen(QHostAddress::Any, port)){
        qDebug() << "start server";
    }
    else qDebug() << "error";
}

void Tcpip::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);

    if (!socket->isValid()) {
            qDebug() << "Invalid socket. Connection failed.";
            socket->deleteLater();
            return;
        }

    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    Sockets.push_back(socket);
    descriptor = socketDescriptor;
    emit newConnection();
    qDebug() << "client connected" << socketDescriptor;
}

quint64 Tcpip::getDescriptor()
{
    return descriptor;
}
