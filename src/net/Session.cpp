#include "Session.h"

Session::Session(unsigned int sessionKey, NetManager * cnet)
: m_sessionKey(sessionKey), m_cnet(cnet)
{

}

Session::~Session()
{

}

void Session::AddHost(const HostID & hid)
{
    if(!m_hosts.contains(hid))
    {
        m_hosts.append(hid);
    }
}

void Session::SendToAll(const Packet * pkt)
{
    QListIterator<HostID> itor(m_hosts);

    while(itor.hasNext())
    {
        m_cnet->SendTo(pkt, itor.next());
    }
}
