#include <QMenuBar>
#include <QTextEdit>
#include <QSettings>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>

#include "mainwindow.h"

MainWindow::MainWindow()
{
    setAttribute(Qt::WA_DeleteOnClose);

    textEdit = new QTextEdit;
    setCentralWidget(textEdit);

    createActions();
    createMenus();

    setWindowFilePath(QString());
    resize(400, 300);
}

MainWindow::~MainWindow()
{
    QSettings settings;
    settings.setValue("recentFiles", recentFilesMenu->saveState());
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this);

    if (!fileName.isEmpty())
    {
        loadFile(fileName);
    }
}

void MainWindow::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);

    recentFilesMenu = new QRecentFilesMenu(tr("Recent Files"), fileMenu);

    QSettings settings;
    recentFilesMenu->restoreState(settings.value("recentFiles").toByteArray());

    connect(recentFilesMenu, SIGNAL(recentFileTriggered(const QString &)), this, SLOT(loadFile(const QString &)));

    fileMenu->addMenu(recentFilesMenu);

    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
}

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Recent Files"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    textEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();

    setWindowFilePath(fileName);

    recentFilesMenu->addRecentFile(fileName);
}
