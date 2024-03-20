#ifndef USERDATASERVICE_H
#define USERDATASERVICE_H

#include <QString>
#include <QObject>

struct UserData
{
    QString name, email, title, body;
};

class UserDataService : public QObject
{
    Q_OBJECT
public:
    explicit UserDataService(QObject *parent = nullptr);
    bool send(const UserData& data) const;

signals:

};

#endif // USERDATASERVICE_H
