#include "connect.h"

Connect::Connect()
{
    tcpip = new Tcpip;
    udp = new Udp;
    protocol = new Protocol(tcpip);



    QObject::connect(protocol, &Protocol::newConnection, this, &Connect::serverConnect);

}

void Connect::serverConnect()
{
    emit newConnection();
}

quint64 Connect::getId()
{
    return protocol->getDescriptor();
}
