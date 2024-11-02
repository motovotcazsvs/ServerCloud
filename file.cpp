#include "file.h"

#include <QDebug>

#include "synchronization.h"

File::File(Synchronization* synchronization, QDataStream& in) : synchronization(synchronization)
{
    in >> this->name >> this->size;
    this->current_size = 0;
    this->path = synchronization->getCurrentPath();
    createOrReplace();


}

File::~File()
{
    delete this->file;
    qDebug() << "~File()";
}

void File::copyFile()
{
    qDebug() << "copyFile() open";
    qDebug() << "get state" << synchronization->getState();

    quint64 available = synchronization->getBytesAvailable();
    quint64 subtract = this->size - this->current_size;
    if(this->size < this->current_size) subtract = 0;
    quint64 bytesToRead = qMin(available, subtract);
    QByteArray data_block_file;
    synchronization->getBytes(data_block_file, bytesToRead);
    qDebug() << "file->write(data_block_file)1";
    this->file->write(data_block_file);
    qDebug() << "file->write(data_block_file)2";
    this->current_size += data_block_file.size();

    if(this->current_size >= this->size) {
        qDebug() << "current_size >= size";
        qDebug() << "The file is received completely";
        this->file->close();
        qDebug() << "file->close()";
        synchronization->setState(Synchronization::Waiting);
    }

    if(available > bytesToRead){
        qDebug() << "available > bytesToRead";
        synchronization->setState(Synchronization::Waiting);
    }

    qDebug() << "copyFile() close";

}

void File::createOrReplace()
{
    qDebug() << "createOrReplace() open";

    this->file = new QFile(this->path + "/" + this->name);

    // Перевірка, чи існує файл
    if(this->file->exists()){
        qDebug() << "The file exists, replace:" << this->file->fileName();
        this->file->remove(); // Видалити існуючий файл
    }else{
        qDebug() << "The file does not exist, create it:" << this->file->fileName();
    }

    // Відкриваємо файл для запису
    if (!this->file->open(QIODevice::WriteOnly)) {
        qWarning() << "no open for write" << this->file->fileName();
    }

    qDebug() << "createOrReplace() close";

}
