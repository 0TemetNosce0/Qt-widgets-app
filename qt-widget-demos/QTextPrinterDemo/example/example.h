#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QMainWindow>

class QAction;
class QMenu;
class QTextEdit;
class TextPrinter;

class Example : public QMainWindow
{
    Q_OBJECT
public:
    Example();

public slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void print();
    void preview();
    void exportPdf();
    void documentModified();

private:
    void closeEvent(QCloseEvent *event);
    bool askSave();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);

private:
    QTextEdit *editor;
    TextPrinter *m_pTextPrinter;
    QMenu *filemenu;
    QString currentFile;
    bool html;
};

#endif
