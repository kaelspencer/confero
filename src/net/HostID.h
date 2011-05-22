#ifndef HOSTID_H
#define HOSTID_H

#include <QHostAddress>

typedef QHostAddress ID_TYPE;

class HostID
{
    friend uint qHash(const HostID & key);

private:
    ID_TYPE m_id;
    quint32 m_ipAddr;

public:
    HostID(const ID_TYPE & id);
    HostID(const HostID & rhs);
    ~HostID();
    HostID & operator=(const HostID & rhs);
    inline bool operator==(const HostID & rhs) const;
    const ID_TYPE & GetID() const { return m_id; }
};

uint qHash(const HostID & key);

//inline
bool HostID::operator==(const HostID & rhs) const
{
    return (m_id == rhs.m_id);
}

#endif
