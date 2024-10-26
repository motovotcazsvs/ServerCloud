#ifndef SYNCHRONIZATION_H
#define SYNCHRONIZATION_H

#include <QTcpSocket>
#include <QObject>


class File; //forward declaration
class Folder; //forward declaration
class Synchronization : public QObject
{
    Q_OBJECT

public:
    explicit Synchronization(QObject* parent = nullptr, QTcpSocket* sock = nullptr, QString path_id = "");
    ~Synchronization();
    enum State{
        Waiting,    // Очікування нових даних
        ReadingInfo,// Читання інформації про файли/папки
        ReadingFile, // Читання даних файлу
        Redundant
    };
    quint64 getBytesAvailable();
    void getBytes(QByteArray&, quint64);
    void setState(State);
    State getState();
    QString getCurrentPath();
    void setCurrentPath(QString);

private:
    QTcpSocket* socket;
    QList<Folder*> folders;
    File* file;
    quint16 size_info;
    QString path_id;
    QString current_path;
    State state;


private slots:
    void receive();

};

#endif // SYNCHRONIZATION_H
