#include "HostID.h"

HostID::HostID(const ID_TYPE & id)
: m_id(id), m_ipAddr(id.toIPv4Address())
{
}

HostID::HostID(const HostID & rhs)
: m_id(rhs.m_id), m_ipAddr(rhs.m_id.toIPv4Address())
{

}

HostID::~HostID()
{

}

HostID & HostID::operator =(const HostID & rhs)
{
    if(this != &rhs)
    {
        m_id = rhs.m_id;
        m_ipAddr = rhs.m_ipAddr;
    }

    return *this;
}

uint qHash(const HostID & key)
{
    return qHash(key.m_id.toIPv4Address());
}
