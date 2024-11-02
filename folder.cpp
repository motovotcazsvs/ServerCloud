#include "folder.h"

#include <QDir>

#include "synchronization.h"

Folder::Folder(Synchronization* synchronization, QDataStream& in) : synchronization(synchronization)
{
    qDebug() << "Folder() open";

    in >> name;
    path = synchronization->getCurrentPath();
    previous_path = path;
    path = path + "/" + name;
    QDir().mkdir(path);
    synchronization->setCurrentPath(path);
    qDebug() << "START_FOLDER:" << name;

    qDebug() << "Folder() close";

}

Folder::~Folder()
{

}

//
void Folder::endFolder(QDataStream& in)
{
    qDebug() << "endFolder() open";


    QString endfolder;
    in >> endfolder;
    synchronization->setCurrentPath(previous_path);
    qDebug() << "END_FOLDER:" << endfolder;

    qDebug() << "endFolder() close";

}
