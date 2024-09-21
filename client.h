#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

#include "authorization.h"
#include "copy.h"
#include "connect.h"

class Client: public QObject
{
    Q_OBJECT

private:
    Connect* connect;
    Copy *copy;

public:
    Client(Connect*);
};

#endif // CLIENT_H
