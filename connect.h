#ifndef CONNECT_H
#define CONNECT_H

#include <QObject>

#include "protocol.h"

class Connect: public QObject
{
    Q_OBJECT

private:
    Protocol *protocol;
    Tcpip* tcpip;
    Udp* udp;

public:
    Connect();
    quint64 getId();

signals:
    void newConnection();
private slots:
    void serverConnect();



};

#endif // CONNECT_H
