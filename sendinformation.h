#ifndef SENDINFORMATION_H
#define SENDINFORMATION_H

#include <QObject>

class SendInformation : public QObject
{
    Q_OBJECT
public:
    explicit SendInformation(QObject *parent = 0);

signals:

public slots:
};

#endif // SENDINFORMATION_H