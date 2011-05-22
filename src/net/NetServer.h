#ifndef NETSERVER_H
#define NETSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include "NetClient.h"

class NetManager;
class NetClient;

class NetServer : QObject
{
    Q_OBJECT

private:
    QTcpServer * m_server;
    quint16 m_port;
    const NetManager * m_parent;

    NetServer();
    NetServer(const NetServer & rhs);
    NetServer & operator=(const NetServer & rhs);

public:
    NetServer(quint16 port, const NetManager * parent);
    ~NetServer();

    void Listen();
    NetClient * OnConnection() const;
};

#endif
