#ifndef FOLDER_H
#define FOLDER_H

#include <QObject>

class Folder : public QObject
{
    Q_OBJECT
public:
    explicit Folder(QObject *parent = 0);

signals:

public slots:
};

#endif // FOLDER_H