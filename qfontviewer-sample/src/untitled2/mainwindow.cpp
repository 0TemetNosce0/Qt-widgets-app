#include "mainwindow.h"
#include "settingsdialog.h"
#include <QMessageBox>
#include <QSettings>
#include <QFileDialog>
#include <QFile>
#include <QMimeData>
#include <QRegExpValidator>
#include <QUrl>

class SettingsDialog;

QRegExp MainWindow::unicodeRegExp = QRegExp("^u\\+([0-9a-f]{4,})", Qt::CaseInsensitive);
//QRegExp MainWindow::utf8RegExp = QRegExp("(0x[0-9a-f]*( |))*", Qt::CaseInsensitive);

MainWindow::MainWindow(const QStringList & args, QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    clipboard = QApplication::clipboard();
    setValidators();

    setWindowTitle(QString("%1 %2").arg(qApp->applicationName(),
                                        qApp->applicationVersion()));
    fontBold->setFixedWidth(fontBold->height());
    fontItalic->setFixedWidth(fontItalic->height());

    // initializing subsets
    QList<QFontDatabase::WritingSystem> writingSystems = \
        fontDatabase.writingSystems();
    for (int i = 0; i < writingSystems.size(); ++i)
        subsets->addItem(QFontDatabase::writingSystemName(writingSystems[i]),
                         writingSystems[i]);

    connect(this, SIGNAL(jobDoneSignal()),
            this, SLOT(jobDone()), Qt::QueuedConnection);

    updateFontList();
    loadSettings();
    processArgs(args);
    makePangram();
    updateInfo();
    fontFilter->setFocus();
}

MainWindow::~MainWindow()
{
}

void MainWindow::processArgs(const QStringList & args)
{
    for (int i = 1; i < args.size(); ++i) {
        if (args[i] == QString("-b") || args[i] == QString("--bold"))
            setFontBold(true);
        else if (args[i] == QString("-B") || args[i] == QString("--no-bold"))
            setFontBold(false);
        else if (args[i] == QString("-c") || args[i] == QString("--chars"))
            tabWidget->setCurrentIndex(1);
        else if (args[i] == QString("-i") || args[i] == QString("--italic"))
            setFontItalic(true);
        else if (args[i] == QString("-I") || args[i] == QString("--no-italic"))
            setFontItalic(false);
        else if (args[i] == QString("-p") || args[i] == QString("--pangram"))
            tabWidget->setCurrentIndex(0);
        else {
            QStringList fonts(fontDatabase.families());
            if (fonts.indexOf(args[i]) != -1)
                setFontFamily(args[i]);
            else
                setFontFromFile(args[i]);
        }
    }
}

void MainWindow::setValidators()
{
    codeSearch->setValidator(new QRegExpValidator(
        //QRegExp("(^u\\+[0-9a-f]{4,}|(0x[0-9a-f]*( |))*|[0-9]*)",
        QRegExp("(^u\\+[0-9a-f]{4,})",
                Qt::CaseInsensitive), this));

    fontSize->setValidator(new QRegExpValidator(QRegExp("^([0-9]{1,})"), this));
}

void MainWindow::loadSettings(bool reload)
{
    QSettings s(qApp->applicationName());

    QVariant autoFontMerge = s.value("autoFontMerge");
    if (autoFontMerge.isValid())
        setFontAutoMerging(autoFontMerge.toBool());

    QVariant antialias = s.value("antialias");
    if (antialias.isValid())
        setFontAntialiasing(antialias.toBool());

    QVariant systemColors0 = s.value("systemColors");
    if (systemColors0.isValid()) {
        systemColors = systemColors0.toBool();
    } else {
        systemColors = false;
    }
    QString pangramStyle;
    if (!systemColors)
        pangramStyle = QString(
            "QLabel { color: black; background-color: white; }");
    text->setStyleSheet(pangramStyle);
    charsTable->useSystemColors(systemColors);

    if (reload)
        return;

    QVariant fontStyle0 = s.value("fontStyle");
    if (fontStyle0.isValid()) {
        QFont fontStyle1 = fontStyle0.value<QFont>();
        setFontStyle(fontStyle1);
    } else if (fontList->count() > 0) {
        fontList->setCurrentItem(fontList->item(0));
    }

    QString fileName = s.value("fileName").toString();
    setFontFromFile(fileName);

    QString subset = s.value("subset").toString();
    if (!subset.isEmpty())
        setCurrentSubset(subset);

    QSize windowSize = s.value("windowSize").toSize();
    if (windowSize.isValid())
        resize(windowSize);

    QVariant tab = s.value("tab");
    if (tab.isValid())
        tabWidget->setCurrentIndex(tab.toInt());

    QVariant key = s.value("key");
    if (key.isValid())
        charsTable->goToChar(QChar(key.toInt()));

    QVariant recentList0 = s.value("recentList");
    if (recentList0.isValid()) {
        QStringList recentList1 = recentList0.value< QStringList >();

        for (int i = 0; i < recentList1.size() && i < 10; ++i) {
            if ((recentList.indexOf(recentList1[i]) == -1) &&
                QFile().exists(recentList1[i]))
                recentList.append(recentList1[i]);
        }

        updateRecentList();
    }
}

void MainWindow::saveSettings() const
{
    QSettings s(qApp->applicationName());

    s.setValue("antialias", antialiasing);
    s.setValue("autoFontMerge", autoMerging);
    s.setValue("systemColors", systemColors);
    s.setValue("fontStyle", fontStyle);
    s.setValue("subset", subsets->currentText());
    s.setValue("windowSize", QSize(width(), height()));
    s.setValue("tab", tabWidget->currentIndex());
    s.setValue("fileName", fileName);
    s.setValue("recentList", recentList);
    s.setValue("key", charsTable->currentKey());

    s.sync();
}

const QString & MainWindow::fullFontName(bool noSize) const
{
    static QString result;
    result = fontStyle.family() +
        (fontStyle.bold() ? " " + tr("Bold") : "") +
        (fontStyle.italic() ? " " + tr("Italic") : "") +
        (noSize ? "" : " " + QString::number(fontStyle.pointSize()));
    return result;
}

void MainWindow::updateRecentList()
{
    QList<QAction *> items = menuRecentFiles->actions();
    qDeleteAll(items.begin(), items.end());
    items.clear();

    if (!fileName.isEmpty()) {
        (void)recentList.removeDuplicates();
        (void)recentList.removeOne(fileName);
        recentList.prepend(fileName);
    }

    for (int i = 0; i < recentList.size() && i < 10; ++i) {
        QAction *action = new QAction(
            QFileInfo(recentList[i]).baseName(), this);
        action->setData(recentList[i]);
        action->setToolTip(recentList[i]);
        connect(action, SIGNAL(triggered()),
                this, SLOT(recentAction_triggered()));
        menuRecentFiles->addAction(action);
    }
}

void MainWindow::makePangram()
{
    jobStart(tr("Making pangram..."));

    QString numbers;
    for (int i = 0; i <= 9; ++i)
        numbers += QString::number(i);

    QString s = QString("<span style=\"font-size:16pt\">%1</span><br/><br/>"
        "<span style=\"font-size:12pt\">"
        "abcdefghjklmnopqrstuvwxyz<br>ABCDEFGHJKLMNOPQRSTUVWXYZ<br/>"
        "%2.:,;(*!?')<br/>"
        "<br/></span>").arg(fullFontName(), numbers);

    QList<int> sizes;
    sizes << 8 << 9 << 10 << 12 << 14 << 16 << 18 << 20 << 22 << 24 << 26
          << 28 << 36;
    for(int i = 0; i < sizes.size(); ++i) {
        s += QString("<span style=\"font-size:%1pt\">%2 %3</span><br/>")
                 .arg(QString::number(sizes[i]),
                      tr("The quick brown fox jumps over the lazy dog."),
                      numbers);
    }

    QString htmlText = QString("<!DOCTYPE HTML PUBLIC " \
"\"-//W3C//DTD HTML 4.0//EN" \
"http://www.w3.org/TR/REC-html40/strict.dtd\"><html><body>%1</body></html>")
        .arg(s);
    text->setText(htmlText);

    emit jobDoneSignal();
}

void MainWindow::updateInfo()
{
    QFont font = QFont(fontStyle.family(), 16);
    font.setBold(fontStyle.bold());
    font.setItalic(fontStyle.italic());
    fontNameLabel->setFont(font);
    fontNameLabel->setText(fullFontName());

    fileNameLabel->setText(fileName.isEmpty() ? tr("Unknown") : fileName);

    QList<QFontDatabase::WritingSystem> subs =
        fontDatabase.writingSystems(fontStyle.family());
    supportedSubsets->clear();
    for (int i = 0; i < subs.size(); ++i)
        supportedSubsets->addItem(QFontDatabase::writingSystemName(subs[i]));
}

QFontDatabase::WritingSystem MainWindow::currentSubset()
{
    int subsetId = subsets->itemData(subsets->currentIndex()).toInt();
    return (QFontDatabase::WritingSystem)subsetId;
}

void MainWindow::setCurrentSubset(const QString & subset)
{
    subsets->setCurrentIndex(subsets->findText(subset));
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this,
        tr("About %1 %2").arg(qApp->applicationName(),
                              qApp->applicationVersion()),
        tr("<b>%1 %2</b><br><br>"
           "%1 is a font viewer with character table.<br>\n"
           "Copyright (c) 2009-2014 Alexander Lopatin<br>\n"
           "<a href=\"http://qfontviewer.sourceforge.net\">http://qfontviewer.sourceforge.net</a><br>\n\n"
           "<center>This program is released under<br>\n"
           "the terms of the<br>\n"
           "GNU GENERAL PUBLIC LICENSE<br>\n"
           "Version 3, 29 June 2007</center>")
                .arg(qApp->applicationName(),
                     qApp->applicationVersion()));
}

void MainWindow::on_actionAboutQt_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
        this, tr("Open font file"), ".",
        tr("TrueType fonts (*.ttf);;OpenType fonts (*.otf);;\
TrueType collection (*.ttc *.ttcf);;All files (*.*)"));
    setFontFromFile(fileName);
}

void MainWindow::on_actionCut_triggered()
{
}

void MainWindow::on_actionCopy_triggered()
{
    switch (tabWidget->currentIndex()) {
    case 1:
        //text->
    case 2:
        copy(QString(charsTable->currentChar()));
    case 3:
        break;
    default:
        break;
    }
}

void MainWindow::on_actionPaste_triggered()
{
}

void MainWindow::on_actionDelete_triggered()
{
}

void MainWindow::on_actionRefresh_triggered()
{
    forceUpdateFontList();
    makePangram();
}

void MainWindow::on_actionSettings_triggered()
{
    saveSettings();
    SettingsDialog dialog;
    if (dialog.exec() == QDialog::Accepted)
        loadSettings(true);
}

void MainWindow::copy(const QString & text)
{
    clipboard->setText(text, QClipboard::Clipboard);
    clipboard->setText(text, QClipboard::Selection);
}

void MainWindow::on_copy_clicked()
{
    copy(copyBuffer->text());
}

void MainWindow::on_charsTable_characterSelected(const QChar & character)
{
    copyBuffer->setText(copyBuffer->text() + character);
}

void MainWindow::on_codeSearch_editingFinished()
{
    const QString & text = codeSearch->text();
    if (unicodeRegExp.indexIn(text) != -1) {
        uint code = unicodeRegExp.cap(1).toInt(0, 16);
        charsTable->goToChar(QChar(code));
        return;
    }

    // if (utf8RegExp.indexIn(text) != -1)
}

void MainWindow::recentAction_triggered()
{
    QAction *action = qobject_cast<QAction *>(sender());
    setFontFromFile(action->data().toString());
}

void MainWindow::updateFontList(bool force)
{
    jobStart(tr("Loading font list..."));

    static QString lastFontFilter, lastSubset;

    if (!force && lastFontFilter == fontFilter->text() &&
        lastSubset == subsets->currentText())
        return;

    lastFontFilter = fontFilter->text();
    lastSubset = subsets->currentText();

    QStringList fonts = fontDatabase.families(currentSubset());

    fontList->clear();

    if (!fontFilter->text().isEmpty())
        fonts = fonts.filter(fontFilter->text(), Qt::CaseInsensitive);

    fontList->addItems(fonts);

    QList<QListWidgetItem *> found = fontList->findItems(fontStyle.family(),
                                                         Qt::MatchExactly);
    if (!found.isEmpty())
        fontList->setCurrentItem(found[0]);

    emit jobDoneSignal();
}

void MainWindow::setFontStyle(const QFont & font)
{
    jobStart(tr("Loading font..."));

    // FIXME: Sometimes after typing in fontFilter field font.family() returns
    // an empty string. Fix this bug and remove the hack.
    if (font.family().isEmpty())
        return;

    QFont lastFont = fontStyle;
    fontStyle = font;

    if (lastFont != fontStyle) {
        QList<QListWidgetItem *> found = fontList->findItems(font.family(),
                                                             Qt::MatchExactly);
        if (!found.isEmpty())
            fontList->setCurrentItem(found[0]);

        fontBold->setChecked(font.bold());
        fontItalic->setChecked(font.italic());
        fontSize->setEditText(QString::number(font.pointSize()));

        const QString & fileName = fontsFileNames[fontStyle.family()];
        if (!fileName.isEmpty())
            this->fileName = fileName;

        text->setFont(fontStyle);
        emit update();
        makePangram();
        updateInfo();
        charsTable->setFontStyle(font);
    }

    emit jobDoneSignal();
}

void MainWindow::setFontFamily(const QString & family)
{
    fileName = QString();
    QFont newFont = fontStyle;
    newFont.setFamily(family);
    setFontStyle(newFont);
}

void MainWindow::setFontBold(bool enable)
{
    QFont newFont = fontStyle;
    newFont.setBold(enable);
    setFontStyle(newFont);
}

void MainWindow::setFontItalic(bool enable)
{
    QFont newFont = fontStyle;
    newFont.setItalic(enable);
    setFontStyle(newFont);
}

void MainWindow::setFontSize(qreal size)
{
    QFont newFont = fontStyle;
    newFont.setPointSizeF(size);
    setFontStyle(newFont);
}

void MainWindow::setFontSize(const QString & size)
{
    setFontSize(size.toDouble());
}

void MainWindow::setFontAutoMerging(bool enable)
{
    QFont newFont = fontStyle;
    autoMerging = enable;

    QFont::StyleStrategy strategy = antialiasing ? QFont::PreferDefault
                                                 : QFont::PreferAntialias;

    if (!autoMerging)
        strategy = (QFont::StyleStrategy)(strategy | QFont::NoFontMerging);

    newFont.setStyleStrategy(strategy);
    setFontStyle(newFont);
}

void MainWindow::setFontAntialiasing(bool enable)
{
    QFont newFont = fontStyle;
    antialiasing = enable;

    QFont::StyleStrategy strategy = autoMerging ? QFont::PreferDefault
                                                : QFont::NoFontMerging;

    strategy = (QFont::StyleStrategy)
        (strategy | (enable ? QFont::PreferAntialias : QFont::NoAntialias));
    newFont.setStyleStrategy(strategy);

    setFontStyle(newFont);
}

void MainWindow::setFontFromFile(const QString & fileName)
{
    if (fileName.isEmpty())
        return;

    int fontId = fontDatabase.addApplicationFont(fileName);
    if (fontId == -1) {
        QMessageBox::critical(this, tr("Font load failed"),
                              tr("Can't load font from the file \"%1\"")
                                  .arg(fileName));
        return;
    }

    QStringList families = QFontDatabase::applicationFontFamilies(fontId);
    if (families.size() > 0) {
        updateFontList(true);
        setFontFamily(families[0]);
        fontsFileNames[families[0]] = fileName;
        this->fileName = fileName;
        updateRecentList();
    } else {
        QMessageBox::critical(this, tr("Font load failed"),
                              tr("Can't set font family from the file \"%1\"")
                                  .arg(fileName));
    }
}

void MainWindow::jobStart(const QString & statusText)
{
    emit update();
    if (statusText.length() > 0)
        statusBar()->showMessage(statusText);

    setCursor(QCursor(Qt::WaitCursor));
}

void MainWindow::jobDone()
{
    statusBar()->clearMessage();
    setCursor(QCursor(Qt::ArrowCursor));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveSettings();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        QString fileName = event->mimeData()->urls()[0].path();
        setFontFromFile(fileName);
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
}
