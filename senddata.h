#ifndef SENDDATA_H
#define SENDDATA_H

#include <QObject>

class SendData : public QObject
{
    Q_OBJECT
public:
    explicit SendData(QObject *parent = 0);

signals:

public slots:
};

#endif // SENDDATA_H