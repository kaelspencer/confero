#ifndef SESSION_H
#define SESSION_H

#include <QList>
#include "SessionManager.h"
#include "NetManager.h"
#include "HostID.h"
#include "Packet.h"

class NetManager;

class Session
{
    friend class SessionManager;

private:
    unsigned int m_sessionKey;
    NetManager * m_cnet;
    QList<HostID> m_hosts;

    Session(unsigned int sessionKey, NetManager * cnet);
    Session(const Session & rhs);
    Session & operator=(const Session & rhs);
    void AddHost(const HostID & hid);

public:
    ~Session();

    void SendToAll(const Packet * pkt);
};

#endif
