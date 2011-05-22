#include "NetServer.h"

NetServer::NetServer(quint16 port, const NetManager * parent)
: m_server(0), m_port(port), m_parent(parent)
{
    m_server = new QTcpServer();
}

NetServer::~NetServer()
{
    if(m_server)
    {
        m_server->close();
        delete m_server;
        m_server = 0;
    }
}

void NetServer::Listen()
{
    m_server->listen(QHostAddress::Any, m_port);

    connect(m_server, SIGNAL(newConnection()),
        reinterpret_cast<const QObject *> (m_parent), SLOT(OnServerConnection()));
}

NetClient * NetServer::OnConnection() const
{
    QTcpSocket * clientSocket = m_server->nextPendingConnection();
    //hopefully this doesn't do some funny things
    connect(clientSocket, SIGNAL(disconnected()), clientSocket, SLOT(deleteLater()));

    return new NetClient(clientSocket);
}
