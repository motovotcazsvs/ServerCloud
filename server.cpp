#include <QDebug>

#include "server.h"
#include "settingsfile.h"

Server::Server()
{
    connect = new Connect();
    QObject::connect(connect, &Connect::newConnection, this, &Server::createNewClient);
}

void Server::createNewClient()
{
    Client* newClient = new Client(connect);
    clients.insert(connect->getId(), newClient);


}
