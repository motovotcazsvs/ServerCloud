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
    QTcpSocket* socket;
    quint64 id;
    SettingsFile* settingsfile;
    Client* client;

public:
    explicit Authorization(QObject* parent = nullptr, Client* client = nullptr, QTcpSocket* sock = nullptr, SettingsFile* settingsfile = nullptr);
    ~Authorization();
    QString getFolderID();
    quint64 getID();

signals:

public slots:

private slots:
    void authorizationClient();
};

#endif // AUTHORIZATION_H
