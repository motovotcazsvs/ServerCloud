#include "file.h"

#include <QDebug>

#include "synchronization.h"

File::File(Synchronization* synchronization, QDataStream& in) : synchronization(synchronization)
{
    in >> name >> size;
    current_size = 0;
    path = synchronization->getCurrentPath();
    createOrReplace();


}

File::~File()
{
    delete file;
    qDebug() << "~File()";
}

void File::copyFile()
{
    qDebug() << "copyFile() open";
    qDebug() << "get state" << synchronization->getState();

    quint64 available = synchronization->getBytesAvailable();
    quint64 subtract = size - current_size;
    if(size < current_size) subtract = 0;
    quint64 bytesToRead = qMin(available, subtract);
    QByteArray data_block_file;
    synchronization->getBytes(data_block_file, bytesToRead);
    qDebug() << "file->write(data_block_file)1";
    file->write(data_block_file);
    qDebug() << "file->write(data_block_file)2";
    current_size += data_block_file.size();

    if(current_size >= size) {
        qDebug() << "current_size >= size" << current_size << size;
        qDebug() << "The file is received completely";
        file->close();
        qDebug() << "file->close()";
        synchronization->setState(Synchronization::Waiting);
    }

    if(available > bytesToRead){
        qDebug() << "available > bytesToRead" << available << bytesToRead;
        synchronization->setState(Synchronization::Waiting);
        //synchronization->receive();

    }

    qDebug() << "copyFile() close";

}

void File::createOrReplace()
{
    qDebug() << "createOrReplace() open";

    file = new QFile(path + "/" + name);

    // Перевірка, чи існує файл
    if(file->exists()){
        qDebug() << "The file exists, replace:" << file->fileName();
        file->remove(); // Видалити існуючий файл
    }else{
        qDebug() << "The file does not exist, create it:" << file->fileName();
    }

    // Відкриваємо файл для запису
    if(!file->open(QIODevice::WriteOnly)) {
        qWarning() << "no open for write" << file->fileName();
    }

    qDebug() << "createOrReplace() close";

}
