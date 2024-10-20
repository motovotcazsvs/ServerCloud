#include "client.h"
#include <QDebug>
#include <QDataStream>

#include "settingsfile.h"

Client::Client(QObject *parent, QTcpSocket* socket, SettingsFile* settingsfile) : QObject(parent), socket(socket)
{
    state = stateWaiting;
    socket_descriptor = socket->socketDescriptor();
    authorization = new Authorization(this, this, socket, settingsfile);



    qDebug() << "socket->socketDescriptor()" << socket->socketDescriptor();

}

Client::~Client()
{
    delete synchronization;
}

void Client::authorizationSuccessfull()
{
    delete authorization;
    synchronization = new Synchronization(this, socket, folder_id);

}

void Client::setID(quint64 id)
{
    ID = id;
}

void Client::setFolderID(QString folder_name)
{
    folder_id = folder_name;
}







