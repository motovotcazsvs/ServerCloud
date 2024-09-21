#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QObject>

#include "Tcpip.h"
#include "Udp.h"

class Protocol: public QObject
{
    Q_OBJECT

private:
    Tcpip* tcpip;
    Udp* udp;
    int descriptor;
    void protocolTCPIP();
    void protocolUDP();

public:
    Protocol(Tcpip*);
    Protocol(Udp*);
    quint64 getDescriptor();

signals:
    void newConnection();

public slots:

private slots:
    void connectTCPIPUDP();

};

#endif // PROTOCOL_H
