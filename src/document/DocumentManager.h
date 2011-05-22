#ifndef DOCUMENTMANAGER_H
#define DOCUMENTMANAGER_H

#include <QMap>
#include <QtGui/QTabWidget>
#include <QtGui/QTreeWidget>
#include "DocHolder.h"
#include "Chat.h"
#include "../net/ConferoNet.h"
#include "ui_ip.h"

const QString NEW_CONNECTION_STRING("<new connection>");

class DocumentManager : public QObject
{
    Q_OBJECT

private:
    QTabWidget * m_tabWidget;
    QTabWidget * m_chatTab;
    QTreeWidget * m_treeWidget;
    ConferoNet * m_cnet;
    QString m_localHostName;
    QMap<QString, QList<unsigned int> *> * m_hostKeys;
    QMap<unsigned int, DocHolder *> * m_docs;
    QMap<QString, Chat *> * m_chats;

    bool AddKey(unsigned int key, const QString & host);
    void UpdateTreeWidget();

private slots:
    void handleEdit(const char * data, size_t size, const QString & sender);
    void itemDoubleClicked(QTreeWidgetItem * item, int column);
    void tabCloseRequested(int index);
    void chatTabCloseRequested(int index);

public:
    DocumentManager(QTabWidget * tabWidget, QTabWidget * chatTab,
        QTreeWidget * treeWidget, ConferoNet * cnet, const QString & localHostName);
    ~DocumentManager();

    void AddExisting(QsciScintilla * scintilla, QWidget * tab, unsigned int key, const QString & host);
    void Add(unsigned int key, const QString & host, bool show = false);
    void SetLanguage(SciWrapper::Language language);

signals:
    void statusMessage(const QString &);
};

#endif
