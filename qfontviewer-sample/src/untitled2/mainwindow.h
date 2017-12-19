#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QWidget>
#include <QMainWindow>
#include <QFont>
#include <QFontDatabase>
#include <QMap>
#include <QClipboard>
#include <QRegExp>
#include <QDropEvent>
#include <QDragEnterEvent>

class MainWindow : public QMainWindow, Ui::MainWindow
{
    Q_OBJECT

    static QRegExp unicodeRegExp/*, utf8RegExp*/;
    QFontDatabase fontDatabase;
    bool antialiasing, autoMerging, systemColors;
    QFont fontStyle;
    QString fileName;
    QStringList recentList;
    QMap<QString, QString> fontsFileNames;
    QClipboard *clipboard;

    void processArgs(const QStringList & args);
    void setValidators();

public:
    MainWindow(const QStringList & args = QStringList(), QWidget *parent = 0);
    ~MainWindow();
    void loadSettings(bool reload = false);
    void saveSettings() const;

    QFontDatabase::WritingSystem currentSubset();
    void setCurrentSubset(const QString & subset);

    void updateRecentList();

public slots:
    void makePangram();
    void updateInfo();
    void on_actionOpen_triggered();
    void on_actionCut_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionDelete_triggered();
    void on_actionSettings_triggered();
    void on_actionRefresh_triggered();
    void on_actionAbout_triggered();
    void on_actionAboutQt_triggered();
    void on_actionExit_triggered();
    void copy(const QString & text);
    void on_copy_clicked();
    void on_charsTable_characterSelected(const QChar & character);
    void on_codeSearch_editingFinished();
    void recentAction_triggered();
    void updateFontList(bool force = false);
    void forceUpdateFontList() { updateFontList(true); }
    const QString & fullFontName(bool noSize = true) const;
    void setFontStyle(const QFont & font);
    void setFontFamily(const QString & family);
    void setFontBold(bool enable);
    void setFontItalic(bool enable);
    void setFontSize(qreal size);
    void setFontSize(const QString & size);
    void setFontAutoMerging(bool enable);
    void setFontAntialiasing(bool enable);
    void setFontFromFile(const QString & fileName);
    void jobStart(const QString & statusText);
    void jobDone();

signals:
    void jobDoneSignal();

protected:
    void closeEvent(QCloseEvent *event);
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
};

#endif
