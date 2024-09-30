#ifndef FILE_H
#define FILE_H

#include <QObject>
#include <QFile>
#include <QDataStream>



class Synchronization;
class File
{
private:
    QFile* file;
    quint64 current_size;
    quint64 size;
    QString name;
    QString path;
    Synchronization* synchronization;
    void createOrReplace();

public:
    File(Synchronization*, QDataStream&);
    ~File();
    void copyFile();


signals:

private slots:


public slots:

};

#endif // FILE_H
