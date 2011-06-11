#ifndef NETCLIENT_H
#define NETCLIENT_H

#include <QTcpSocket>
#include <QHostAddress>
#include <QList>
#include "SessionManager.h"
#include "NetServer.h"
#include "PacketDefs.h"
#include "Packet.h"

#include <string>
using std::string;

class SessionManager;
class NetManager;

class NetClient : QObject
{
    Q_OBJECT

private:
    QTcpSocket * m_socket;
    QHostAddress m_host;
    quint16 m_port;

    NetClient();
    NetClient(const NetClient & rhs);
    NetClient & operator=(const NetClient & rhs);

    void SendKeys(bool courtesy = false);
    qint64 HandleKeys(const Sessions * ss);
    qint64 ParsePacket(const char * data, SessionManager * sm);
    void PacketPump(const char * data, qint64 size);

public:
    NetClient(QTcpSocket * socket);
    NetClient(const QHostAddress & hostAddress, quint16 port);
    ~NetClient();

    inline bool IsConnected() const;
    void Connect();
    void ConnectSocketRead(const QObject * parent, const char * member);
    void ConnectNewSessionSlot(const QObject * parent, const char * member);
    void ConnectStatusMessageSlot(const QObject * parent, const char * member);
    void ConnectEditReadySlot(const QObject * parent, const char * member);

    void Write(const QByteArray & block);
    void WriteRawData(const char * data, unsigned short size);
    void WritePacket(const Packet * pkt);
    void SendSessionJoin(unsigned int key);

    inline QHostAddress GetHostAddress() const;
    inline void Abort();
    inline void DisconnectFromHost();

    inline void HaveConnection();

signals:
    void dataReady(const QString & block);
    void newSession(unsigned int key, const QString & host);
    void statusMessage(const QString & msg);
    void editReady(const char * data, size_t size, const QString &);

private slots:
    void Read();
};

//inline
QHostAddress NetClient::GetHostAddress() const
{
    return m_host;
}

void NetClient::Abort()
{
    m_socket->abort();
}

void NetClient::DisconnectFromHost()
{
    m_socket->disconnectFromHost();
}

void NetClient::HaveConnection()
{
    QHostAddress had(m_socket->peerAddress());
    QString str(35);

    if(had.isNull())
    {
        str = "New connection: no IP available";
    }
    else
    {
        str = "New connection: " + had.toString();
    }

    emit statusMessage(str);
}

#endif
