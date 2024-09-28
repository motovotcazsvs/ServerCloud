#include "folder.h"

#include <QDir>

#include "synchronization.h"

Folder::Folder(Synchronization* synchronization, QDataStream& in) : synchronization(synchronization)
{
    in >> name;
    path = synchronization->getCurrentPath();
    previous_path = path;
    path = path + "/" + name;
    QDir().mkdir(path);
    synchronization->setCurrentPath(path);
    qDebug() << "START_FOLDER:" << name;
}

Folder::~Folder()
{

}

//
void Folder::endFolder(QDataStream& in)
{
    QString endfolder;
    in >> endfolder;
    synchronization->setCurrentPath(previous_path);
    qDebug() << "END_FOLDER:" << endfolder;
}
