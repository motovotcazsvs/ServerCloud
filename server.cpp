#include <QDebug>

#include "server.h"
#include "settingsfile.h"

Server::Server()
{
    settingsfile = nullptr;

    if(this->listen(QHostAddress::Any, 44)){
        qDebug() << "start server";
        settingsfile = new SettingsFile("settingsfile.json");
    }
    else qDebug() << "error";


}

Server::~Server()
{
    if(settingsfile != nullptr) delete settingsfile;
}

//підключення клієнта
void Server::incomingConnection(qintptr socket_descriptor)
{
    socket = new QTcpSocket(this);
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
    Client* newClient = new Client(this, socket, settingsfile);
    clients.insert(descriptor, newClient);
    qDebug() << "client connected" << descriptor;
}

void Server::deleteClient()
{
    //delete client;//нада дороблять
}
