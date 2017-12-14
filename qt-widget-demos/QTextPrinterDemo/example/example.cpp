#include <QTextEdit>
#include <QMenuBar>
#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

#include "example.h"
#include "textprinter.h"

QString headertext = 
    "<table width=\"100%\">"
    "  <tr>"
    "    <td align=\"left\"><strong>%1</strong></td>"
    "    <td align=\"right\"><strong>&date;</strong></td>"
    "  </tr>"
    "</table>";

QString footertext = "<p align=\"right\"><strong>&page;</strong></p>";

Example::Example()
{
    editor = new QTextEdit;
    setCentralWidget(editor);

    m_pTextPrinter = new TextPrinter(this);
    m_pTextPrinter->setHeaderSize(10);
    m_pTextPrinter->setFooterSize(10);
    m_pTextPrinter->setDateFormat("MMMM dd yyyy");

    filemenu = menuBar()->addMenu("&File");

    filemenu->addAction("&New", this, SLOT(newFile()));
    filemenu->addAction("&Open...", this, SLOT(open()));
    filemenu->addAction("&Save", this, SLOT(save()));
    filemenu->addAction("Save &As...", this, SLOT(saveAs()));
    filemenu->addSeparator();
    filemenu->addAction("&Print...", this, SLOT(print()));
    filemenu->addAction("Pre&view...", this, SLOT(preview()));
    filemenu->addAction("&Export to PDF...", this, SLOT(exportPdf()));

    filemenu->addSeparator();
    filemenu->addAction("E&xit", this, SLOT(close()));

    connect(editor->document(), SIGNAL(contentsChanged()),
            this, SLOT(documentModified()));

    currentFile = QString();
    html = false;
    setWindowTitle("[*]Example");
    setWindowModified(false);
}

void Example::closeEvent(QCloseEvent *event)
{
    if (askSave())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void Example::newFile()
{
    if (askSave())
    {
        editor->clear();
        currentFile = QString();
        setWindowModified(false);
    }
}

void Example::open()
{
    if (askSave())
    {
        QString filename = QFileDialog::getOpenFileName(this);
        if (!filename.isEmpty())
        {
            loadFile(filename);
        }
    }
}

bool Example::save()
{
    if (currentFile.isEmpty()) return saveAs();
    else return saveFile(currentFile);
}

bool Example::saveAs()
{
    QString filename = QFileDialog::getSaveFileName(this);
    if (filename.isEmpty())
    {
        return false;
    }

    return saveFile(filename);
}

void Example::print()
{
    m_pTextPrinter->setHeaderText(headertext.arg(currentFile));
    m_pTextPrinter->setFooterText(footertext);
    m_pTextPrinter->print(editor->document(), "Example Print");
}

void Example::preview()
{
    m_pTextPrinter->setHeaderText(headertext.arg(currentFile));
    m_pTextPrinter->setFooterText(footertext);
    m_pTextPrinter->preview(editor->document(), "Example Print");
}

void Example::exportPdf()
{
    m_pTextPrinter->setHeaderText(headertext.arg(currentFile));
    m_pTextPrinter->setFooterText(footertext);
    m_pTextPrinter->exportPdf(editor->document(), "Example Print");
}

void Example::documentModified()
{
    setWindowModified(editor->document()->isModified());
}

bool Example::askSave()
{
    if (editor->document()->isModified())
    {
        QMessageBox::StandardButton result;
        result = QMessageBox::warning(this, "Example", "Save changes?",
                                      QMessageBox::Save |
                                      QMessageBox::Discard |
                                      QMessageBox::Cancel);
        if (result == QMessageBox::Save)
        {
            return save();
        }
        else if (result == QMessageBox::Cancel)
        {
            return false;
        }
    }
    return true;
}

void Example::loadFile(const QString &filename)
{
    QFile file(filename);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Example", "Cannot read file");
        return;
    }

    QByteArray text = file.readAll();
    if (Qt::mightBeRichText(text))
    {
        editor->setHtml(text);
        html = true;
    }
    else
    {
        editor->setPlainText(text);
        html = false;;
    }

    currentFile = filename;
    setWindowModified(false);
}

bool Example::saveFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Example", "Cannot write file");
        return false;
    }

    QTextStream outstream(&file);
    if (html)
    {
        outstream << editor->document()->toHtml();
    }
    else
    {
        outstream << editor->document()->toPlainText();
    }

    currentFile = filename;
    setWindowModified(false);
    return true;
}
