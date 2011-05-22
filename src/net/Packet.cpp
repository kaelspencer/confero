#include "Packet.h"

Packet::Packet()
: m_data(0), m_size(0)
{
    m_data = new char[m_MAX];
    memset(m_data, 0, m_MAX);
}

Packet::~Packet()
{
    if(m_data != 0)
    {
        delete [] m_data;
        m_data = 0;
    }
}

Packet::Packet(const Packet & rhs)
: m_data(0)
{
    m_data = new char[m_MAX];
    if(rhs.m_data != 0)
    {
        memcpy(m_data, rhs.m_data, m_MAX);
    }
}

void Packet::Add(char * data, unsigned short size)
{
    memcpy((void*)&(m_data[m_size]), data, size);
    m_size += size;
}
