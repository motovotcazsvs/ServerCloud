#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>

#include "settingsfile.h"
#include "client.h"

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server();
    ~Server();

private:
    QMap<qintptr, Client*> clients;
    void createNewClient(qintptr);
    quint16 port;
    quint32 ip;
    QTcpSocket* socket;
    SettingsFile* settingsfile;


private slots:
    void deleteClient();

public slots:
    void incomingConnection(qintptr);

};

#endif // SERVER_H
