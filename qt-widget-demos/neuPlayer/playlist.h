#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QMainWindow>
#include <QDebug>
#include <QModelIndex>
#include <QListWidgetItem>
#include <QPointer>
#include <QToolTip>

#include "neuplaylist.h"
#include "fademanager.h"
#include "moveanimation.h"
#include "player.h"
namespace Ui {
class Playlist;
}
class Player;
class neuPlaylist;

class Playlist : public QMainWindow
{
    Q_OBJECT
public slots:
    //Basic interface with the player
    void playItem(QModelIndex itemIndex);
    void quickUpdate(QList <QUrl> *items, int currentItemPlusOne);
    void updateList(neuPlaylist *listeFichiers, bool setZeroIndex = false);
    //Other
    void setTab(int tabId); //Called by :  user, programmatically, and by player when needed.
public:
    explicit Playlist(neuPlaylist &liste, neuPlaylist &favs, Player *player, QPixmap *cover, QString title, bool playingState, QWidget *parent = 0);
    explicit Playlist(QWidget *parent = 0);
    void setupConnections();
    void setupActions();
    void setupMode();
    /*Setters and getters */
    void setCurrentItem(int index, QPixmap *cover, QString title, bool playing);
    //Icon
    void setToPlaying(int index);
    void setToPaused(int index);
    void deleteItem(int index);
    bool isPlayingState() const
    {
        return a_isPlaying;
    }

    void updateFavs(neuPlaylist *favPlaylist);
    void setHeader(QPixmap *cover, QString title); //Sets the cover art and the title
    int queuedIndex() //getter
    {
        return ++a_queueIndex;
    }

    ~Playlist();

private slots:
    void scrollToPlaying();
    void findItemVisibilityHandler();
    void prepareContextMenu();
    void showContextMenu() const;
    void deleteItem();
    void addItemToQueue();
    void addToFavContext();
    void addToFav();
    void viewInfo();
    void sendNewInfos();
    //Own actions of the playlist interacting with the player
    void setFolder();
    void on_starClicked();

    void reloadLibrary();
    void randomModeChanger();
    void loopModeChanger();
    void setShuffle();
    void setSequential();
    void validateSearch();
    void saveTheItems();

private:
    void updateInfoHeader(QString &title, QPixmap &cover);
    bool checkIfNotFav(int index);
    void deleteFav(int index);
    void makeStarFull();
    void makeStarEmpty();
    //Events
    void closeEvent(QCloseEvent *);

    //Attributes

    Ui::Playlist *ui;
    Player *a_player;
    neuPlaylist *a_playlist;
    neuPlaylist *a_favPlaylist;
    bool a_isPlaying;
    bool a_isReload;
    bool a_favsNotLoadedYet;
    QPixmap a_defaultCover;
    FadeManager a_fadeManager;
    MoveAnimation a_moveAnim;
    int a_previousIndex;
    int a_previousTab;
    int a_currentIndex;
    int a_queueIndex;
    QList <QListWidgetItem*> a_backupItems;
    QAction *a_findItemTrigger; // ctrl-F to search ~
    QAction *a_validateFind; // Pouvoir trigger facilement un search sans farfouiller des events
    QAction *a_easyHideFind; // Pour pouvoir hide avec echap
    QMenu *a_playlistMenu; //This is for the ... button
    //Actions of the playlist menu
    QAction *a_reloadLibrary;
    QAction *a_selectOtherDir;
    QMenu *a_playlistContextMenu; //This is the context menu called by right-click on an item
    //Actions of the context menu
    QAction *a_addToQueue;
    QAction *a_viewInfo;
    QAction *a_deleteItemFromQueue;
    QAction *a_addToFav;
    QSettings a_settings;
    QPointer <QMediaPlayer> a_tempPlayer;
};

#endif // PLAYLIST_H
