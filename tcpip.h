#ifndef TCPIP_H
#define TCPIP_H

#include <QObject>

class tcpip : public QObject
{
    Q_OBJECT
public:
    explicit tcpip(QObject *parent = 0);

signals:

public slots:
};

#endif // TCPIP_H