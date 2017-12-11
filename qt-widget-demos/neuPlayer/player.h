#ifndef PLAYER_H
#define PLAYER_H

#include <QMainWindow>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaMetaData>
#include <QFileDialog>
#include <QFile>
#include <QSettings>
#include <QMenu>
#include <QTimer>
#include <QTime>
#include <QAction>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDropEvent>
#include <QDesktopServices>
#include <QFileInfo>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QMessageBox>
#include <QGraphicsOpacityEffect>
#include <QBitmap>
#include <QPainter>
#include <QRegion>

#ifdef Q_OS_WIN
#include <QtWinExtras/QWinThumbnailToolButton>
#include <QtWinExtras/QWinThumbnailToolBar>
#endif

#include "tagviewer.h"
#include "playlist.h"
#include "slider.h"
#include "settings.h"
#include "neuplaylist.h"
#include "fademanager.h"
#include "fadewindow.h"
#include "scrollinglabel.h"
namespace Ui {
class Player;
}
class Playlist;
class ScrollingLabel;
class Settings;
class Player : public QMainWindow
{
    Q_OBJECT
public slots:
    //Loading library
    void setupNewLibrary();
    void checkForNewMedias();
    void updateLibrary();
    void savePlaylists();
    //Basic Media Controls
    void playMedia();
    void errorHandling(QMediaPlayer::Error error);
    void statusChanged(QMediaPlayer::MediaStatus status);
    void stateChanged(QMediaPlayer::State state);
    void setType();
    void finishingUp();
    void pauseMedia();
    void forwardMedia();
    void previousMedia();
    void endOfMediaGuard();
    //Show un QMenu...
    void showMenu();
    //Ouvre un file dialog natif pour choisir quoi lire
    void openMedia();
    //Quand on le lit et il avance...
    void UpdateProgress(qint64 pos);
    //Utilisateur bougeant le slide...
    void seekProgress(int pos);
    //Quand on charge le fichier...
    void on_durationChanged(qint64 pos);
    void advanceProgress();
    void backProgress();
    void setMeta();
    void update_info();
    //Volume
    void on_volumeChanged(int pos);
    void setVolumeMuted();
    void volumeUp();
    void volumeDown();
    //éléments menu
    void windowFlagsHandler();
    void setShuffle();
    void playbackHandler(QAction *playbackSelected);
    void setPlaybackRate();
    void showSettings();
    void showPlaylist();
    void showTagViewer(); //Uses QList <QString> for the sake of consistency

    void loadSkin();
    //Events
    void closeEvent(QCloseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event); //Autorise le drop
    void dropEvent(QDropEvent *event); //Effectue le traitement du drop
    void delayedClose();

signals:
    void EndOfMedia();
public:
    Ui::Player *ui;
    explicit Player(QWidget *parent = 0);
    void restart();
    void setupPlayMode();
    void loadPlaylist();
    void setLightCSS();
    void setDarkCSS();
    //Do all the check for which label to show and update it.
    void updateLabel(QString &text);
    // Routine to update anim target when necessary
    void updateAnimTarget();
    //Handles the change of the speed at which the info displayed changes
    void updateFadeinSpeed();
    //Méthodes accesseurs et mutateurs

    void setAudioFadeValue(int value)
    {
        a_audioFade->setDuration(value);
    }

    void setAudioFade(bool enabled)
    {
        a_audioFadeActivated = enabled;
    }

    void runAudioFade();
    void setPlaylistOpen(bool open)
    {
        a_isPlaylistOpen = open;
        if(!a_isPlaylistOpen)
            a_playlist = nullptr;
    }
    void setSettingsOpen(bool open)
    {
        a_isSettingsOpen = open;
    }

    //Will always return the correct index regardless of the playlist used
    inline int getIndexOfThePlayer()
    {
        return neu->playlist()->currentIndex();
    }

    void setIndexOfThePlayer(int index, bool play);
    void addMediasToThePlayer(QList <QUrl> &medias);
    void setPlaylistToBeSaved(bool foo)
    {
        a_hasToSavePlaylistLater = foo;
    }

    void setFavsToBeSaved(bool foo)
    {
        a_hasToSaveFavsLater = foo;
    }

    bool deleteMedia(int index, int tab = 0)
    {
        if(!a_isUsingFavPlaylist)
        {
            if(tab == 0)
            {
                if(a_mediaPlaylist.currentIndex() == index)
                    return false;
            }
        }
        else
        {
            if(tab == 1)
            {
                if(a_favPlaylist.currentIndex() == index)
                    return false;
            }
        }
        a_settings.setValue("trackPosition", neu->position());
        int track = neu->playlist()->currentIndex() - 1;
        if(tab == 0)
            a_mediaPlaylist.removeMedia(index);
        else
            a_favPlaylist.removeMedia(index);
        if(tab == 0 && !a_isUsingFavPlaylist)
        {
            if(index <= track)
            {
                a_deleteTriggered = true;
                a_mediaPlaylist.setCurrentIndex(track);
            }
        }
        else if (tab == 1 && a_isUsingFavPlaylist)
        {
            if(index <= track)
            {
                a_deleteTriggered = true;
                a_favPlaylist.setCurrentIndex(track);
            }
        }
        if(a_hasToSavePlaylistLater != true)
            a_hasToSavePlaylistLater = true;
        //The update of a_hasToSaveFavsLater is handled by the playlist if needed
        return true;
    }

    void addFav(int index);

    void changeToFavPlaylist();
    void changeToDefaultPlaylist();

    void addToQueue(int index, int currentlyPlaying);
    void setOpacity(qreal opacityFromSettings = 0.0);
    void setRandomMode(bool mode);
    void setLoopMode(bool mode);
    bool getRandomState() const
    {
        return a_isRandomMode;
    }
    inline void setUsingFav(bool usingFav)
    {
        a_isUsingFavPlaylist = usingFav;
    }

    inline bool isUsingFav() const
    {
        return a_isUsingFavPlaylist;
    }
    bool getLoopState() const
    {
        return a_isLoopPlaylistMode;
    }
    inline bool canChangeMusic() const
    {
        return a_canChangeMusic;
    }
    bool deleteTriggered() const
    {
        return a_deleteTriggered;
    }
    void updatePlaylistOfThePlayer(const QList <QUrl> &medias, bool play = false);
    void saveBeforeClosing();

    ~Player();


private slots:
    inline void canChangeMusicNow()
    {
        a_canChangeMusic = true;
    }
    inline void canShuffleNow()
    {
        a_canDoShuffleAgain = true;
    }
private:
    //Méthodes de constructeur
    void setupObjects();
    void setupMenus();
    void setupConnections();
    //Load plugins selected
    void setupPlugins();
    void setFramelessButtonsVisibility(bool visible);

    void forwardAnim(); //Created as a separate module because we call it at several places
    void previousAnim(); //Created for consistency with forwardAnim();
    void fadeInLabel(); //Convenience function
    void updateProgressDisplay(qint64 pos, bool isProgress); //Used to update the display of both duration (isProgress = false) and progress (isProgress = true)

    //Attributs
    QMediaPlayer *neu; //Dat media player
    Slider *a_progressSlider;
    Slider *a_volumeSlider;
    QPointer <Playlist> a_playlist;
    QPointer <Settings> a_settingsForm;

    /* Extras for win */
#ifdef Q_OS_WIN
    QWinThumbnailToolButton a_thumbActionButton;
    QWinThumbnailToolButton a_thumbPreviousButton;
    QWinThumbnailToolButton a_thumbForwardButton;
    QWinThumbnailToolBar a_thumbnailToolbar;
#endif

    QSettings a_settings; //Contient les settings de l'application
    neuPlaylist a_mediaPlaylist;
    neuPlaylist a_favPlaylist;
    QPointer<FadeManager> a_animManager;
    int a_idSkin; // 0 : Light | 1 : Dark | n : custom theme
    int a_previousIndex;
    bool a_isFrameless;
    bool a_hasToSavePlaylistLater;
    bool a_hasToSaveFavsLater;
    bool a_wasPrevious;
    bool a_hasToStartupPlaylist;
    bool a_deleteTriggered;
    bool a_recoveredProgress;
    bool a_isSettingsOpen;
    bool a_isPlaylistOpen;
    bool a_isRandomMode;
    bool a_isLoopPlaylistMode;
    bool a_hasToDoInitialShuffle;
    bool a_isPlaying;
    bool a_isScrollingText;
    bool a_hasToSetLabelType;
    bool a_canClose;
    bool a_canChangeMusic;
    bool a_canDoShuffleAgain;
    bool a_isStarting;
    bool a_isUsingFavPlaylist;
    bool a_audioFadeActivated;
    bool a_no_meta;
    int a_secondesPasse;
    int a_volumeBeforeMute;
    //The three int delays at which we switch over
    int a_titleCase;
    int a_artistCase;
    int a_albumCase;
    //Meta datas
    QString a_titre, a_artiste, a_album;
    /* Icons stored on attributes to avoid reloading each time */
    const QIcon a_forwardIcon, a_forwardDarkIcon;
    const QIcon a_previousIcon, a_previousDarkIcon;
    const QIcon a_volumeIcon, a_volumeDarkIcon;
    const QIcon a_volumeLowIcon, a_volumeLowDarkIcon;
    const QIcon a_volumeMutedIcon, a_volumeMutedDarkIcon;
    const QPixmap a_neuDarkBg, a_neuLightBg, a_neuLightCustombg, a_neuDarkCustombg;

    ScrollingLabel a_scrollingLabel; //Custom label
    QPixmap a_coverArt;
    QPropertyAnimation *a_titleAnimate;
    QPropertyAnimation *a_audioFade;
    QGraphicsOpacityEffect *a_infoFadein;
    QPropertyAnimation *a_infoFadeAnim;
    //Regular timer, updated each second
    QTimer Timer;
    //The timer which sets the type when it timeouts
    QTimer setTypeTimer;
    //The timers slowing down operations so there's no crash
    QTimer grantChangeTimer;
    QTimer grantShuffleAgainTimer;
    /*          Permet l'utilisation de raccourcis clavier
     * qui interagissent directement avec le player sans souris */
    QAction a_advance;
    QAction a_back;
    QAction a_volumeUp;
    QAction a_volumeDown;
    //Menu et ses actions
    QMenu a_playbackMenu;
    QActionGroup a_playbackrates;
    QAction a_normalrate;
    QAction a_halfrate;
    QAction a_doublerate;
    int a_playbackState;
    QMenu a_menu;
    QAction a_openMedia;
    QAction a_accessSettings ;
    QAction a_tagViewer;
    QAction a_showPlaylist;
    QAction a_alwaysOnTopHandler; //Set les flags pour always on top ou non
    QAction a_shuffle;
};

#endif // PLAYER_H
