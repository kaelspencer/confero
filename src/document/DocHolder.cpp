#include "DocHolder.h"

DocHolder::DocHolder(QTabWidget * tabWidget, ConferoNet * cnet, unsigned int key)
: m_tabWidget(tabWidget), m_tab(0), m_sci(0), m_key(QString::number(key))
{
    m_tab = new QWidget();
    m_tab->setObjectName("tab_" + m_key);
    QsciScintilla * scintilla = new QsciScintilla(m_tab);
    scintilla->setObjectName("textEdit_" + m_key);
    scintilla->setGeometry(QRect(0, 0, SCI_DEFAULT_WIDTH, SCI_DEFAULT_LENGTH));
    scintilla->setMarginLineNumbers(QsciScintillaBase::SC_MARGIN_NUMBER, true);

    m_sci = new SciWrapper(scintilla, cnet, key);
}

DocHolder::DocHolder(QTabWidget * tabWidget, ConferoNet * cnet, unsigned int key,
                     QsciScintilla * scintilla, QWidget * tab)
 : m_tabWidget(tabWidget), m_tab(tab),
 m_sci(new SciWrapper(scintilla, cnet, key)), m_key(QString::number(key))
{
    scintilla->setMarginLineNumbers(QsciScintillaBase::SC_MARGIN_NUMBER, true);
}

DocHolder::~DocHolder()
{
    delete m_sci;
    delete m_tab;
}

void DocHolder::IntegrateEdit(Edit * ed)
{
    m_sci->integrateEdit(ed);
}

void DocHolder::Show() const
{
    int index = m_tabWidget->indexOf(m_tab);
    if(index == -1)
    {
        m_tabWidget->addTab(m_tab, QString());
        index = m_tabWidget->indexOf(m_tab);
        m_tabWidget->setTabText(index, m_key);
    }

    m_tabWidget->setCurrentIndex(index);
}

void DocHolder::Hide() const
{
    int index = m_tabWidget->indexOf(m_tab);
    if(index != -1)
    {
        m_tabWidget->removeTab(index);
    }
}

void DocHolder::SetLanguage(SciWrapper::Language language)
{
    m_sci->SetLanguage(language);
}
