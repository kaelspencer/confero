#include "SciWrapper.h"

QsciLexer ** SciWrapper::m_lexers = 0;

SciWrapper::SciWrapper(QsciScintilla * sci, ConferoNet * cnet, unsigned int key)
: m_sci(sci), m_cnet(cnet), m_key(key), m_doc(0), m_okToInsert(true)
{
    connect(m_sci, SIGNAL(SCN_MODIFIED(int, int, const char *, int, int, int, int, int, int, int)),
            this, SLOT(modified(int, int, const char *, int, int, int, int, int, int, int)));

    m_doc = new kDocument();
    InitLexers();
}

void SciWrapper::modified(int position, int type, const char * text, int length, int linesAdded,
                           int iline, int foldNow, int foldPrev, int token, int annotationLinesAdded)
{
    Q_UNUSED(linesAdded);
    Q_UNUSED(iline);
    Q_UNUSED(foldNow);
    Q_UNUSED(foldPrev);
    Q_UNUSED(token);
    Q_UNUSED(annotationLinesAdded);

    if(!m_okToInsert)
    {
        return;
    }

    if(type & SC_MOD_INSERTTEXT)
    {
        int line, index;
        m_doc->insertAt(position, *text, line, index);

        if(length > 1)
        {
            int templ = 0, tempi = 0;
            for(int i = 1; i < length; ++i)
            {
                m_doc->insertAt(position + i, *(text+i), templ, tempi);
            }
        }

        QString msg = QString(char(*text));
        msg.append(" (" + QString::number(line) + "," + QString::number(index) + ")");
        emit statusMessage(msg);

        Edit * ed = new Edit(text, length, line, index, type, m_key);
        size_t size;
        const unsigned char * ptr = ed->GetData(size);
        m_cnet->SendEdit(ptr, size, m_key);
    }
    else if(type & SC_MOD_DELETETEXT)
    {
        int line, index;
        m_doc->removeAt(position, line, index);

        Edit * ed = new Edit(0, 0, line, index, type, m_key);
        size_t size;
        const unsigned char * ptr = ed->GetData(size);
        m_cnet->SendEdit(ptr, size, m_key);
    }
}

void SciWrapper::integrateEdit(Edit * ed)
{
    QString msg;

    if(ed->GetType() & SC_MOD_INSERTTEXT)
    {
        int length = ed->GetLength();
        int line = ed->GetLine();
        int index = ed->GetIndex();
        char * val = ed->GetValue();

        QString str;
        str.reserve(length + 1);

        for(int i = 0; i < length; ++i)
        {
            m_doc->insertAt(line, index++, *(val+i));
            str.append(*(val+i));
        }

        m_okToInsert = false;
        m_sci->insertAt(str, ed->GetLine(), ed->GetIndex());
        m_okToInsert = true;

        msg = "Received edit: " + str + " (" + QString::number(ed->GetLine()) + "," +
            QString::number(ed->GetIndex()) + ")";
    }
    else if(ed->GetType() & SC_MOD_DELETETEXT)
    {
        msg = "Removing at (" + QString::number(ed->GetLine()) + "," +QString::number(ed->GetIndex()) + ")";
        m_doc->removeAt(ed->GetLine(), ed->GetIndex());

        //we need to check to see if the edit was before the current cursor position
        //if it is, then we need to adjust the new position.
        int line = 0, index = 0;
        m_okToInsert = false;
        m_sci->getCursorPosition(&line, &index);
        m_sci->setText(m_doc->Text());
        m_sci->setCursorPosition(line, index);
        m_okToInsert = true;
    }
    else
    {
        msg = "Received unrecognized edit";
    }

    emit statusMessage(msg);
}

void SciWrapper::SetLanguage(Language language)
{
    m_sci->setLexer(m_lexers[language]);
}

void SciWrapper::InitLexers()
{
    if(m_lexers == 0)
    {
        m_lexers = new QsciLexer * [None + 1];
        m_lexers[Bash] = new QsciLexerBash();
        m_lexers[Batch] = new QsciLexerBatch();
        m_lexers[CMake] = new QsciLexerCMake();
        m_lexers[CPP] = new QsciLexerCPP();
        m_lexers[CSHARP] = new QsciLexerCSharp();
        m_lexers[CSS] = new QsciLexerCSS();
        m_lexers[D] = new QsciLexerD();
        m_lexers[Diff] = new QsciLexerDiff();
        m_lexers[Fortran] = new QsciLexerFortran();
        m_lexers[Fortran77] = new QsciLexerFortran77();
        m_lexers[HTML] = new QsciLexerHTML();
        m_lexers[IDL] = new QsciLexerIDL();
        m_lexers[Java] = new QsciLexerJava();
        m_lexers[JavaScript] = new QsciLexerJavaScript();
        m_lexers[LUA] = new QsciLexerLua();
        m_lexers[MakeFile] = new QsciLexerMakefile();
        m_lexers[Pascal] = new QsciLexerPascal();
        m_lexers[Perl] = new QsciLexerPerl();
        m_lexers[PostScript] = new QsciLexerPostScript();
        m_lexers[POV] = new QsciLexerPOV();
        m_lexers[Properties] = new QsciLexerProperties();
        m_lexers[Python] = new QsciLexerPython();
        m_lexers[Ruby] = new QsciLexerRuby();
        m_lexers[Spice] = new QsciLexerSpice();
        m_lexers[SQL] = new QsciLexerSQL();
        m_lexers[TCL] = new QsciLexerTCL();
        m_lexers[TeX] = new QsciLexerTeX();
        m_lexers[Verilog] = new QsciLexerVerilog();
        m_lexers[VHDL] = new QsciLexerVHDL();
        m_lexers[XML] = new QsciLexerXML();
        m_lexers[YAML] = new QsciLexerYAML();
        m_lexers[None] = 0;
    }
}
