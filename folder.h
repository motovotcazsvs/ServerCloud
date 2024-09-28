#ifndef FOLDER_H
#define FOLDER_H

#include <QObject>
#include <QDataStream>


class Synchronization;
class Folder
{
private:
    QString path;
    QString name;
    QString previous_path;
    Synchronization* synchronization;

public:
    Folder(Synchronization*, QDataStream&);
    ~Folder();
    void endFolder(QDataStream&);

};

#endif // FOLDER_H
