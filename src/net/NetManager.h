#ifndef NETMANAGER_H
#define NETMANAGER_H

#include <QHash>

#include "NetServer.h"
#include "NetClient.h"
#include "HostID.h"
#include "Packet.h"

void HostConnected(unsigned int key, const HostID & hid);

class NetClient;
class NetServer;

class NetManager : QObject
{
    Q_OBJECT

    friend class NetServer;

private:
    QHash<HostID, NetClient *> m_remoteHosts;
    NetServer * m_server;
    quint16 m_port;

    const QObject * m_tcpReadSlotParent;
    const char * m_tcpReadSlot;
    const QObject * m_newSessionParent;
    const char * m_newSessionSlot;
    const QObject * m_statusMessageParent;
    const char * m_statusMessageSlot;
    const QObject * m_editReadyParent;
    const char * m_editReadySlot;

    NetManager();
    NetManager(const NetManager & rhs);
    NetManager & operator=(const NetManager & rhs);

    void Connect(NetClient * client);

private slots:
    void OnServerConnection();

public:
    NetManager(quint16 port, const QObject * tcpReadSlotParent, const char * tcpReadSlot);
    ~NetManager();

    NetClient * ConnectToHost(const QHostAddress & hostAddress);
    NetClient * ConnectToHost(const QHostAddress & hostAddress, unsigned int key);
    void SendToAll(const QByteArray & block);
    void SendToAll(const Packet * pkt);
    void SendTo(const Packet * pkt, const HostID & hosts);

    void SetMessageReady(const QObject * receiver, const char * member);
    void SetNewSessionSlot(const QObject * receiver, const char * member);
    void SetStatusMessageSlot(const QObject * receiver, const char * member);
    void SetEditReadySlot(const QObject * receiver, const char * member);
};

#endif // CONFERONET_H
