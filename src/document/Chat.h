#ifndef CHAT_H
#define CHAT_H

#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QLineEdit>
#include <Qsci/qsciscintilla.h>
#include "Edit.h"
#include "../net/ConferoNet.h"

extern const int SC_MOD_INSERTTEXT;

class Chat : public QObject
{
    Q_OBJECT

private:
    QTabWidget * m_tabWidget;
    QWidget * m_tab;
    QTextEdit * m_display;
    QLineEdit * m_enter;
    //this is used as the host
    QString m_remoteName;
    ConferoNet * m_cnet;
    bool m_visible;

    Chat();
    Chat(const Chat & rhs);
    Chat & operator=(const Chat & rhs);

    void SendEdit(const QString & text);

private slots:
    void returnPressed();

public:
    Chat(QTabWidget * tabWidget, const QString & remoteName, ConferoNet * cnet);
    void AddChat(Edit * ed);
    void Show();
    void Hide();
};

#endif
