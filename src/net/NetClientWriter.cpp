#include "NetClientWriter.h"

NetClientWriter::NetClientWriter(QTcpSocket * socket, QObject * parent)
: m_socket(socket), QThread(parent), abort(false), mutex(0), m_data(0)
{
    mutex = new QMutex(QMutex::NonRecursive);
}

NetClientWriter::~NetClientWriter()
{
    abort = true;
    mutex->lock();
    condition.wakeOne();
    mutex->unlock();

    wait();
}

void NetClientWriter::Start()
{
    if(!isRunning())
    {
        start();
    }
}

void NetClientWriter::SendData(const char * data, size_t size)
{
    static int count = 0;
    ++count;
    qDebug() << "SendData " << count;

    char * ptr = new char[size];
    memcpy(ptr, data, size);

    mutex->lock();
    m_queue.enqueue(QPair<const char *, size_t> (ptr, size));
    mutex->unlock();

    if(!isRunning())
    {
        start();
    }
}

void NetClientWriter::run()
{
    return;
    quint64 bytesAvailable;

    forever
    {
        static int count2 = 0;
        ++count2;
        qDebug() << "Loop " << count2;

        if(abort)
        {
            return;
        }

        if((bytesAvailable = m_socket->bytesAvailable()) > 0)
        {
            static int count = 0;
            ++count;
            qDebug() << "BytesAvailable " << count;

            mutex->lock();
            if(m_data)
            {
                delete [] m_data;
            }

            m_data = new char[bytesAvailable + 1];
            m_bytesRead = m_socket->read(m_data, bytesAvailable + 1);

            mutex->unlock();
            emit dataReady();
        }

        while(!m_queue.isEmpty())
        {
            mutex->lock();
            QPair<const char *, size_t> pair = m_queue.dequeue();
            mutex->unlock();

            m_socket->write(pair.first, pair.second);
            //m_socket->waitForBytesWritten();
            delete [] pair.first;
        }

        //TODO: Why 500 ms?
        msleep(500);
    }
}

quint64 NetClientWriter::GetData(char ** data)
{
    static int count = 0;
    ++count;
    qDebug() << "GetData " << count;
    QMutexLocker locker(mutex);

    if(m_data == 0 || m_bytesRead <= 0)
    {
        return 0;
    }

    *data = new char[m_bytesRead];
    memcpy(*data, m_data, m_bytesRead);
    delete m_data;
    m_data = 0;

    return m_bytesRead;
}
