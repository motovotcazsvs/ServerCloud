#include "client.h"
#include <QDebug>
#include <QDataStream>

Client::Client(QObject *parent, QTcpSocket* sock) : QObject(parent), socket(sock)
{
    state = stateWaiting;

    //synchronization = new Synchronization(this, socket);

    qDebug() << "socket->socketDescriptor()" << socket->socketDescriptor();

    connect(socket, &QTcpSocket::readyRead, this, &Client::slotReadyRead);
}

Client::~Client()
{
    delete synchronization;
}

void Client::slotReadyRead()
{
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_7);
    quint16 size;
    QString info;
    in >> size;
    in >> info;
    qDebug() << socket->socketDescriptor() << "info" << info;

}



