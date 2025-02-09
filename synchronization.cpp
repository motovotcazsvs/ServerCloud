#include "synchronization.h"

#include <QDataStream>
#include "folder.h"
#include "file.h"

Synchronization::Synchronization(QObject* parent, QTcpSocket* sock, QString path_id) : QObject(parent), socket(sock), path_id(path_id)
{
    qDebug() << "Synchronization::Synchronization";
    current_path = path_id;
    QObject::connect(socket, &QTcpSocket::readyRead, this, &Synchronization::receive);
    size_info = 0;
    state = Waiting;
}

Synchronization::~Synchronization()
{
    qDebug() << "Synchronization();";

    delete socket;

    // Видаляємо всі папки зі списку
    for(Folder* folder : folders) {
        delete folder;  // Видаляємо кожен об'єкт Folder
    }
    folders.clear();  // Очищаємо список після видалення

    delete file;  //add file = nullptr;
}

void Synchronization::receive()
{
    qDebug() << "receive() open";

    socket = (QTcpSocket*)sender();
    qDebug() << "socket->bytesAvailable()" << socket->bytesAvailable();
    if(state == Waiting){ //якщо ще не прочитали інформацію
        qDebug() << "state Waiting";
        QDataStream in(socket);
        in.setVersion(QDataStream::Qt_5_7);

        if(size_info == 0){ //якщо інфи ще не було
            qDebug() << "size_info == 0";
            if(socket->bytesAvailable() < 2){ //якщо інфи менше двох байт
                qDebug() << "bytesAvailable() < 2";
                qDebug() << "receive() close1";
                return; //то вийти
            }
            in >> size_info; //розмір інформації
            //qDebug() << "size_info" << size_info;
        }

        qDebug() << "size_info" << size_info;
        if (socket->bytesAvailable() < size_info){ //якщо доступно байт менше розміру інфо
            qDebug() << "bytesAvailable() < size_info" << socket->bytesAvailable();
            qDebug() << "receive() close2";
            return;
        }

        QString type;
        in >> type;
        qDebug() << "type:" << type;
        if(type == "START_FOLDER"){
            Folder* newFolder = new Folder(this, in);
            folders.append(newFolder);
            size_info = 0;
            if(socket->bytesAvailable()){
                qDebug() << "if(bytesAvailable())";
                receive();
            }
            qDebug() << "receive() close3";
            return;
        }
        else if(type == "END_FOLDER"){
            Folder* lastFolder = folders.last();
            lastFolder->endFolder(in);
            delete lastFolder;
            folders.takeLast();
            size_info = 0;
            state = Waiting;
            if(socket->bytesAvailable()){
                qDebug() << "if(bytesAvailable())";
                receive();
            }

            qDebug() << "receive() close4";
            return;

        }
        else if(type == "FILE"){
            file = new File(this, in);
            size_info = 0;
            state = ReadingFile;

            //перевіряєм чи є вже дані файла, щоб їх обробити
            qint64 available = socket->bytesAvailable();
            qDebug() << "availableData" << available;
            if(available == 0){
                qDebug() << "receive() close5";
                return;
            }

        }
    }


    file->copyFile();

    if(state == Redundant){
        delete file;
        state = ReadingInfo;
        //receive(); //викликаємо слот знову, щоб обробити зайві дані
    }

    if(socket->bytesAvailable()){
        qDebug() << "socket->bytesAvailable()finish";
        receive();
    }
    qDebug() << "receive() close6";

}

quint64 Synchronization::getBytesAvailable()
{
    quint64 available = socket->bytesAvailable();

    return available;
}

void Synchronization::getBytes(QByteArray& arr, quint64 size)
{
   arr = socket->read(size);
}

QString Synchronization::getCurrentPath()
{
    return current_path;
}

void Synchronization::setCurrentPath(QString path)
{
    current_path = path;
}

void Synchronization::setState(State current_state)
{
    state = current_state;
}

Synchronization::State Synchronization::getState()
{
    return state;
}
