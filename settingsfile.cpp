#include "settingsfile.h"

#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QDir>

SettingsFile::SettingsFile(const QString& settingsfile_p)
{
    settingsfile_path = settingsfile_p;
    loadSettings(settingsfile_path);
}

SettingsFile::~SettingsFile()
{

}

void SettingsFile::loadSettings(const QString& settingsfile_path)
{
    QFile file(settingsfile_path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "no open file!" << settingsfile_path;
        saveSettingsFile(); // Викликаємо функцію для збереження базових даних у файл
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);

    if (!doc.isObject()) {
        qWarning() << "no format json!";
        return;
    }

    QJsonObject jsonObj = doc.object();
    QJsonArray clientsArray = jsonObj["clients"].toArray();

    for (const QJsonValue& value : clientsArray) {
        QJsonObject clientObj = value.toObject();
        quint64 clientId = clientObj["id"].toVariant().toULongLong();
        QString folderName = clientObj["folder"].toString();

        list_id[clientId] = folderName;
    }
}

QString SettingsFile::getFolderID(quint64 id)const
{
    if(list_id.contains(id)){
        return list_id[id];
    }
    else return QString();
}

quint64 SettingsFile::newID()
{
    quint64 newId = 1; // Починаємо з 1, якщо ще немає жодного ID

    if (!list_id.isEmpty()) {
        newId = list_id.lastKey() + 1; // Генеруємо новий ID на основі останнього
    }


    QString folderName = "ID" + QString::number(newId);
    list_id[newId] = folderName;

    QDir dir;
    dir.mkpath(folderName);

    qDebug() << "New ID generated:" << newId << "folder:" << folderName;

    saveSettingsFile(); // Зберігаємо новий ID у файл після генерації
    return newId;
}

void SettingsFile::saveSettingsFile()
{
    QFile file(settingsfile_path);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "no open file for write!" << settingsfile_path;
        return;
    }

    QJsonArray idsArray;
    for (auto it = list_id.begin(); it != list_id.end(); ++it) {
        QJsonObject obj;
        obj["id"] = QString::number(it.key());
        obj["folder"] = it.value();
        idsArray.append(obj);
    }

    QJsonObject json;
    json["ids"] = idsArray;

    QJsonDocument doc(json);
    file.write(doc.toJson());
    file.close();

    qDebug() << "save settings";
}

