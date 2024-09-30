#ifndef SETTINGSFILE_H
#define SETTINGSFILE_H

#include <QMap>


class SettingsFile
{
public:
    SettingsFile(const QString&);
    ~SettingsFile();
    QString getFolderID(quint64)const;
    bool checkID(quint64);
    quint64 newID();

private:
    QMap<quint64, QString> list_id;
    void loadSettings(const QString& filePath);
    void saveSettingsFile();
    QString settingsfile_path;
    QString file_name;

};

#endif // SETTINGSFILE_H
