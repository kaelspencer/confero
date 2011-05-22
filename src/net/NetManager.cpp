#include "NetManager.h"

NetManager::NetManager(quint16 port, const QObject * tcpReadSlotParent, const char * tcpReadSlot)
: m_server(0), m_port(port),
m_tcpReadSlotParent(tcpReadSlotParent), m_tcpReadSlot(tcpReadSlot),
m_newSessionParent(0), m_newSessionSlot(0),
m_statusMessageParent(0), m_statusMessageSlot(0),
m_editReadyParent(0), m_editReadySlot(0)
{
    m_server = new NetServer(m_port, this);
    m_server->Listen();
}

NetManager::~NetManager()
{
    if(m_server)
    {
        //m_server->stop();
        delete m_server;
        m_server = 0;
    }
}

void NetManager::OnServerConnection()
{
    NetClient * client = m_server->OnConnection();
    HostID hid(client->GetHostAddress());

    if(!(hid == HostID(QHostAddress::LocalHost)) || !m_remoteHosts.contains(hid))
    {
        Connect(client);
        m_remoteHosts.insert(hid, client);
        client->HaveConnection();
    }
    else
    {
        client->Abort();
    }
}

NetClient * NetManager::ConnectToHost(const QHostAddress & hostAddress)
{
    HostID hid(hostAddress);

    if(!m_remoteHosts.contains(hid))
    {
        NetClient * client = new NetClient(hostAddress, m_port);
        m_remoteHosts.insert(hid, client);
        client->Connect();
        Connect(client);
        return client;
    }

    return m_remoteHosts.value(hid);
}

NetClient * NetManager::ConnectToHost(const QHostAddress & hostAddress, unsigned int key)
{
    HostID hid(hostAddress);

    if(!m_remoteHosts.contains(hid))
    {
        NetClient * client = new NetClient(hostAddress, m_port);
        m_remoteHosts.insert(hid, client);
        client->Connect();
        Connect(client);

        Header hdr;
        hdr.type = SESSIONREQUEST;

        Packet * pkt = new Packet();
        pkt->Add((char*) &hdr, sizeof(Header));
        client->WritePacket(pkt);
        delete pkt;

        return client;
    }

    return m_remoteHosts.value(hid);
}

void NetManager::SendToAll(const QByteArray & block)
{
    foreach(NetClient * client, m_remoteHosts)
    {
        client->Write(block);
    }
}

void NetManager::SendToAll(const Packet * pkt)
{
    foreach(NetClient * client, m_remoteHosts)
    {
        client->WritePacket(pkt);
    }
}

void NetManager::SendTo(const Packet * pkt, const HostID & host)
{
    if(m_remoteHosts.contains(host))
    {
        m_remoteHosts[host]->WritePacket(pkt);
    }
}

void NetManager::SetMessageReady(const QObject * receiver, const char * member)
{
    m_tcpReadSlotParent = receiver;
    m_tcpReadSlot = member;

    QHashIterator<HostID, NetClient *> itor(m_remoteHosts);

    while(itor.hasNext())
    {
        itor.next();
        itor.value()->ConnectSocketRead(m_tcpReadSlotParent, m_tcpReadSlot);
    }
}

void NetManager::SetNewSessionSlot(const QObject * receiver, const char * member)
{
    m_newSessionParent = receiver;
    m_newSessionSlot = member;

    QHashIterator<HostID, NetClient *> itor(m_remoteHosts);

    while(itor.hasNext())
    {
        itor.next();
        itor.value()->ConnectNewSessionSlot(m_newSessionParent, m_newSessionSlot);
    }
}

void NetManager::SetStatusMessageSlot(const QObject * receiver, const char * member)
{
    m_statusMessageParent = receiver;
    m_statusMessageSlot = member;

    QHashIterator<HostID, NetClient *> itor(m_remoteHosts);

    while(itor.hasNext())
    {
        itor.next();
        itor.value()->ConnectStatusMessageSlot(m_statusMessageParent, m_statusMessageSlot);
    }
}

void NetManager::SetEditReadySlot(const QObject * receiver, const char * member)
{
    m_editReadyParent = receiver;
    m_editReadySlot = member;

    QHashIterator<HostID, NetClient *> itor(m_remoteHosts);

    while(itor.hasNext())
    {
        itor.next();
        itor.value()->ConnectEditReadySlot(m_editReadyParent, m_editReadySlot);
    }
}

void NetManager::Connect(NetClient * client)
{
    client->ConnectSocketRead(m_tcpReadSlotParent, m_tcpReadSlot);
    client->ConnectNewSessionSlot(m_newSessionParent, m_newSessionSlot);
    client->ConnectStatusMessageSlot(m_statusMessageParent, m_statusMessageSlot);
    client->ConnectEditReadySlot(m_editReadyParent, m_editReadySlot);
}
