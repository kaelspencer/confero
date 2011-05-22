#ifndef NETCLIENTWRITER_H
#define NETCLIENTWRITER_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QQueue>
#include <QTcpSocket>

class NetClientWriter : public QThread
{
    Q_OBJECT

private:
    QTcpSocket * m_socket;
    QQueue<QPair<const char *, size_t> > m_queue;
    char * m_data;
    quint64 m_bytesRead;

    QMutex * mutex;
    QWaitCondition condition;
    bool abort;
    NetClientWriter();
    NetClientWriter(const NetClientWriter & rhs);
    NetClientWriter & operator=(const NetClientWriter & rhs);

protected:
    void run();

public:
    NetClientWriter(QTcpSocket * socket, QObject * parent = 0);
    ~NetClientWriter();

    void Start();
    void SendData(const char * data, size_t size);
    quint64 GetData(char ** data);

signals:
    void dataReady();
};

#endif
