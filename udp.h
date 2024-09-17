#ifndef UDP_H
#define UDP_H

#include <QObject>

class udp : public QObject
{
    Q_OBJECT
public:
    explicit udp(QObject *parent = 0);

signals:

public slots:
};

#endif // UDP_H