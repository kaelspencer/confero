#include "SessionManager.h"

SessionManager * SessionManager::m_instance = 0;

SessionManager::SessionManager(quint16 port)
: m_sessions(), m_netmgr(0)
{
    m_netmgr = new NetManager(port, 0, 0);
}

SessionManager * SessionManager::Instance()
{
    if(m_instance == 0)
    {
        m_instance = new SessionManager(g_DefaultPort);
    }

    return m_instance;
}

SessionManager::~SessionManager()
{
    if(m_netmgr != 0)
    {
        delete m_netmgr;
        m_netmgr = 0;
    }

    QMapIterator<unsigned int, Session *> itor(m_sessions);

    while(itor.hasNext())
    {
        itor.next();
        delete itor.value();
    }
}

unsigned int SessionManager::CreateSession()
{
    unsigned int key = 0;

    while( m_sessions.find(key = Random::Instance()->GetNumber()) != m_sessions.end() );

    m_sessions[key] = new Session(key, m_netmgr);

    InformAllOfNewSession(key);

    return key;
}

void SessionManager::HostConnected(unsigned int key, const HostID & hid)
{
    if(m_sessions.contains(key))
    {
        Session * session = m_sessions[key];
        Header hdr;
        hdr.type = SESSIONHOST;
        SessionHosts sh;
        sh.key = key;
        sh.hostCount = session->m_hosts.size();

        Packet * pkt = new Packet();
        pkt->Add((char*)&hdr, sizeof(hdr));
        pkt->Add((char*)&sh, sizeof(sh));

        quint32 ip = 0;
        for(int i = 0; i < session->m_hosts.size(); ++i)
        {
            ip = session->m_hosts.at(i).GetID().toIPv4Address();
            pkt->Add((char*) &ip, sizeof(quint32));
        }

        m_netmgr->SendTo(pkt, hid);

        delete pkt;

        m_sessions[key]->AddHost(hid);
    }
}

void SessionManager::AddHostToSession(unsigned int key, const HostID & hid)
{
    if(m_sessions.contains(key))
    {
        m_sessions.value(key)->AddHost(hid);
    }
}

void SessionManager::SendMessage(const QString & msg, unsigned int key)
{
    Packet * pkt = new Packet();

    Header hdr;
    hdr.type = MESSAGE;
    Message mess;
    mess.length = msg.size();

    pkt->Add((char*) &hdr, sizeof(hdr));
    pkt->Add((char*) &mess, sizeof(msg));
    pkt->Add(msg.toAscii().data(), mess.length);

    m_sessions.value(key)->SendToAll(pkt);

    delete pkt;
}

void SessionManager::SendEdit(const unsigned char * data, size_t size, unsigned int key)
{
    Packet * pkt = new Packet();

    Header hdr;
    hdr.type = EDIT;
    EditStruct ed;
    ed.size = size;

    pkt->Add((char*) &hdr, sizeof(hdr));
    pkt->Add((char*) &ed, sizeof(ed));
    pkt->Add((char*) data, size);

    if(m_sessions.contains(key))
    {
        m_sessions.value(key)->SendToAll(pkt);
    }

    delete pkt;
}

void SessionManager::SendChat(const unsigned char * data, size_t size, const QString & host)
{
    Packet * pkt = new Packet();

    Header hdr;
    hdr.type = EDIT;
    EditStruct ed;
    ed.size = size;

    pkt->Add((char*) &hdr, sizeof(hdr));
    pkt->Add((char*) &ed, sizeof(ed));
    pkt->Add((char*) data, size);

    QHostAddress had(host);
    HostID hid(had);
    m_netmgr->SendTo(pkt, hid);

    delete pkt;
}

void SessionManager::SetMessageReady(const QObject * receiver, const char * member)
{
    m_netmgr->SetMessageReady(receiver, member);
}

void SessionManager::SetNewSessionSlot(const QObject * receiver, const char * member)
{
    m_netmgr->SetNewSessionSlot(receiver, member);
}

void SessionManager::SetStatusMessageSlot(const QObject * receiver, const char * member)
{
    m_netmgr->SetStatusMessageSlot(receiver, member);
}

void SessionManager::SetEditReadySlot(const QObject * receiver, const char * member)
{
    m_netmgr->SetEditReadySlot(receiver, member);
}

void SessionManager::ConnectToHost(const QHostAddress & hostAddress, unsigned int key)
{
    HostID hid(hostAddress);

    if(!m_sessions.value(key)->m_hosts.contains(hid))
    {
        NetClient * client = m_netmgr->ConnectToHost(hostAddress);
        m_sessions.value(key)->AddHost(hid);

        Header hdr;
        hdr.type = SESSIONOFFER;

        SessionHosts sh;
        sh.key = key;

        //this is temporary
        //it needs to list all of the hosts in the session
        sh.hostCount = 0;

        Packet * pkt = new Packet();
        pkt->Add((char*) &hdr, sizeof(hdr));
        pkt->Add((char*) &sh, sizeof(sh));

        client->WritePacket(pkt);

        delete pkt;
    }
}

void SessionManager::ConnectToHost(const QHostAddress & hostAddress)
{
    NetClient * client = m_netmgr->ConnectToHost(hostAddress);

    Header hdr;
    hdr.type = SESSIONREQUEST;

    Packet * pkt = new Packet();
    pkt->Add((char*) &hdr, sizeof(hdr));

    client->WritePacket(pkt);

    delete pkt;
}

void SessionManager::ConnectAndJoin(const QHostAddress & hostAddress, unsigned int key)
{
    NetClient * client = m_netmgr->ConnectToHost(hostAddress);

    Header hdr;
    hdr.type = SESSIONJOIN;
    SessionJoin sj;
    sj.key = key;

    Packet * pkt = new Packet();
    pkt->Add((char*) &hdr, sizeof(hdr));
    pkt->Add((char*) &sj, sizeof(sj));

    client->WritePacket(pkt);

    delete pkt;
}

QList<unsigned int> SessionManager::GetKeys() const
{
    return m_sessions.keys();
}

void HostConnected(unsigned int key, const HostID & hid)
{
    SessionManager::Instance()->HostConnected(key, hid);
}

void SessionManager::JoinExistingSession(unsigned int key, const HostID & hid)
{
    if(m_sessions.contains(key))
    {
        m_sessions.value(key)->AddHost(hid);
    }
    else
    {
        Session * s = new Session(key, m_netmgr);
        m_sessions.insert(key, s);
        s->AddHost(hid);
    }

    ConnectAndJoin(hid.GetID(), key);
}

void SessionManager::InformAllOfNewSession(unsigned int key) const
{
    Header hdr;
    hdr.type = SESSIONCOURTESY;

    Sessions ss;
    ss.count = 1;

    Packet * pkt = new Packet();
    pkt->Add((char*) &hdr, sizeof(Header));
    pkt->Add((char*) &ss, sizeof(Sessions));
    pkt->Add((char*) &key, sizeof(key));

    m_netmgr->SendToAll(pkt);

    delete pkt;
}
