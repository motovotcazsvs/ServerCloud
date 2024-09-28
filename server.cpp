#include <QDebug>

#include "server.h"
#include "settingsfile.h"

Server::Server()
{
    if(this->listen(QHostAddress::Any, 44)){
        qDebug() << "start server";
    }
    else qDebug() << "error";
}

//підключення клієнта
void Server::incomingConnection(qintptr socket_descriptor)
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socket_descriptor);

    if (!socket->isValid()) {
            qDebug() << "Invalid socket. Connection failed.";
            socket->deleteLater();
            return;
        }

    QObject::connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    QObject::connect(socket, &QTcpSocket::disconnected, this, &Server::deleteClient);

    createNewClient(socket_descriptor);
}


void Server::createNewClient(qintptr descriptor)
{
    Client* newClient = new Client(this, socket);
    clients.insert(descriptor, newClient);
    qDebug() << "client connected" << descriptor;
}

void Server::deleteClient()
{
    //delete client;
}
