#ifndef CONFERO_H
#define CONFERO_H

#include <QtGui/QMainWindow>
#include <QHostAddress>
#include <QMessageBox>
#include <QMap>
#include "ui_confero.h"
#include "net/ConferoNet.h"

#include "document/SciWrapper.h"
#include "document/DocumentManager.h"

class Confero : public QMainWindow
{
    Q_OBJECT

public:
    Confero(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~Confero();

private:
    Ui::ConferoClass ui;
    ConferoNet * cnet;
    DocumentManager * m_docman;

    const QString m_localHostName;

    void ConnectLanguages();

private slots:
    void statusMessage(const QString & msg);
    void newSession(unsigned int key, const QString & host);
    void exitApplication();
    void createNew();
    void handleLanguage();
};

#endif // CONFERO_H
