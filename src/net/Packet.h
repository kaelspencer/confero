#ifndef PACKET_H
#define PACKET_H

#include <cstring>

class Packet
{
private:
    static const unsigned short m_MAX = 5000;
    char * m_data;
    unsigned short m_size;

    Packet & operator=(const Packet & rhs);

public:
    Packet();
    Packet(const Packet & rhs);
    ~Packet();

    void Add(char * data, unsigned short size);
    inline char * Data(unsigned short & size) const;
};

inline char * Packet::Data(unsigned short & size) const
{
    size = m_size;
    return m_data;
}

#endif
