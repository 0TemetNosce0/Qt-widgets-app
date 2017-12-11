#ifndef NEUPLAYLIST_H
#define NEUPLAYLIST_H

#include <QMediaPlaylist>
#include <QUrl>
#include <QWidget>
#include <QApplication>
#include <QSettings>
#include <QFile>
#include <QTextStream>
#include <QDirIterator>
#include <QMessageBox>

class neuPlaylist : public QMediaPlaylist
{
    Q_OBJECT
public:
    explicit neuPlaylist(QObject *parent = 0);
    void save(const QString &toFileName = "neuLibrary.m3u8");
    void save(const QString &toFileName, const QUrl &pathSaved);
    void saveFromPlaylist(const QString &playlistName = "neuLibrary.m3u8");
    QList<QUrl> setLibrary(const QString &path); //Used by settings.cpp
    QList <QUrl> update(const QString &path); //Used by playlist to update
    ~neuPlaylist();

private:
    QStringList a_listFilter;
};

#endif // NEUPLAYLIST_H
