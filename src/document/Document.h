#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QLinkedList>
#include <QString>

class kDocument
{
private:
    QLinkedList<QLinkedList<char> * > * m_doc;
    unsigned int m_lines;
    unsigned int m_chCount;

    QLinkedList<char> * getLine(unsigned int line) const;
    QLinkedList<char> * getLine(unsigned int line, QMutableLinkedListIterator<QLinkedList<char> *> & inItor) const;
    void calcPos(unsigned int pos, int & line, int & index);
    void joinLines(int line);

public:
    kDocument();
    ~kDocument();
    kDocument(const kDocument & rhs);
    kDocument & operator=(const kDocument & rhs);

    void insertAt(unsigned int pos, char ch, int & line, int & index);
    void insertAt(int line, int index, char ch);
    void removeAt(unsigned int pos, int & line, int & index);
    void removeAt(int line, int index);

    QString Text() const;
};

#endif
