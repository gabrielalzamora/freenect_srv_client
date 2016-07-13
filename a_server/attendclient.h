#ifndef ATTENDCLIENT_H
#define ATTENDCLIENT_H

#include <QObject>
#include <QTcpServer>

class AttendClient : public QTcpServer
{
public:
    AttendClient();
};

#endif // ATTENDCLIENT_H
