#include "ConferoNet.h"

ConferoNet * ConferoNet::m_inst = 0;

ConferoNet::ConferoNet()
: m_sm(SessionManager::Instance())
{

}

ConferoNet * ConferoNet::Instance()
{
    if(m_inst == 0)
    {
        m_inst = new ConferoNet;
    }

    return m_inst;
}

unsigned int ConferoNet::CreateSession()
{
    return m_sm->CreateSession();
}

void ConferoNet::SendMessage(const QString & msg, unsigned int key)
{
    m_sm->SendMessage(msg, key);
}

void ConferoNet::SendEdit(const unsigned char * data, size_t size, unsigned int key)
{
    m_sm->SendEdit(data, size, key);
}

void ConferoNet::SendChat(const unsigned char * data, size_t size, const QString & host)
{
    m_sm->SendChat(data, size, host);
}

void ConferoNet::SetMessageReady(const QObject * receiver, const char * member)
{
    m_sm->SetMessageReady(receiver, member);
}

void ConferoNet::SetNewSessionSlot(const QObject * receiver, const char * member)
{
    m_sm->SetNewSessionSlot(receiver, member);
}

void ConferoNet::SetStatusMessageSlot(const QObject * receiver, const char * member)
{
    m_sm->SetStatusMessageSlot(receiver, member);
}

void ConferoNet::SetEditReadySlot(const QObject * receiver, const char * member)
{
    m_sm->SetEditReadySlot(receiver, member);
}

void ConferoNet::ConnectToHost(const QHostAddress & hostAddress, unsigned int key)
{
    m_sm->ConnectToHost(hostAddress, key);
}

void ConferoNet::ConnectToHost(const QHostAddress & hostAddress)
{
    m_sm->ConnectToHost(hostAddress);
}

void ConferoNet::JoinExistingSession(unsigned int key, const QHostAddress & hostAddress)
{
    HostID hid(hostAddress);
    m_sm->JoinExistingSession(key, hid);
}
