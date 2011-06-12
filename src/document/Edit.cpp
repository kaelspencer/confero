#include "Edit.h"

Edit::Edit(const char * data, size_t size)
: m_key(-1), m_value(), m_line(-1), m_index(-1), m_type(-1), m_length(0)
{
    if(size >= sizeof(EditData))
    {
        const EditData * ed = reinterpret_cast<const EditData *> (data);
        m_key = ed->key;
        m_line = ed->line;
        m_index = ed->index;
        m_type = ed->type;
        m_length = ed->length;

        if(m_length > 0)
        {
            m_value = new char[m_length];
            memcpy(m_value, data + sizeof(*ed), m_length);
        }
    }
}

Edit::Edit(const char * value, int length, int line, int index, int type, unsigned int key)
: m_key(key), m_value(0), m_line(line), m_index(index), m_type(type), m_length(length)
{
    m_value = new char[length];
    memcpy(m_value, value, length);
}

const unsigned char * Edit::GetData(size_t & size) const
{
    size = sizeof(EditData) + m_length;

    EditData ed;
    ed.key = m_key;
    ed.line = m_line;
    ed.index = m_index;
    ed.type = m_type;
    ed.length = m_length;

    unsigned char * data = new unsigned char[size];
    memcpy(data, &ed, sizeof(ed));
    memcpy(data + sizeof(ed), m_value, m_length);

    return data;
}
