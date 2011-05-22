#include "confero.h"

Confero::Confero(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags), cnet(0), m_docman(0), m_localHostName("local")
{
    ui.setupUi(this);

    ui.tabWidget->removeTab(1);
    ui.treeWidget->setColumnCount(1);

    ui.tabWidget_2->removeTab(0);
    ui.tabWidget_2->removeTab(0);

    connect(ui.actionQuit, SIGNAL(triggered()), this, SLOT(exitApplication()));
    connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(createNew()));

    cnet = ConferoNet::Instance();
    unsigned int key = cnet->CreateSession();
    ui.tabWidget->setTabText(ui.tabWidget->indexOf(ui.tab), QString::number(key));

    cnet->SetMessageReady(this, SLOT(statusMessage(const QString &)));
    cnet->SetNewSessionSlot(this, SLOT(newSession(unsigned int, const QString &)));
    cnet->SetStatusMessageSlot(this, SLOT(statusMessage(const QString &)));

    m_docman = new DocumentManager(ui.tabWidget, ui.tabWidget_2, ui.treeWidget, cnet, m_localHostName);
    connect(m_docman, SIGNAL(statusMessage(const QString &)), this, SLOT(statusMessage(const QString &)));
    m_docman->AddExisting(ui.textEdit, ui.tab, key, m_localHostName);

    ConnectLanguages();
}

void Confero::statusMessage(const QString & msg)
{
    ui.statusBar->showMessage(msg);
}

void Confero::newSession(unsigned int key, const QString & host)
{
    QString msg = "New session offer: " + QString::number(key);
    statusMessage(msg);
    m_docman->Add(key, host);
}

Confero::~Confero()
{
}

void Confero::exitApplication()
{
    qApp->exit(0);
}

void Confero::createNew()
{
    unsigned int key = cnet->CreateSession();
    m_docman->Add(key, m_localHostName, true);
}

void Confero::handleLanguage()
{
    QAction * sender = reinterpret_cast<QAction *> (QObject::sender());
    SciWrapper::Language lang(SciWrapper::None);
    QString text(sender->text());

    if(text == "Bash") {
        lang = SciWrapper::Bash;
    } else if(text == "Batch") {
        lang = SciWrapper::Batch;
    } else if(text == "CMake") {
        lang = SciWrapper::CMake;
    } else if(text == "C++") {
        lang = SciWrapper::CPP;
    } else if(text == "C#") {
        lang = SciWrapper::CSHARP;
    } else if(text == "CSS") {
        lang = SciWrapper::CSS;
    } else if(text == "D") {
        lang = SciWrapper::D;
    } else if(text == "Diff") {
        lang = SciWrapper::Diff;
    } else if(text == "Fortran") {
        lang = SciWrapper::Fortran;
    } else if(text == "Fortran77") {
        lang = SciWrapper::Fortran77;
    } else if(text == "HTML") {
        lang = SciWrapper::HTML;
    } else if(text == "IDL") {
        lang = SciWrapper::IDL;
    } else if(text == "Java") {
        lang = SciWrapper::Java;
    } else if(text == "JavaScript") {
        lang = SciWrapper::JavaScript;
    } else if(text == "LUA") {
        lang = SciWrapper::LUA;
    } else if(text == "MakeFile") {
        lang = SciWrapper::MakeFile;
    } else if(text == "Pascal") {
        lang = SciWrapper::Pascal;
    } else if(text == "Perl") {
        lang = SciWrapper::Perl;
    } else if(text == "PostScript") {
        lang = SciWrapper::PostScript;
    } else if(text == "POV") {
        lang = SciWrapper::POV;
    } else if(text == "Properties") {
        lang = SciWrapper::Properties;
    } else if(text == "Python") {
        lang = SciWrapper::Python;
    } else if(text == "Ruby") {
        lang = SciWrapper::Ruby;
    } else if(text == "Spice") {
        lang = SciWrapper::Spice;
    } else if(text == "SQL") {
        lang = SciWrapper::SQL;
    } else if(text == "TCL") {
        lang = SciWrapper::TCL;
    } else if(text == "TeX") {
        lang = SciWrapper::TeX;
    } else if(text == "Verilog") {
        lang = SciWrapper::Verilog;
    } else if(text == "VHDL") {
        lang = SciWrapper::VHDL;
    } else if(text == "XML") {
        lang = SciWrapper::XML;
    } else if(text == "YAML") {
        lang = SciWrapper::YAML;
    }

    m_docman->SetLanguage(lang);
}

void Confero::ConnectLanguages()
{
    connect(ui.actionBash, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionBatch, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionCMake, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionC, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionC_2, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionCSS, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionD, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionDiff, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionFortran, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionFortran77, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionHTML, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionIDL, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionJava, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionJavaScript, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionLua, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionMakefile, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionPascal, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionPerl, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionPostScript, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionPOV, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionProperties, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionPython, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionRuby, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionSpice, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionSQL, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionTCL, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionTeX, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionVerilog, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionVHDL, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionXML, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionYAML, SIGNAL(triggered()), this, SLOT(handleLanguage()));
    connect(ui.actionNone, SIGNAL(triggered()), this, SLOT(handleLanguage()));
}
