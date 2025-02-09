#include "client.h"
#include <QDebug>
#include <QDataStream>

#include "settingsfile.h"

Client::Client(QObject *parent, QTcpSocket* socket, SettingsFile* settingsfile) : QObject(parent), socket(socket)
{
    state = stateWaiting;
    socket_descriptor = socket->socketDescriptor();
    authorization = new Authorization(this, socket, settingsfile);
    QObject::connect(authorization, &Authorization::authorizationSuccessfull, this, &Client::authorizationClient);




    qDebug() << "socket->socketDescriptor()" << socket->socketDescriptor();

}

Client::~Client()
{
    delete synchronization;
}

void Client::authorizationClient()
{
    qDebug() << "Client::authorizationSuccessfull()";
    ID = authorization->getID();
    folder_id = authorization->getFolderID();
    authorization->deleteLater();
    authorization = nullptr;
    //qDebug() << "Client::authorizationSuccessfull dohode";
    synchronization = new Synchronization(this, socket, folder_id);
    //qDebug() << "Client::authorizationSuccessfull dohode2";
}

void Client::setID(quint64 id)
{
    ID = id;
}

void Client::setFolderID(QString folder_name)
{
    folder_id = folder_name;
}







