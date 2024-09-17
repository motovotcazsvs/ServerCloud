#ifndef SETTINGSFILE_H
#define SETTINGSFILE_H

#include <QObject>

class SettingsFile : public QObject
{
    Q_OBJECT
public:
    explicit SettingsFile(QObject *parent = 0);

signals:

public slots:
};

#endif // SETTINGSFILE_H