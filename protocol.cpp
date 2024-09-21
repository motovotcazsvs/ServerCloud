#include "protocol.h"

Protocol::Protocol(Tcpip* tcpip) :tcpip(tcpip)
{
    descriptor = tcpip->getDescriptor();

    QObject::connect(tcpip, &Tcpip::newConnection, this, &Protocol::connectTCPIPUDP);

}

Protocol::Protocol(Udp* udp)
{

    //descriptor = udp->getDescriptor();

    //QObject::connect(udp, &Udp::newConnection, this, &Protocol::connectTCPIPUDP);

}

void Protocol::connectTCPIPUDP()
{
    emit newConnection();
}

quint64 Protocol::getDescriptor()
{
    return descriptor;
}
