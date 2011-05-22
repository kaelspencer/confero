#include "DocumentManager.h"

DocumentManager::DocumentManager(QTabWidget * tabWidget, QTabWidget * chatTab,
                                 QTreeWidget * treeWidget, ConferoNet * cnet,
                                 const QString & localHostName)
: m_tabWidget(tabWidget), m_chatTab(chatTab), m_treeWidget(treeWidget), m_cnet(cnet),
  m_localHostName(localHostName), m_hostKeys(0), m_docs(0), m_chats(0)
{
    m_hostKeys = new QMap<QString, QList<unsigned int> *>();
    m_docs = new QMap<unsigned int, DocHolder *>();
    m_chats = new QMap<QString, Chat *>();

    cnet->SetEditReadySlot(this, SLOT(handleEdit(const char *, size_t, const QString &)));
    connect(m_treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)),
            this, SLOT(itemDoubleClicked(QTreeWidgetItem *, int)));
    connect(tabWidget, SIGNAL(tabCloseRequested(int)),
            this, SLOT(tabCloseRequested(int)));
    connect(m_chatTab, SIGNAL(tabCloseRequested(int)),
            this, SLOT(chatTabCloseRequested(int)));
}

DocumentManager::~DocumentManager()
{
    delete m_hostKeys;

    QMapIterator<unsigned int, DocHolder *> itor(*m_docs);

    while(itor.hasNext())
    {
        itor.next();
        delete itor.value();
    }

    delete m_docs;
}

void DocumentManager::AddExisting(QsciScintilla * scintilla, QWidget * tab,
                                  unsigned int key, const QString & host)
{
    if(!m_docs->contains(key))
    {
        DocHolder * pdh = new DocHolder(m_tabWidget, m_cnet, key, scintilla, tab);
        AddKey(key, host);
        m_docs->insert(key, pdh);
        UpdateTreeWidget();
    }
}

void DocumentManager::Add(unsigned int key, const QString & host, bool show)
{
    if(!m_docs->contains(key))
    {
        DocHolder * pdh = new DocHolder(m_tabWidget, m_cnet, key);
        AddKey(key, host);
        m_docs->insert(key, pdh);
        UpdateTreeWidget();

        if(host != "local" && !m_chats->contains(host))
        {
            m_chats->insert(host, new Chat(m_chatTab, host, m_cnet));
        }
    }
    else
    {
        m_cnet->JoinExistingSession(key, QHostAddress(host));
    }

    if(show)
    {
        m_docs->value(key)->Show();
    }
}

bool DocumentManager::AddKey(unsigned int key, const QString & host)
{
    bool val = false;

    if(m_hostKeys->contains(host))
    {
        QList<unsigned int> * plkeys = m_hostKeys->value(host);
        if(!plkeys->contains(key))
        {
            plkeys->append(key);
            val = true;
        }
    }
    else
    {
        QList<unsigned int> * plkeys = new QList<unsigned int>();
        plkeys->append(key);
        m_hostKeys->insert(host, plkeys);
        val = true;
    }

    if(host != m_localHostName)
    {
        QHostAddress had(host);
        m_cnet->JoinExistingSession(key, had);
    }

    return val;
}

void DocumentManager::handleEdit(const char * data, size_t size, const QString & sender)
{
    Edit * ed = new Edit(data, size);

    if(ed->GetType() == CHAT_MESSAGE)
    {
        if(m_chats->contains(sender))
        {
            m_chats->value(sender)->AddChat(ed);
        }
    }
    else if(m_docs->contains(ed->GetKey()))
    {
        m_docs->value(ed->GetKey())->IntegrateEdit(ed);
    }

    delete ed;
}

void DocumentManager::UpdateTreeWidget()
{
    QList<QTreeWidgetItem *> items;
    items.append(new QTreeWidgetItem((QTreeWidget*)0, QStringList(NEW_CONNECTION_STRING)));

    QMapIterator<QString, QList<unsigned int> *> mitor(*m_hostKeys);

    while(mitor.hasNext())
    {
        mitor.next();
        QTreeWidgetItem * parent = new QTreeWidgetItem((QTreeWidgetItem*)0, QStringList(mitor.key()));
        items.append(parent);

        QListIterator<unsigned int> itor(*mitor.value());
        while(itor.hasNext())
        {
            items.append(new QTreeWidgetItem(parent, QStringList(QString::number(itor.next()))));
        }
    }

    m_treeWidget->clear();
    m_treeWidget->insertTopLevelItems(0, items);
}

void DocumentManager::itemDoubleClicked(QTreeWidgetItem * item, int column)
{
    Q_UNUSED(column);

    if(item->text(0) == NEW_CONNECTION_STRING)
    {
        QDialog dialog;
        Ui_ip uiip;
        uiip.setupUi(&dialog);

        if(dialog.exec())
        {
            m_cnet->ConnectToHost(QHostAddress(uiip.lineEdit->text()));
        }
    }
    else if(item->childCount() == 0)
    {
        int key = item->text(0).toInt();
        if(m_docs->contains(key))
        {
            m_docs->value(key)->Show();
        }
    }
}

void DocumentManager::tabCloseRequested(int index)
{
    m_tabWidget->removeTab(index);
}

void DocumentManager::chatTabCloseRequested(int index)
{
    QString title = m_chatTab->tabText(index);
    if(m_chats->contains(title))
    {
        m_chats->value(title)->Hide();
    }
}

void DocumentManager::SetLanguage(SciWrapper::Language language)
{
    unsigned int key = m_tabWidget->tabText(m_tabWidget->currentIndex()).toInt();

    if(m_docs->contains(key))
    {
        m_docs->value(key)->SetLanguage(language);
    }
}
