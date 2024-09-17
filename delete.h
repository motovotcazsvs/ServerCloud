#ifndef DELETE_H
#define DELETE_H

#include <QObject>

class Delete : public QObject
{
    Q_OBJECT
public:
    explicit Delete(QObject *parent = 0);

signals:

public slots:
};

#endif // DELETE_H