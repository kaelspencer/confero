#include "NetClient.h"

NetClient::NetClient(const QHostAddress & hostAddress, quint16 port)
: m_socket(0), m_host(hostAddress), m_port(port)
{
    m_socket = new QTcpSocket();
}

NetClient::NetClient(QTcpSocket * socket)
: m_socket(socket), m_host(socket->peerAddress()), m_port(socket->peerPort())
{

}

NetClient::~NetClient()
{
    if( m_socket )
    {
        m_socket->abort();
        delete m_socket;
        m_socket = 0;
    }
}

bool NetClient::IsConnected() const
{
    return m_socket->state() == QAbstractSocket::ConnectedState;
}

void NetClient::Connect()
{
    if(!IsConnected())
    {
        m_socket->abort();
        m_socket->connectToHost(m_host, m_port);
    }
}

void NetClient::ConnectSocketRead(const QObject * parent, const char * member)
{
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(Read()));
    connect(this, SIGNAL(dataReady(const QString &)), parent, member);
}

void NetClient::ConnectNewSessionSlot(const QObject * parent, const char * member)
{
    connect(this, SIGNAL(newSession(unsigned int, const QString &)), parent, member);
}

void NetClient::ConnectStatusMessageSlot(const QObject * parent, const char * member)
{
    connect(this, SIGNAL(statusMessage(const QString &)), parent, member);
}

void NetClient::ConnectEditReadySlot(const QObject * parent, const char * member)
{
    connect(this, SIGNAL(editReady(const char *, size_t, const QString &)), parent, member);
}

void NetClient::Write(const QByteArray & block)
{
    WriteRawData(block.constData(), (unsigned short) block.size());
}

void NetClient::WriteRawData(const char * data, unsigned short size)
{
    m_socket->write(data, size);
}

void NetClient::WritePacket(const Packet * pkt)
{
    unsigned short size = 0;
    const char * data = pkt->Data(size);
    WriteRawData(data, size);
}

void NetClient::Read()
{
    qint64 bytesAvailable = m_socket->bytesAvailable();
    char * data = new char[bytesAvailable + 1];
    qint64 bytesRead = m_socket->read(data, bytesAvailable + 1);

    if(bytesRead > 0)
    {
        PacketPump(data, bytesRead);
    }
}

void NetClient::PacketPump(const char * data, qint64 size)
{
    qint64 bused = 0;
    qint64 temp = 0;
    SessionManager * sm = SessionManager::Instance();

    while(size - bused > 0)
    {
        temp = ParsePacket(data + bused, sm);
        bused += temp;

        if(temp == -1)
        {
            //something happened
            return;
        }
    }
}

qint64 NetClient::ParsePacket(const char * data, SessionManager * sm)
{
    qint64 bused = 0;
    const Header * hdr = reinterpret_cast<const Header *> (data);
    bused += sizeof(Header);

    const char * payload = (char*) hdr + sizeof(Header);

    switch((unsigned short)hdr->type)
    {
        case SESSIONHOST:
        {
            const SessionHosts * sh = reinterpret_cast<const SessionHosts *> (payload);
            bused += sizeof(SessionHosts);

            const quint32 * ip = 0;
            for(unsigned short i = 0; i < sh->hostCount; ++i)
            {
                ip = reinterpret_cast<const quint32 *> (sh + sizeof(SessionHosts) + i);
                bused += sizeof(unsigned short);
                sm->ConnectAndJoin(QHostAddress(*ip), sh->key);
                sm->AddHostToSession(sh->key, HostID(QHostAddress(*ip)));
            }
            break;
        }
        case SESSIONJOIN:
        {
            const SessionJoin * sj = reinterpret_cast<const SessionJoin *> (payload);
            bused += sizeof(SessionJoin);
            sm->AddHostToSession(sj->key, HostID(m_host));

            break;
        }
        case SESSIONOFFER:
        {
            //TODO: Investigate why this is commented out.
            //I don't remember why this was commented out.
            //const SessionJoin * sj = reinterpret_cast<const SessionJoin *> (payload);
            bused += sizeof(SessionJoin);
            //sm->JoinExistingSession(sj->key, HostID(m_host));

            //QString str("Received session offer: " + QString::number(sj->key));
            //emit statusMessage(str);

            break;
        }
        case SESSIONREQUEST:
        {
            SendKeys();
            break;
        }
        case SESSIONS:
        {
            const Sessions * ss = reinterpret_cast<const Sessions *> (payload);
            bused += HandleKeys(ss);
            SendKeys(true);

            break;
        }
        case SESSIONCOURTESY:
        {
            const Sessions * ss = reinterpret_cast<const Sessions *> (payload);
            bused += HandleKeys(ss);

            break;
        }
        case MESSAGE:
        {
            const Message * msg = reinterpret_cast<const Message *> (payload);
            bused += sizeof(Message);
            QString str = m_socket->peerAddress().toString() + ": " + QString::fromAscii(reinterpret_cast<const char *>
                ((char*)msg + sizeof(Message)), msg->length);
            bused += msg->length;
            emit dataReady(str);
            break;
        }
        case EDIT:
        {
            const EditStruct * ed = reinterpret_cast<const EditStruct *> (payload);
            bused += sizeof(EditStruct);
            char * data = new char[ed->size];

            memcpy(data, ((char*)ed) + sizeof(ed), ed->size);
            bused += ed->size;

            emit editReady(data, ed->size, m_host.toString());

            break;
        }
        default:
            bused = -1;
            break;
    }

    return bused;
}

void NetClient::SendKeys(bool courtesy)
{
    QList<unsigned int> keys(SessionManager::Instance()->GetKeys());

    Header hdr;

    if(courtesy)
    {
        hdr.type = SESSIONCOURTESY;
    }
    else
    {
        hdr.type = SESSIONS;
    }

    Sessions ss;
    ss.count = keys.count();

    Packet * pkt = new Packet();
    pkt->Add((char*) &hdr, sizeof(Header));
    pkt->Add((char*) &ss, sizeof(Sessions));

    foreach(unsigned int key, keys)
    {
        pkt->Add((char*) &key, sizeof(key));
    }

    WritePacket(pkt);
    delete pkt;
}

void NetClient::SendSessionJoin(unsigned int key)
{
    Header hdr;
    hdr.type = SESSIONJOIN;
    SessionJoin sj;
    sj.key = key;

    Packet * pkt = new Packet();
    pkt->Add((char*) &hdr, sizeof(Header));
    pkt->Add((char*) &sj, sizeof(SessionJoin));

    this->WritePacket(pkt);

    delete pkt;
}

qint64 NetClient::HandleKeys(const Sessions * ss)
{
    qint64 bused = 0;
    bused += sizeof(Sessions);
    const unsigned int * key = reinterpret_cast<const unsigned int *>
        ((char*)ss + sizeof(Sessions));
    QString host(m_host.toString());

    for(unsigned short i = 0; i < ss->count; ++i, ++key)
    {
        bused += sizeof(unsigned int);
        if(*key)
        {
            emit newSession(*key, host);
        }
    }

    return bused;
}
