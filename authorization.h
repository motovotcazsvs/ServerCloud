#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QObject>
#include <QTcpSocket>

class SettingsFile;
class Authorization : public QObject
{
    Q_OBJECT

private:
    QString folder_id;
    QTcpSocket* socket;
    quint64 id;
    SettingsFile* settingsfile;
    void sendID();
    void sendOK();

public:
    explicit Authorization(QObject* parent = nullptr, QTcpSocket* socket = nullptr, SettingsFile* settingsfile = nullptr);
    ~Authorization();
    QString getFolderID();
    quint64 getID();
    void disconnectSignal();

signals:
    void authorizationSuccessfull();

public slots:

private slots:
    void authorizationClient();
};

#endif // AUTHORIZATION_H
