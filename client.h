#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

#include "authorization.h"
#include "synchronization.h"


class Client: public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject* parent = nullptr, QTcpSocket* sock = nullptr);
    enum State {
        stateWaiting,
        stateSync
    };
    ~Client();

private:
    QTcpSocket* socket;
    State state;
    QString ID;
    QString folder_id;
    qintptr socket_descriptor;
    Synchronization* synchronization;
    Authorization* authorization;


signals:
    void signalReceive();

private slots:
    void slotReadyRead();
};

#endif // CLIENT_H
