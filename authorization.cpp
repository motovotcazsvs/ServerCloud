#include "authorization.h"

#include <QDataStream>

#include "settingsfile.h"
#include "client.h"

Authorization::Authorization(QObject* parent, Client* client, QTcpSocket* socket, SettingsFile* settingsfile) : QObject(parent), client(client), socket(socket), settingsfile(settingsfile)
{
    QObject::connect(socket, &QTcpSocket::readyRead, this, &Authorization::authorizationClient);
    id = 0;

}

Authorization::~Authorization()
{

}

void Authorization::authorizationClient()
{
    qDebug() << "authorizationClient()";
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_8);
    quint16 size;
    QString type;

    if(socket->bytesAvailable() < 2) return;
    in >> size;
    if(socket->bytesAvailable() < size) return;

    in >> type;
    qDebug() << socket->socketDescriptor() << "Type Authorization: " << type;
    if(type == "ID"){
        in >> id;
        qDebug() << "ID" << id;
        if(id == 0){
            qDebug() << "new client";
            id = settingsfile->newID();
            sendID();
            return;
        }
        folder_id = settingsfile->getFolderID(id);
        if(folder_id.isEmpty() == false){
            sendOK();
        }
        else return;

        client->setID(id);
        client->setFolderID(folder_id);
        client->authorizationSuccessfull();

    }
    if(socket->bytesAvailable()){
        qDebug() << "data available";
        authorizationClient();
    }
}

void Authorization::sendID()
{
    qDebug() << "sendID()" << id;
    QByteArray arr;
    QDataStream out(&arr, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_8);
    out << quint16(0) << QString("ID") << id;//резервуєм два байта на розмір блоку(записуючи туди нулі) та поміщаєм дані в масив
    out.device()->seek(0);//переміщаємо вказівник на начало в масиві, тобто на зарезервовані два байта - розмір блоку
    out << quint16(arr.size() - sizeof(quint16));//та записуєм туди фактичний розмір даних(віднявши від масива перші два байти)
    qDebug() << arr;
    socket->write(arr);
    socket->waitForBytesWritten();

}

void Authorization::sendOK()
{
    qDebug() << "sendOK()";
    QByteArray arr;
    QDataStream out(&arr, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_8);
    out << quint16(0) << QString("OK");//резервуєм два байта на розмір блоку(записуючи туди нулі) та поміщаєм дані в масив
    out.device()->seek(0);//переміщаємо вказівник на начало в масиві, тобто на зарезервовані два байта - розмір блоку
    out << quint16(arr.size() - sizeof(quint16));//та записуєм туди фактичний розмір даних(віднявши від масива перші два байти)
    qDebug() << arr;
    socket->write(arr);
    socket->waitForBytesWritten();

}

