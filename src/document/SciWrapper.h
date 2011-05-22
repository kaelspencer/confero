#ifndef SCIWRAPPER_H
#define SCIWRAPPER_H

#include <Qsci/qsciscintilla.h>
#include "../net/ConferoNet.h"
#include "Edit.h"
#include "Document.h"

#include <Qsci/qscilexer.h>
#include <Qsci/qscilexerbash.h>
#include <Qsci/qscilexerbatch.h>
#include <Qsci/qscilexercmake.h>
#include <Qsci/qscilexercpp.h>
#include <Qsci/qscilexercsharp.h>
#include <Qsci/qscilexercss.h>
#include <Qsci/qscilexerd.h>
#include <Qsci/qscilexerdiff.h>
#include <Qsci/qscilexerfortran.h>
#include <Qsci/qscilexerfortran77.h>
#include <Qsci/qscilexerhtml.h>
#include <Qsci/qscilexeridl.h>
#include <Qsci/qscilexerjava.h>
#include <Qsci/qscilexerjavascript.h>
#include <Qsci/qscilexerlua.h>
#include <Qsci/qscilexermakefile.h>
#include <Qsci/qscilexerpascal.h>
#include <Qsci/qscilexerperl.h>
#include <Qsci/qscilexerpostscript.h>
#include <Qsci/qscilexerpov.h>
#include <Qsci/qscilexerproperties.h>
#include <Qsci/qscilexerpython.h>
#include <Qsci/qscilexerruby.h>
#include <Qsci/qscilexerspice.h>
#include <Qsci/qscilexersql.h>
#include <Qsci/qscilexertcl.h>
#include <Qsci/qscilexertex.h>
#include <Qsci/qscilexerverilog.h>
#include <Qsci/qscilexervhdl.h>
#include <Qsci/qscilexerxml.h>
#include <Qsci/qscilexeryaml.h>

extern const int SC_MOD_INSERTTEXT;
extern const int SC_MOD_DELETETEXT;

class SciWrapper : public QObject
{
    Q_OBJECT

private:
    static QsciLexer ** m_lexers;
    QsciScintilla * m_sci;
    ConferoNet	  * m_cnet;
    unsigned int    m_key;
    kDocument	  * m_doc;
    bool			m_okToInsert;

    SciWrapper();
    SciWrapper & operator=(const SciWrapper & rhs);
    SciWrapper(const SciWrapper & rhs);
    void InitLexers();

private slots:
    void modified(int, int, const char *, int, int, int, int, int, int, int);

public:
    enum Language {Bash, Batch, CMake, CPP, CSHARP, CSS, D, Diff, Fortran, Fortran77,
        HTML, IDL, Java, JavaScript, LUA, MakeFile, Pascal, Perl, PostScript,
        POV, Properties, Python, Ruby, Spice, SQL, TCL, TeX, Verilog,
        VHDL, XML, YAML, None};

    SciWrapper(QsciScintilla * sci, ConferoNet * cnet, unsigned int key);
    ~SciWrapper() {};

    void integrateEdit(Edit * ed);
    void SetLanguage(Language language);

signals:
    void statusMessage(const QString & msg);
};

#endif
