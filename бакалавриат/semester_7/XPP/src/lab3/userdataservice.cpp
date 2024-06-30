#include <iostream>
#include <QFile>
#include <QTextStream>
#include "userdataservice.h"

UserDataService::UserDataService(QObject *parent)
    : QObject{parent}
{}

bool UserDataService::send(const UserData &data) const
{
    using std::cerr;
    using std::endl;

    QFile file{"/tmp/plainfile.txt"};
    const bool open_res = file.open(QIODeviceBase::OpenModeFlag::WriteOnly);
    if (open_res)
    {
        QTextStream fstrm{&file};
        fstrm << data.name << " <" << data.email << ">" << "\n\n"
              << data.title << "\n\n"
              << data.body;
    }
    else
    {
        cerr << "Unable to open file " << file.fileName().toStdString() << endl;
    }
    return open_res;
}
