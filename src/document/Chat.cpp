#include "Chat.h"

Chat::Chat(QTabWidget * tabWidget, const QString & remoteName, ConferoNet * cnet)
: m_tabWidget(tabWidget), m_tab(0), m_display(0), m_enter(0), m_remoteName(remoteName),
    m_cnet(cnet), m_visible(true)
{
    m_tab = new QWidget();
    m_tab->setObjectName(m_remoteName);

    m_display = new QTextEdit(m_tab);
    m_display->setObjectName(m_remoteName + "_display");
    m_display->setGeometry(QRect(1, 1, 252, 198));
    m_display->setReadOnly(true);

    m_enter = new QLineEdit(m_tab);
    m_enter->setObjectName(m_remoteName + "_enter");
    m_enter->setGeometry(QRect(1, 201, 252, 20));

    m_tabWidget->addTab(m_tab, QString());
    m_tabWidget->setTabText(m_tabWidget->indexOf(m_tab), m_remoteName);

    connect(m_enter, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
}

void Chat::returnPressed()
{
    QString text(m_enter->text());
    m_display->append("You: " + text);
    m_enter->clear();
    SendEdit(text);
}

void Chat::SendEdit(const QString & text)
{
    Edit * ed = new Edit(text.toStdString().c_str(), text.length(), 0, 0, CHAT_MESSAGE, 0);
    size_t size = 0;
    const unsigned char * ptr = ed->GetData(size);
    m_cnet->SendChat(ptr, size, m_remoteName);
}

void Chat::AddChat(Edit * ed)
{
    QString text;
    text.reserve(ed->GetLength() + m_remoteName.size() + 5);
    text.append(m_remoteName);
    text.append(": ");

    char * data = ed->GetValue();
    int size = ed->GetLength();
    for(int i = 0; i < size; ++i)
    {
        text.append(data[i]);
    }

    m_display->append(text);
}

void Chat::Show()
{
    int index = m_tabWidget->indexOf(m_tab);
    if(index == -1)
    {
        m_tabWidget->addTab(m_tab, QString());
        index = m_tabWidget->indexOf(m_tab);
        m_tabWidget->setTabText(index, m_remoteName);
    }

    m_tabWidget->setCurrentIndex(index);

    m_visible = true;
}

void Chat::Hide()
{
    int index = m_tabWidget->indexOf(m_tab);
    if(index != -1)
    {
        m_tabWidget->removeTab(index);
    }

    m_visible = false;
}
