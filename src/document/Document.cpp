#include "Document.h"

kDocument::kDocument()
: m_doc(0), m_lines(0), m_chCount(0)
{
    m_doc = new QLinkedList<QLinkedList<char> * >();
}

kDocument::kDocument(const kDocument & rhs)
: m_doc(0), m_lines(0), m_chCount(0)
{
    *this = rhs;
}

kDocument::~kDocument()
{
    if(m_doc)
    {
        QLinkedList<char> * ptr;
        while(!m_doc->isEmpty())
        {
            ptr = m_doc->takeFirst();
            delete ptr;
        }

        delete m_doc;
        m_doc = 0;
    }

    m_lines = 0;
    m_chCount = 0;
}

kDocument & kDocument::operator=(const kDocument & rhs)
{
    m_lines = rhs.m_lines;
    m_chCount = rhs.m_chCount;

    if(rhs.m_doc)
    {
        m_doc = new QLinkedList<QLinkedList<char> * >();

        QLinkedListIterator<QLinkedList<char> *> itor(*rhs.m_doc);

        while(itor.hasNext())
        {
            *m_doc << new QLinkedList<char>(*itor.next());
        }
    }

    return *this;
}

QLinkedList<char> * kDocument::getLine(unsigned int line, QMutableLinkedListIterator<QLinkedList<char> *> & itor) const
{
    if(m_lines > line)
    {
        unsigned int i = 0;
        while(itor.hasNext() && i != line)
        {
            itor.next();
            ++i;
        }

        return itor.next();
    }
    else
    {
        return 0;
    }
}

QLinkedList<char> * kDocument::getLine(unsigned int line) const
{
    QMutableLinkedListIterator<QLinkedList<char> *> itor(*m_doc);
    return getLine(line, itor);
}

void kDocument::calcPos(unsigned int pos, int & line, int & index)
{
    if(pos > m_chCount)
    {
        line = -1;
        index = -1;
    }
    else
    {
        QLinkedListIterator<QLinkedList<char> *> itor(*m_doc);
        QLinkedList<char> * l = 0;
        int count = 0;
        line = 0;
        index = 0;

        while(itor.hasNext())
        {
            l = itor.next();

            if(l->size() + count == pos)
            {
                if(l->back() == char(10) || l->back() == char(13))
                {
                    count += l->size();
                    ++line;
                    break;
                }
                else
                {
                    break;
                }
            }
            else if(l->size() + count > pos)
            {
                break;
            }

            count += l->size();
            ++line;
        }

        if(l)
        {
            QLinkedListIterator<char> it(*l);

            while(it.hasNext() && count != pos)
            {
                it.next();
                ++count;
                ++index;
            }
        }
    }
}

void kDocument::insertAt(unsigned int pos, char ch, int & line, int & index)
{
    calcPos(pos, line, index);
    insertAt(line, index, ch);
}

void kDocument::insertAt(int line, int index, char ch)
{
    if(ch == char(10))
    {
        return;
    }
    else if(ch == char(13) && line < m_lines)
    {
        QMutableLinkedListIterator<QLinkedList<char> *> itor(*m_doc);
        QLinkedList<char> * l = getLine(line, itor);
        QLinkedList<char> * nextLine = new QLinkedList<char>;

        if(index == l->size())
        {
            if(itor.hasNext())
            {
                nextLine->append(13);
                nextLine->append(10);
                itor.insert(nextLine);
            }
            else
            {
                l->append(13);
                l->append(10);
                m_doc->append(nextLine);
            }

            ++m_lines;
        }
        else
        {
            QMutableLinkedListIterator<char> inItor(*l);

            int i = 0;
            while(inItor.hasNext())
            {
                if(i >= index)
                {
                    nextLine->append(inItor.next());
                    inItor.remove();
                }
                else
                {
                    inItor.next();
                }

                ++i;
            }

            l->append(13);
            l->append(10);
            itor.insert(nextLine);
            ++m_lines;
        }

        m_chCount += 2;
    }
    else if(line == m_lines && index >= 0)
    {
        QLinkedList<char> * ll = new QLinkedList<char>();
        ll->append(ch);
        m_doc->append(ll);

        ++m_chCount;
        ++m_lines;
    }
    else if(line >= 0 && line < m_lines && index >= 0)
    {
        QLinkedList<char> * list = getLine(line);

        if(index == 0)
        {
            list->push_front(ch);
        }
        else if(index == list->size())
        {
            list->push_back(ch);
        }
        else
        {
            QLinkedList<char>::iterator itor(list->begin()),
                                        end(list->end());

            int i = 0;
            for(; itor != end && i != index; ++itor, ++i);

            if(i == index)
            {
                list->insert(itor, ch);
            }
        }

        ++m_chCount;
    }
}

void kDocument::removeAt(unsigned int pos, int & line, int & index)
{
    calcPos(pos, line, index);
    removeAt(line, index);
}

void kDocument::removeAt(int line, int index)
{
    if(line < m_lines)
    {
        //QMutableLinkedListIterator<QLinkedList<char> *> oitor(*m_doc);
        //QLinkedList<char> * pline = getLine(line, oitor);
        QLinkedList<char> * pline = getLine(line);

        if(index < pline->size())
        {
            QMutableLinkedListIterator<char> iitor(*pline);
            char ch = 0;
            int i = 0;

            while(iitor.hasNext())
            {
                ch = iitor.next();
                if(i++ == index)
                {
                    iitor.remove();
                    --m_chCount;

                    if(ch == 13)
                    {
                        iitor.next();
                        iitor.remove();
                        --m_chCount;
                        joinLines(line);
                    }

                    break;
                }
            }
        }

        if(line == 0 && index == 0 && m_lines == 1 && pline->size() == 0)
        {
            m_doc->clear();
            m_lines = 0;
            m_chCount = 0;
        }
    }
}

void kDocument::joinLines(int line)
{
    QLinkedList<char> * pline = getLine(line);
    QLinkedList<char> * pline2 = getLine(line + 1);

    if(pline2)
    {
        while(!pline2->isEmpty())
        {
            pline->append(pline2->takeFirst());
        }

        QMutableLinkedListIterator<QLinkedList<char> *> itor(*m_doc);
        int i = 0;
        while(i != line + 2)
        {
            ++i;
            itor.next();
        }

        itor.remove();

        --m_lines;
    }
}

QString kDocument::Text() const
{
    QString text;
    QLinkedListIterator<QLinkedList<char> *> oitor(*m_doc);

    while(oitor.hasNext())
    {
        QLinkedListIterator<char> itor(*oitor.next());

        while(itor.hasNext())
        {
            text.append(itor.next());
        }
    }

    return text;
}
