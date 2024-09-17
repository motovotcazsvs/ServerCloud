#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QObject>

class Authorization : public QObject
{
    Q_OBJECT
public:
    explicit Authorization(QObject *parent = 0);

signals:

public slots:
};

#endif // AUTHORIZATION_H