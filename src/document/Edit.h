#ifndef EDIT_H
#define EDIT_H

#include <cstring>

const int SC_MOD_INSERTTEXT = 0x0001;
const int SC_MOD_DELETETEXT = 0x0002;
const int CHAT_MESSAGE = 0x1000;

typedef struct
{
    unsigned int key;
    int line;
    int index;
    int type;
    int length;
} EditData;

class Edit
{
private:
    unsigned int m_key;
    char * m_value;
    int m_line;
    int m_index;
    int m_type;
    int m_length;

public:
    Edit(const char * data, size_t size);
    Edit(const char * value, int length, int line, int index, int type, unsigned int key);
    ~Edit() {};
    Edit(const Edit & rhs);
    Edit & operator=(const Edit & rhs);

    inline char * GetValue() const;
    inline int GetLine() const;
    inline int GetIndex() const;
    inline int GetType() const;
    inline int GetLength() const;
    inline unsigned int GetKey() const;

    const unsigned char * GetData(size_t & size) const;
};

//inline
char * Edit::GetValue() const
{
    return m_value;
}

int Edit::GetLine() const
{
    return m_line;
}

int Edit::GetIndex() const
{
    return m_index;
}

int Edit::GetType() const
{
    return m_type;
}

int Edit::GetLength() const
{
    return m_length;
}

unsigned int Edit::GetKey() const
{
    return m_key;
}

#endif
