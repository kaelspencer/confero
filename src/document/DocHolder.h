#ifndef DOCHOLDER_H
#define DOCHOLDER_H

#include <QtGui/QTabWidget>
#include <QtGui/QWidget>
#include <Qsci/qsciscintilla.h>
#include "SciWrapper.h"
#include "../net/ConferoNet.h"

const int SCI_DEFAULT_WIDTH = 761;
const int SCI_DEFAULT_LENGTH = 508;

class DocHolder
{
private:
    QTabWidget	* m_tabWidget;
    QWidget		* m_tab;
    SciWrapper	* m_sci;
    QString		  m_key;

public:
    DocHolder(QTabWidget * tabWidget, ConferoNet * cnet, unsigned int key);
    DocHolder(QTabWidget * tabWidget, ConferoNet * cnet, unsigned int key,
            QsciScintilla * scintilla, QWidget * tab);
    ~DocHolder();

    void IntegrateEdit(Edit * ed);
    void Show() const;
    void Hide() const;
    void SetLanguage(SciWrapper::Language language);
};

#endif
