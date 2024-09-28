#include "file.h"

#include <QDebug>

#include "synchronization.h"

File::File(Synchronization* synchronization, QDataStream& in) : synchronization(synchronization)
{
    in >> name >> size;
    current_size = 0;
    path = synchronization->getCurrentPath();
    file = new QFile(path + "/" + name);
    file->open(QIODevice::WriteOnly | QIODevice::Append);

}

File::~File()
{
    delete file;
    qDebug() << "~File()";
}

void File::copyFile()
{
    quint64 available = synchronization->getBytesAvailable();
    quint64 subtract = size - current_size;
    if(size < current_size) subtract = 0;
    quint64 bytesToRead = qMin(available, subtract);
    QByteArray data_block_file;
    synchronization->getBytes(data_block_file, bytesToRead);
    file->write(data_block_file);
    current_size += data_block_file.size();

    if(current_size >= size) {
        qDebug() << "Файл отримано повністю";
        file->close();
        synchronization->setState(Synchronization::ReadingInfo);
    }

    if(available > bytesToRead) synchronization->setState(Synchronization::ReadingInfo);



}
