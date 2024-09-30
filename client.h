#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

#include "authorization.h"
#include "synchronization.h"

class SettingsFile;
class Client: public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject* parent = nullptr, QTcpSocket* sock = nullptr, SettingsFile* settingsfile = nullptr);
    enum State {
        stateWaiting,
        stateSync
    };
    ~Client();
    void setID(quint64);
    void setFolderID(QString);
    void authorizationSuccessful();

private:
    QTcpSocket* socket;
    State state;
    quint64 ID;
    QString folder_id;
    qintptr socket_descriptor;
    Synchronization* synchronization;
    Authorization* authorization;



signals:


private slots:

};

#endif // CLIENT_H
