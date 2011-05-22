#ifndef CONFERONET_H
#define CONFERONET_H

#include "SessionManager.h"

class ConferoNet
{
private:
    static ConferoNet * m_inst;
    SessionManager * m_sm;

    ConferoNet();
    ConferoNet(const ConferoNet & rhs);
    ConferoNet & operator=(const ConferoNet & rhs);

public:
    static ConferoNet * Instance();
    ~ConferoNet();

    unsigned int CreateSession();
    void SendMessage(const QString & msg, unsigned int key);
    void SendEdit(const unsigned char * data, size_t size, unsigned int key);
    void SendChat(const unsigned char * data, size_t size, const QString & host);
    void ConnectToHost(const QHostAddress & hostAddress, unsigned int key);
    void ConnectToHost(const QHostAddress & hostAddress);
    void JoinExistingSession(unsigned int key, const QHostAddress & hostAddress);

    void SetMessageReady(const QObject * receiver, const char * member);
    void SetNewSessionSlot(const QObject * receiver, const char * member);
    void SetStatusMessageSlot(const QObject * receiver, const char * member);
    void SetEditReadySlot(const QObject * receiver, const char * member);
};

#endif
