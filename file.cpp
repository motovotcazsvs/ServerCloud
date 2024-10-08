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

void File::createOrReplace()
{

    file = new QFile(path + "/" + name);

    // Перевірка, чи існує файл
    if(file->exists()){
        qDebug() << "Файл існує, замінюємо:" << file->fileName();
        file->remove(); // Видалити існуючий файл
    }else{
        qDebug() << "Файл не існує, створюємо:" << file->fileName();
    }

    // Відкриваємо файл для запису
    if (!file->open(QIODevice::WriteOnly)) {
        qWarning() << "no open for write" << file->fileName();
    }
}
