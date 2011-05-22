#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <QMap>
#include "Session.h"
#include "NetManager.h"
#include "../Random.h"
#include "Packet.h"
#include "PacketDefs.h"

class Session;
const quint16 g_DefaultPort = 48984;

class SessionManager
{
    friend void HostConnected(unsigned int key, const HostID & hid);

private:
    static SessionManager * m_instance;
    QMap<unsigned int, Session *> m_sessions;
    NetManager * m_netmgr;

    SessionManager();
    SessionManager(quint16 port);
    SessionManager & operator=(const SessionManager & rhs);
    SessionManager(const SessionManager & rhs);

    void HostConnected(unsigned int key, const HostID & hid);

public:
    ~SessionManager();
    static SessionManager * Instance();
    NetManager * GetCNet() const { return m_netmgr; }

    unsigned int CreateSession();
    void AddHostToSession(unsigned int key, const HostID & hid);
    void SendMessage(const QString & msg, unsigned int key);
    void SendEdit(const unsigned char * data, size_t size, unsigned int key);
    void SendChat(const unsigned char * data, size_t size, const QString & host);
    void ConnectToHost(const QHostAddress & hostAddress, unsigned int key);
    void ConnectToHost(const QHostAddress & hostAddress);
    void ConnectAndJoin(const QHostAddress & hostAddress, unsigned int key);
    QList<unsigned int> GetKeys() const;
    void InformAllOfNewSession(unsigned int key) const;

    void JoinExistingSession(unsigned int key, const HostID & hid);

    void SetMessageReady(const QObject * receiver, const char * member);
    void SetNewSessionSlot(const QObject * receiver, const char * member);
    void SetStatusMessageSlot(const QObject * receiver, const char * member);
    void SetEditReadySlot(const QObject * receiver, const char * member);
};

#endif
