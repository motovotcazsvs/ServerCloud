#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QObject>
#include <QTcpSocket>

class SettingsFile;
class Client;
class Authorization : public QObject
{
    Q_OBJECT

private:
    QString folder_id;
    Client* client;
    QTcpSocket* socket;
    quint64 id;
    SettingsFile* settingsfile;

    void sendID();

public:
    explicit Authorization(QObject* parent = nullptr, Client* client = nullptr, QTcpSocket* socket = nullptr, SettingsFile* settingsfile = nullptr);
    ~Authorization();
    QString getFolderID();
    quint64 getID();

signals:

public slots:

private slots:
    void authorizationClient();
};

#endif // AUTHORIZATION_H
