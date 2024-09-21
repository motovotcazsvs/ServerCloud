#ifndef SERVER_H
#define SERVER_H

#include <QObject>

#include "connect.h"
#include "client.h"

class Server: public QObject
{
    Q_OBJECT

public:
    Server();

private:
    Connect *connect;
    QMap<quint64, Client*> clients;  // Map to store clients by socket descriptor
private slots:
    void createNewClient();
};

#endif // SERVER_H
