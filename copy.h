#ifndef COPY_H
#define COPY_H

#include <QObject>

#include "file.h"
#include "folder.h"

class Copy : public QObject
{
    Q_OBJECT

private:
    File* file;
    Folder* folder;

public:
    explicit Copy(QObject *parent = 0);

signals:

public slots:
};

#endif // COPY_H
