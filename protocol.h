#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QObject>

class Protocol : public QObject
{
    Q_OBJECT
public:
    explicit Protocol(QObject *parent = 0);

signals:

public slots:
};

#endif // PROTOCOL_H